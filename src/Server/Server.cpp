#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <sstream>

void irc::Server::pending()
{
	struct pollfd pfd;
	pfd.fd = tcp_socket;
	pfd.events = POLLIN;
	poll(&pfd, 1, -1);
}
void irc::Server::displayUsers()
{
	std::stringstream ss;
	ss << "Users: " << users.size();
	display.setLine(1, ss.str());
}
void irc::Server::registerUsers()
{
	if (users.empty())
	{
		display.setLine(1, "No user, waiting for a connection...");
		pending();
	}
	while (true)
	{
		struct sockaddr_in address;
		socklen_t csin_len = sizeof(address);
		int fd = accept(tcp_socket, (struct sockaddr *)&address, &csin_len);
		if (fd == -1)
			break;
		users.push_back(new User(fd));
		displayUsers();
	}
}

irc::Server::Server(unsigned short port, std::string password)
	: tcp_socket(socket(AF_INET, SOCK_STREAM, 0)), users(), display(), channels(display), packet(channels, *this)
{
	(void)password;
	display.setLine(0, "Welcome to our IRC!");

	fcntl(tcp_socket, F_SETFL, O_NONBLOCK);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	bind(tcp_socket, (struct sockaddr *)&address, sizeof(address));
	listen(tcp_socket, port);
}
irc::Server::~Server()
{
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	while (it != ite)
		delete *it;
}

void irc::Server::run()
{
	while (true)
	{
		registerUsers();

		std::vector<User *>::iterator it = users.begin();
		std::vector<User *>::iterator ite = users.end();
		while (it != ite)
		{
			packet.request((*it)->read(), *it);
			it++;
		}
	}
}
void irc::Server::kill(User *user)
{
	std::vector<User *>::iterator it = users.begin();
	std::vector<User *>::iterator ite = users.end();
	while (it != ite)
	{
		if (*it == user)
		{
			users.erase(it);
			delete *it;
			displayUsers();
			return;
		}
		it++;
	}
}
