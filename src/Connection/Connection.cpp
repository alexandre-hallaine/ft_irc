#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <poll.h>
#include <fcntl.h>

irc::Connection::Connection(unsigned short port)
	: tcp_socket(socket(AF_INET, SOCK_STREAM, 0))
{
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	fcntl(tcp_socket, F_SETFL, O_NONBLOCK);
	bind(tcp_socket, (struct sockaddr *)&address, sizeof(address));
	listen(tcp_socket, port);
}

irc::User irc::Connection::waiting()
{
	struct sockaddr_in address;
	socklen_t csin_len = sizeof(address);
	User user(accept(tcp_socket, (struct sockaddr *)&address, &csin_len), address);
	fcntl(user.getFd(), F_SETFL, O_NONBLOCK);
	return user;
}

irc::User irc::Connection::force_waiting()
{
	struct pollfd pfd;
	pfd.fd = tcp_socket;
	pfd.events = POLLIN;
	poll(&pfd, 1, -1);
	return waiting();
}

std::string irc::read(int fd)
{
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;
	if (poll(&pfd, 1, 50) == -1)
		return std::string();
	char buffer[BUF_SIZE + 1];
	ssize_t msg_len = recv(pfd.fd, &buffer, BUF_SIZE, 0);
	if (msg_len == -1)
		return std::string();
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
