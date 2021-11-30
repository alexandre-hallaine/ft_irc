#include "Server.hpp"
#include "../struct/user.hpp"
#include <iostream>
#include <arpa/inet.h>

#include "unistd.h"

irc::Server::Server(unsigned short port, std::string password)
	: settings(), connection(port)
{
	settings.port = port;
	settings.password = password;
}

void irc::Server::run()
{
	struct user user = connection.next();
	std::cout << "new client #" << user.fd << " from " << inet_ntoa(user.address.sin_addr) << ":" << ntohs(user.address.sin_port) << std::endl;

	char buffer[BUF_SIZE + 1];
	ssize_t msg_len = recv(user.fd, &buffer, BUF_SIZE, 0);
	write(1, buffer, msg_len);
}
