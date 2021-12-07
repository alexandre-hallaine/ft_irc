#include "Server.hpp"
#include "../utils/utils.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <cstdlib>
#include <iostream>

irc::Server::Server()
	: config(), display() {}

void irc::Server::init()
{
	upTime = currentTime();
	display.setLine(0, "Welcome to our \033[1;37mIRC\n");

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

	std::cout << config.get("motd") << std::endl;
}

void irc::Server::loop() { init(); }

irc::Config &irc::Server::getConfig() { return config; }
