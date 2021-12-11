#include "Server.hpp"
#include "../User/User.hpp"
#include "../Utils/Utils.hpp"
#include "../User/Command/Channel/Channel.hpp"
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
#include <poll.h>
#include <unistd.h>

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

	displayUsers();

	config.set("user_mode", "aiwroOs");
	config.set("channel_mode", "");
}
void irc::Server::displayUsers()
{
	std::stringstream ss;
	ss << "Users: " << users.size();
	display.write(1, ss.str());
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
			displayUsers();
			if (DEBUG)
				std::cout << "new User " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << " (" << fd << ")" << std::endl;
		}
	}
}

irc::Server::Server()
	: upTime(currentTime()), stop(false) { display.write(0, "Welcome to our \033[1;37mIRC\n"); }

void irc::Server::loop()
{
	init();

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

		if (poll(pfds, users.size() + 1, -1) == -1)
			error("poll", false);

		if (pfds[0].revents == POLLIN)
			pendingConnection();
		else
			for (size_t index = 0; index < users.size(); ++index)
				if (pfds[index + 1].revents == POLLIN)
					this->users[pfds[index + 1].fd]->pendingMessages(this);
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
irc::Channel *irc::Server::getChannel(std::string channelName) { return channels.find(channelName)->second; }
void irc::Server::addChannel(std::string channelName) { channels.insert(std::pair<std::string, irc::Channel *>(channelName, new irc::Channel(channelName))); }
void irc::Server::removeChannel(std::string channelName) { channels.erase(channelName); }

void irc::Server::quitUser(User &user)
{
	users.erase(users.find(user.getFd()));
	delete &user;

	displayUsers();
}
