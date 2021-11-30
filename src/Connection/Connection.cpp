#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <poll.h>

irc::Connection::Connection(unsigned short port)
	: tcp_socket(socket(AF_INET, SOCK_STREAM, 0))
{
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	bind(tcp_socket, (struct sockaddr *)&address, sizeof(address));
	listen(tcp_socket, port);
}

struct user irc::Connection::waiting()
{
	struct sockaddr_in address;
	socklen_t csin_len = sizeof(address);
	std::cout << "waiting for a connection..." << std::endl;
	struct user user;
	user.fd = accept(tcp_socket, (struct sockaddr *)&address, &csin_len);
	user.address = address;
	return user;
}

std::string irc::read(int fd)
{
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;
	if (poll(&pfd, 1, -1) == -1)
		return std::string();
	char buffer[BUF_SIZE + 1];
	ssize_t msg_len = recv(pfd.fd, &buffer, BUF_SIZE, 0);
	buffer[msg_len] = 0;
	return std::string(buffer);
}

void irc::write(int fd, std::string str) { send(fd, str.c_str(), str.length(), 0); }

std::string irc::next(std::string &str, std::string delimiter)
{
	size_t pos = str.find(delimiter);
	if (pos == std::string::npos)
		return std::string();
	std::string tmp(str.substr(0, pos));
	str.erase(0, pos + delimiter.length());
	return tmp;
}

std::string irc::line(std::string &str) { return next(str, std::string("\r\n")); }
