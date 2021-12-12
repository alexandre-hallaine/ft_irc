#include "Server/Runtime.hpp"
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

	irc::Runtime runtime = irc::Runtime();
	signal(SIGINT, handler);

	runtime.getConfig().set("port", argv[1]);
	runtime.getConfig().set("password", argv[2]);

	while (!stop)
		runtime.run();
	return 0;
}
