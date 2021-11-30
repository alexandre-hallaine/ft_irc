#include "Server.hpp"
#include "../struct/user.hpp"
#include <iostream>
#include <arpa/inet.h>

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
	std::cout << "first msg: " << connection.read(user.fd) << std::endl;
}
