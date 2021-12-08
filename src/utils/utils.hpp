#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

#ifndef DEBUG
#define DEBUG 0
#endif

namespace irc
{
	std::string currentTime();
	void error(std::string message);
}
#endif
