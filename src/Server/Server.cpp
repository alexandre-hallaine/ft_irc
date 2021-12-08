#include "Server.hpp"
#include "../User/User.hpp"
#include "../utils/utils.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <cstdlib>
#include <iostream>
#include <sstream>

void irc::Server::init()
{
	int enable = 1;
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		exit(EXIT_FAILURE);
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)))
		exit(EXIT_FAILURE);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		exit(EXIT_FAILURE);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(config.get("port").c_str()));

	if (bind(fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		exit(EXIT_FAILURE);
	if (listen(fd, address.sin_port) < 0)
		exit(EXIT_FAILURE);
}
void irc::Server::displayUsers()
{
	std::stringstream ss;
	ss << "Users: " << users.size();
	display.write(1, ss.str());
}
void irc::Server::checkConnection()
{
	displayUsers();
	while (true)
	{
		struct sockaddr_in address;
		socklen_t csin_len = sizeof(address);
		int fd = accept(this->fd, (struct sockaddr *)&address, &csin_len);
		if (fd == -1)
			break;
		users[fd] = new User(fd, address);
		displayUsers();
	}
}

irc::Server::Server()
	: config(), display(), users(), upTime(currentTime()), stop(false) { display.write(0, "Welcome to our \033[1;37mIRC\n"); }

void irc::Server::loop()
{
	init();
	while (!stop)
	{
		checkConnection();
	}
}

irc::Config &irc::Server::getConfig() { return config; }
