#include "Channel.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../User.hpp"

irc::Channel::Channel(std::string const &name) : name(name) {}

irc::Channel::~Channel() {}

void irc::Channel::addUser(irc::User *user) {
	users.insert(std::make_pair(user->getUsername(), user));
}

void irc::Channel::removeUser(irc::User *user) {
	users.erase(user->getUsername());
}
