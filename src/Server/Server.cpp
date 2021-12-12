#include "Server.hpp"
#include "../User/User.hpp"
#include "../Utils/Utils.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <unistd.h>
#include <algorithm>

void irc::Server::init()
{
	int enable = 1;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		error("socket", true);
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)))
		error("setsockopt", true);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		error("fcntl", true);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(config.get("port").c_str()));

	if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		error("bind", true);
	if (listen(fd, address.sin_port) < 0)
		error("listen", true);

	config.set("user_mode", "aiwroOs");
	config.set("channel_mode", "");
	if ((size_t)atoi(config.get("max").c_str()) > 4242)
		config.set("max", "4242");
}
void irc::Server::pendingConnection()
{
	size_t max_user = atoi(config.get("max").c_str());

	while (true)
	{
		struct sockaddr_in address;
		socklen_t csin_len = sizeof(address);
		int fd = accept(this->fd, (struct sockaddr *)&address, &csin_len);
		if (fd == -1)
			break;
		if (users.size() == max_user)
			close(fd);
		else
		{
			users[fd] = new User(fd, address);
			updateUsers();
			if (DEBUG)
				std::cout << "new User " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << " (" << fd << ")" << std::endl;
		}
	}
}
void irc::Server::sendPing()
{
	time_t current = std::time(0);
	int timeout = atoi(config.get("timeout").c_str());

	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
		if (current - (*it).second->getLastPing() >= timeout)
			delUser(*(*it).second);
		else if ((*it).second->isRegistered())
		{
			(*it).second->write("PING " + (*it).second->getNickname());
			(*it).second->push();
		}
}

void irc::Server::updateUsers()
{
	display.set(fd, "FD\tHost\tNickname");
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		std::stringstream ss;
		ss << (*it).second->getFd() << "\t" << (*it).second->getHost() << "\t" << (*it).second->getNickname();
		display.set((*it).second->getFd(), ss.str());
	}
}
void irc::Server::updateChannels()
{
	std::stringstream ss;
	ss << "Channels: " << channels.size();
	display.set(2, ss.str());
}

irc::Server::Server()
	: upTime(currentTime()), stop(false) { display.set(0, "Welcome to our \033[1;37mIRC\n"); }

void irc::Server::loop()
{
	init();

	int ping = atoi(config.get("ping").c_str());
	time_t last_ping = std::time(0);

	while (!stop)
	{
		std::vector<irc::User *> users = getUsers();
		struct pollfd pfds[4242];

		pfds[0].fd = fd;
		pfds[0].events = POLLIN;

		for (size_t index = 0; index < users.size(); ++index)
		{
			pfds[index + 1].fd = users[index]->getFd();
			pfds[index + 1].events = POLLIN;
		}

		if (poll(pfds, users.size() + 1, (ping * 1000) / 10) == -1)
			error("poll", false);

		if (std::time(0) - last_ping >= ping)
		{
			sendPing();
			last_ping = std::time(0);
			continue;
		}

		if (pfds[0].revents == POLLIN)
			pendingConnection();
		else
		{
			for (size_t index = 0; index < users.size(); ++index)
				if (pfds[index + 1].revents == POLLIN)
					this->users[pfds[index + 1].fd]->pendingMessages(this);
			updateUsers();
		}
	}
}

irc::Config &irc::Server::getConfig() { return config; }
std::string irc::Server::getUpTime() { return upTime; }

std::vector<irc::User *> irc::Server::getUsers()
{
	std::vector<User *> users = std::vector<User *>();

	for (std::map<int, User *>::iterator it = this->users.begin(); it != this->users.end(); ++it)
		users.push_back(it->second);
	return users;
}
void irc::Server::delUser(User &user)
{
	std::vector<Channel> remove;
	for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::vector<irc::User *> users = (*it).second.getUsers();
		if (std::find(users.begin(), users.end(), &user) != users.end())
			(*it).second.removeUser(user);
		if (!(*it).second.getUsers().size())
			remove.push_back((*it).second);
	}
	for (std::vector<Channel>::iterator it = remove.begin(); it != remove.end(); ++it)
		delChannel(*it);

	display.remove(user.getFd());

	users.erase(user.getFd());
	delete &user;
}

bool irc::Server::isChannel(std::string name) { return channels.count(name); }
irc::Channel &irc::Server::getChannel(std::string name)
{
	bool exist = isChannel(name);
	Channel &channel = channels[name];
	if (!exist)
		channel.setName(name);
	updateChannels();
	return channel;
}
void irc::Server::delChannel(Channel channel)
{
	channels.erase(channels.find(channel.getName()));
	updateChannels();
}
