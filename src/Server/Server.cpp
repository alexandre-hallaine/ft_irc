#include "Server.hpp"
#include "../User/User.hpp"
#include <iostream>
#include <arpa/inet.h>

irc::Server::Server(unsigned short port, std::string password)
	: settings(), users(), channels()
{
	settings.port = port;
	settings.password = password;
	connection = new Connection(port);
	commands = new CommandsBook();
}
irc::Server::~Server() { delete connection; }

void irc::Server::run()
{
	while (true)
	{
		User *user;
		if (!users.size())
			user = connection->force_waiting();
		else
			user = connection->waiting();
		if (user->getFd() != -1)
		{
			addUser(user);
			std::cout << "new client #" << user->getFd() << " from " << inet_ntoa(user->getAddress().sin_addr) << ":" << ntohs(user->getAddress().sin_port) << std::endl;
		}

		std::list<User *>::iterator it = users.begin();
		std::list<User *>::iterator ite = users.end();
		while (it != ite)
		{
			std::string str = read((*it)->getFd());
			while (str.length())
			{
				std::string tmp(line(str));
				commands->call(next(tmp, " "), tmp, *it);
			}
			it++;
		}
	}
}

void irc::Server::addUser(User *user)
{
	user->setServer(this);
	users.push_back(user);
}
void irc::Server::rmUser(User *user) { users.remove(user); }
void irc::Server::addChannel(std::string name, User *user) { channels[name].push_back(user); }
void irc::Server::rmChannel(std::string name, User *user)
{
	channels[name].remove(user);
	if (channels[name].empty())
		channels.erase(channels.find(name));
}
std::list<irc::User *> irc::Server::getChannel(std::string name) { return channels.at(name); }
