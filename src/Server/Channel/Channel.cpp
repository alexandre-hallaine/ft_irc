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

void irc::Channel::setMode(std::string mode) { this->mode = mode; }
void irc::Channel::setMode(User &user, std::string mode) { user_mode[user.getFd()] = mode; }
std::string irc::Channel::getMode() { return mode; }
std::string irc::Channel::getMode(User &user) { return user_mode[user.getFd()]; }
