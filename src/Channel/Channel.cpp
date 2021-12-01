#include "Channel.hpp"

irc::Channel::Channel()
	: users() {}

void irc::Channel::addUser(User *user) { users.push_back(user); }
void irc::Channel::delUser(User *user)
{
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	while (it != ite)
	{
		if (*it == user)
			users.erase(it);
		it++;
	}
}

void irc::Channel::broadcast(std::string str)
{
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	while (it != ite)
	{
		(*it)->write(str);
		it++;
	}
}
