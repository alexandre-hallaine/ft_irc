#include "Server/Server.hpp"
#include <iostream>
#include <csignal>

bool stop = false;

void handler(int) { stop = true; }

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return 1;
	}

	irc::Server server = irc::Server();
	signal(SIGINT, handler);

	server.getConfig().set("port", argv[1]);
	server.getConfig().set("password", argv[2]);

	server.init();
	while (!stop)
		server.execute();
	return 0;
}
