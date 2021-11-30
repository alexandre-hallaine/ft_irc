#include "Connection.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

void irc::Connection::next()
{
	struct sockaddr_in address;
	socklen_t csin_len = sizeof(address);
	int user = accept(tcp_socket, (struct sockaddr *)&address, &csin_len);
	std::cout << "new client #" << user << " from " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
}
