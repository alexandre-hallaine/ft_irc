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
bool irc::Channel::isMember(User &user) { return users.find(user.getFd()) != users.end(); }

void irc::Channel::setMode(std::string mode) { this->mode = mode; }
std::string irc::Channel::getMode() { return mode; }

void irc::Channel::setUserMode(User &user, std::string mode) { user_mode[user.getFd()] = mode; }
std::string irc::Channel::getUserMode(User &user) { return user_mode[user.getFd()]; }

void irc::Channel::setKey(std::string key) { this->key = key; }
std::string irc::Channel::getKey() { return key; }

void irc::Channel::setMaxUsers(std::string max_users) { this->max_users = max_users; }
std::string irc::Channel::getMaxUsers() { return max_users; }

void irc::Channel::broadcast(User &user, std::string message)
{
	message = ":" + user.getPrefix() + " " + message;
	for (std::map<int, User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		it->second->write(message);
		if (it->first != user.getFd())
			it->second->push();
	}
}
