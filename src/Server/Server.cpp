#include "Server.hpp"
#include "../User/User.hpp"
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
	while (true)
	{
		User user;
		if (!users.size())
			user = connection.force_waiting();
		else
			user = connection.waiting();
		if (user.getFd() != -1)
		{
			users.push_back(user);
			std::cout << "new client #" << user.getFd() << " from " << inet_ntoa(user.getAddress().sin_addr) << ":" << ntohs(user.getAddress().sin_port) << std::endl;
		}

		size_t index = 0;
		size_t len = users.size();
		while (index < len)
		{
			User &user = users.at(index);
			std::string str = read(user.getFd());
			while (str.length())
			{
				std::string tmp(line(str));
				commands.call(next(tmp, " "), tmp, user);
			}
			index++;
		}
	}
}
