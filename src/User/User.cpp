#include "User.hpp"
#include <poll.h>
#include <sys/socket.h>

irc::User::User(int fd)
	: fd(fd), nickname() {}

std::string irc::User::read()
{
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;
	if (poll(&pfd, 1, 50) == -1)
		return std::string();
	char buffer[BUFFER_SIZE + 1];
	ssize_t msg_len = recv(pfd.fd, &buffer, BUFFER_SIZE, 0);
	if (msg_len == -1)
		return std::string();
	buffer[msg_len] = 0;
	return std::string(buffer);
}
void irc::User::write(std::string str) { send(fd, str.c_str(), str.length(), 0); }

void irc::User::setUsername(std::string username) { this->username = username; }
void irc::User::setHostname(std::string hostname) { this->hostname = hostname; }
void irc::User::setServername(std::string servername) { this->servername = servername; }
void irc::User::setRealname(std::string realname) { this->realname = realname; }
void irc::User::setNickname(std::string nickname) { this->nickname = nickname; }
std::string irc::User::getUsername() { return username; }
std::string irc::User::getHostname() { return hostname; }
std::string irc::User::getServername() { return servername; }
std::string irc::User::getRealname() { return realname; }
std::string irc::User::getNickname() { return nickname; }
