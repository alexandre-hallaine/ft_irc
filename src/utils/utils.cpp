#include "utils.hpp"
#include <ctime>

std::string irc::currentTime()
{
	time_t t = std::time(0);
	struct tm *now = std::localtime(&t);
	return (asctime(now));
}
