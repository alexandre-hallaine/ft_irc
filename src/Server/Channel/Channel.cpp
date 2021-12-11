#include "Channel.hpp"
#include "../../User/User.hpp"

irc::Channel::Channel() {}

void irc::Channel::setName(std::string name) { this->name = name; }
std::string irc::Channel::getName() { return name; }

void irc::Channel::setTopic(std::string topic) { this->topic = topic; }
std::string irc::Channel::getTopic() { return topic; }

void irc::Channel::addUser(User &user) { users[user.getFd()] = &user; }
void irc::Channel::removeUser(User &user) { users.erase(users.find(user.getFd())); }
std::vector<irc::User *> irc::Channel::getUsers()
{
	std::vector<User *> users = std::vector<User *>();

	for (std::map<int, User *>::iterator it = this->users.begin(); it != this->users.end(); ++it)
		users.push_back(it->second);
	return users;
}
std::string irc::Channel::getUsersString()
{
	std::string users = "";

	for (std::map<int, User *>::iterator it = this->users.begin(); it != this->users.end(); ++it)
	{
		if (it != this->users.begin())
			users += " ";
		if (modes[it->second->getFd()].find('o') != std::string::npos)
			users += "@";
		users += it->second->getNickname();
	}
	return users;
}

void irc::Channel::setMode(User &user, std::string mode) { modes[user.getFd()] = mode; }
std::string irc::Channel::getMode(User &user) { return modes[user.getFd()]; }
