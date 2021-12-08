#include "utils.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>

std::string irc::currentTime()
{
	time_t t = std::time(0);
	struct tm *now = std::localtime(&t);
	return (asctime(now));
}

void irc::error(std::string message)
{
	std::cerr << "error: " << message << std::endl;
	exit(EXIT_FAILURE);
}
