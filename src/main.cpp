#include "Server/Server.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
	if (argc < 3 || argc > 4)
	{
		std::cout << "./ircserv [host:port_network:password_network] <port> <password>" << std::endl;
		return 1;
	}
	irc::Server(atoi(argv[argc - 2]), argv[argc - 1]).run();
	return 0;
}
