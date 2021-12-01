#include "Server/Server.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return 1;
	}
	irc::Server(atoi(argv[1]), argv[2]).run();
	return 0;
}
