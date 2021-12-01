#include "Server.hpp"
#include "../struct/user.hpp"
#include <iostream>
#include <arpa/inet.h>

irc::Server::Server(unsigned short port, std::string password)
	: settings(), connection(port), commands(), users()
{
	settings.port = port;
	settings.password = password;
}

void irc::Server::run()
{
	struct user user;

	size_t index;
	size_t len;

	while (true)
	{
		if (!users.size())
			user = connection.force_waiting();
		else
			user = connection.waiting();
		if (user.fd != -1)
		{
			users.push_back(user);
			std::cout << "new client #" << user.fd << " from " << inet_ntoa(user.address.sin_addr) << ":" << ntohs(user.address.sin_port) << std::endl;
		}

		index = 0;
		len = users.size();
		while (index < len)
		{
			user = users.at(index);
			std::string str = read(user.fd);
			while (str.length())
			{
				std::string tmp(line(str));
				commands.call(next(tmp, " "), tmp, &user);
			}
			index++;
		}
	}
}
