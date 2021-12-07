#include "Server/Runtime.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return 1;
	}
	irc::Runtime runtime = irc::Runtime();
	runtime.getConfig().set("port", argv[1]);
	runtime.getConfig().set("password", argv[2]);
	runtime.run();
	return 0;
}
