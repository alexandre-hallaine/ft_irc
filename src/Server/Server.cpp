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

void irc::Server::acceptUser()
{
	size_t max_user = atoi(config.get("max").c_str());

	while (true)
	{
		if (users.size() == max_user)
			if (shutdown(fd, SHUT_RD) == -1)
				break;
		struct sockaddr_in address;
		socklen_t csin_len = sizeof(address);
		int fd = accept(this->fd, (struct sockaddr *)&address, &csin_len);
		if (fd == -1)
			break;
		users[fd] = new User(fd, address);
		if (DEBUG)
			std::cout << "new User " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << " (" << fd << ")" << std::endl;
	}
}
void irc::Server::sendPing()
{
	time_t current = std::time(0);
	int timeout = atoi(config.get("timeout").c_str());

	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
		if (current - (*it).second->getLastPing() >= timeout)
		{
			(*it).second->setDeleteMessage("Ping timeout");
			(*it).second->setStatus(DELETE);
		}
		else if ((*it).second->getStatus() == ONLINE)
			(*it).second->write("PING " + (*it).second->getNickname());
}

void irc::Server::displayUsers()
{
	char buffer[42];
	sprintf(buffer, "%-4s %-9s %s", "FD", "Nickname", "Host");
	display.set(fd, std::string("\n") + buffer);
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		sprintf(buffer, "\033[34m%-4i \033[33m%-9s \033[35m%s", (*it).second->getFd(), (*it).second->getNickname().c_str(), (*it).second->getHost().c_str());
		display.set((*it).second->getFd(), buffer);
	}
}
void irc::Server::displayChannels()
{
	std::stringstream ss;
	ss << "\nChannels: " << channels.size();
	display.set(2, ss.str());
}

irc::Server::Server()
	: upTime(currentTime()), last_ping(std::time(0)) { display.set(0, "Welcome to our \033[1;37mIRC"); }

irc::Server::~Server()
{
	std::vector<User *> users = getUsers();
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
		delUser(*(*it));
}

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

	config.set("user_mode", "aiwros");
	config.set("channel_givemode", "Oov");
	config.set("channel_togglemode", "imnpst");
	config.set("channel_setmode", "kl");
	if ((size_t)atoi(config.get("max").c_str()) > 4242)
		config.set("max", "4242");
}
void irc::Server::execute()
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

	int ping = atoi(config.get("ping").c_str());

	if (poll(pfds, users.size() + 1, (ping * 1000) / 10) == -1)
		return;

	if (std::time(0) - last_ping >= ping)
	{
		sendPing();
		last_ping = std::time(0);
	}
	else
	{
		if (pfds[0].revents == POLLIN)
			acceptUser();
		else
			for (size_t index = 0; index < users.size(); ++index)
				if (pfds[index + 1].revents == POLLIN)
					this->users[pfds[index + 1].fd]->receive(this);
	}

	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		(*it)->push();
		if ((*it)->getStatus() == DELETE)
			delUser(*(*it));
	}
	displayUsers();
}

irc::Config &irc::Server::getConfig() { return config; }
std::string irc::Server::getUpTime() { return upTime; }

irc::User *irc::Server::getUser(std::string const &nick)
{
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
		if ((*it).second->getNickname() == nick)
			return (*it).second;
	return NULL;
}
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
	std::vector<irc::User *> broadcast_users = std::vector<irc::User *>();
	for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
		if ((*it).second.isUser(user))
		{
			(*it).second.removeUser(user);
			std::vector<irc::User *> users = it->second.getUsers();
			if (!users.size())
				remove.push_back((*it).second);
			else
				for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
					if (std::find(broadcast_users.begin(), broadcast_users.end(), *it) == broadcast_users.end())
						broadcast_users.push_back(*it);
		}

	for (std::vector<Channel>::iterator it = remove.begin(); it != remove.end(); ++it)
		delChannel(*it);

	std::string message = "QUIT :" + user.getDeleteMessage();
	for (std::vector<irc::User *>::iterator it = broadcast_users.begin(); it != broadcast_users.end(); ++it)
		user.sendTo(*(*it), message);

	display.remove(user.getFd());

	users.erase(user.getFd());
	delete &user;
}

bool irc::Server::isChannel(std::string const &name) { return channels.count(name); }
irc::Channel &irc::Server::getChannel(std::string name)
{
	bool exist = isChannel(name);
	Channel &channel = channels[name];
	if (!exist)
	{
		channel.setName(name);
		displayChannels();
	}
	return channel;
}
void irc::Server::delChannel(Channel channel)
{
	channels.erase(channel.getName());
	displayChannels();
}
std::vector<irc::Channel *> irc::Server::getChannels()
{
	std::vector<irc::Channel *> channels = std::vector<irc::Channel *>();
	for (std::map<std::string, irc::Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
		channels.push_back(&(*it).second);
	return channels;
}
