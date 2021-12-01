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

void irc::User::setNickname(std::string nick) { nickname = nick; }
std::string irc::User::getNickname() { return nickname; }
