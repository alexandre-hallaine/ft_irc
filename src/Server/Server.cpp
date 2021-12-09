#include "Server.hpp"
#include "../User/User.hpp"
#include "../utils/utils.hpp"
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

void irc::Server::init()
{
	int enable = 1;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		error("socket");
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)))
		error("setsockopt");
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		error("fcntl");

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(config.get("port").c_str()));

	if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		error("bind");
	if (listen(fd, address.sin_port) < 0)
		error("listen");

	displayUsers();
}
void irc::Server::displayUsers()
{
	std::stringstream ss;
	ss << "Users: " << users.size();
	display.write(1, ss.str());
}
void irc::Server::pendingConnection()
{
	while (true)
	{
		struct sockaddr_in address;
		socklen_t csin_len = sizeof(address);
		int fd = accept(this->fd, (struct sockaddr *)&address, &csin_len);
		if (fd == -1)
			break;
		users[fd] = new User(fd, address);
		displayUsers();
		if (DEBUG)
			std::cout << "new User " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << " (" << fd << ")" << std::endl;
	}
}

irc::Server::Server()
	: upTime(currentTime()), stop(false) { display.write(0, "Welcome to our \033[1;37mIRC\n"); }

void irc::Server::loop()
{
	init();
	while (!stop)
	{
		pendingConnection();

		std::map<int, User *>::iterator it = users.begin();
		std::map<int, User *>::iterator ite = users.end();
		while (it != ite)
		{
			(*it).second->pendingMessages(this);
			++it;
		}
	}
}

irc::Config &irc::Server::getConfig() { return config; }
std::string irc::Server::getUpTime() { return upTime; }
std::vector<irc::User *> irc::Server::getUsers()
{
	std::vector<User *> users = std::vector<User *>();

	std::map<int, User *>::iterator it = this->users.begin();
	std::map<int, User *>::iterator ite = this->users.end();
	while (it != ite)
	{
		users.push_back(it->second);
		++it;
	}
	return users;
}

void irc::Server::quitUser(User user)
{
	close(user.getFd());
	users.erase(users.find(user.getFd()));
	displayUsers();
}
