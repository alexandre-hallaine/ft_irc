#include "Server.hpp"
#include "../struct/user.hpp"
#include <iostream>
#include <arpa/inet.h>

irc::Server::Server(unsigned short port, std::string password)
	: settings(), connection(port), commands()
{
	settings.port = port;
	settings.password = password;
}

void irc::Server::run()
{
	while (true)
	{
		struct user user = connection.waiting();
		std::cout << "new client #" << user.fd << " from " << inet_ntoa(user.address.sin_addr) << ":" << ntohs(user.address.sin_port) << std::endl;
		while (true)
		{
			std::string str = read(user.fd);
			if (str.empty())
				break;
			while (str.length())
			{
				std::string tmp(line(str));
				commands.call(next(tmp, " "), tmp);
			}
		}
	}
}
