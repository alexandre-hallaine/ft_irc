#include "User.hpp"
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sstream>

irc::User::User(int fd)
	: fd(fd), nickname("*") { fcntl(fd, F_SETFL, O_NONBLOCK); }

irc::User::~User() { close(fd); }

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
void irc::User::write(std::string query) { send(fd, query.c_str(), query.length(), 0); }
void irc::User::write(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7)
{
	std::stringstream sscode;
	sscode << code;
	std::string scode = sscode.str();
	while (scode.length() < 3)
		scode = "0" + scode;

	write(":" + hostname + " " + scode + " " + nickname + " " + generate(code, arg1, arg2, arg3, arg4, arg5, arg6, arg7) + "\r\n");
}

void irc::User::setUsername(std::string username) { this->username = username; }
void irc::User::setHostname(std::string hostname) { this->hostname = hostname; }
void irc::User::setServername(std::string servername) { this->servername = servername; }
void irc::User::setRealname(std::string realname) { this->realname = realname; }
void irc::User::setNickname(std::string nickname) { this->nickname = nickname; }
void irc::User::setMode(std::string mode) { this->mode = mode; }
std::string irc::User::getUsername() { return username; }
std::string irc::User::getHostname() { return hostname; }
std::string irc::User::getServername() { return servername; }
std::string irc::User::getRealname() { return realname; }
std::string irc::User::getNickname() { return nickname; }
std::string irc::User::getMode() { return mode; }

bool irc::User::operator==(const User &user) const { return fd == user.fd; }
