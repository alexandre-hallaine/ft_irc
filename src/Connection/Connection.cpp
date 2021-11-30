#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>

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

struct user irc::Connection::next()
{
	struct sockaddr_in address;
	socklen_t csin_len = sizeof(address);
	std::cout << "waiting for a connection..." << std::endl;
	struct user user;
	user.fd = accept(tcp_socket, (struct sockaddr *)&address, &csin_len);
	user.address = address;
	return user;
}
