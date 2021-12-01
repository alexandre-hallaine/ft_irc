#include "User.hpp"

irc::User::User()
	: fd(), address() {}
irc::User::User(int fd, struct sockaddr_in address)
	: fd(fd), address(address) {}
irc::User::User(const User &other)
	: fd(other.fd), address(other.address), nick(other.nick) {}
irc::User &irc::User::operator=(const User &other)
{
	if (&other != this)
	{
		fd = other.fd;
		address = other.address;
		nick = other.nick;
	}
	return *this;
}

void irc::User::setNick(std::string nick) { this->nick = nick; }

int irc::User::getFd() { return fd; }
struct sockaddr_in irc::User::getAddress() { return address; }
std::string irc::User::getNick() { return nick; }
