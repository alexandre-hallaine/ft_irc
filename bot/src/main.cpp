#include "bot.hpp"
#include <csignal>

bool sig = false;

void handler(int) { sig = true; }

int main(int argc, char **argv)
{
	try {
		signal(SIGINT, handler);
		if (argc == 2)
		{
			Bot bot(&sig, argv[1]);
			bot.run();
		}
		else if (argc == 3)
		{
			Bot bot(&sig, argv[1], atoi(argv[2]));
			bot.run();
		}
		else if (argc == 4)
		{
			Bot bot(&sig, argv[1], atoi(argv[2]), argv[3]);
			bot.run();
		}
		else if (argc == 5)
		{
			Bot bot(&sig, argv[1], atoi(argv[2]), argv[3], argv[4]);
			bot.run();
		}
		else
		{
			std::cout << "./bot <host> [port] [password] [nick]" << std::endl;
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		if (std::string(e.what()) == "Connection closed")
			return EXIT_SUCCESS;
		return EXIT_FAILURE;
	}
}
