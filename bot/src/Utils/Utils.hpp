#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

namespace Utils
{
	std::string currentTime();

	void error(std::string message, bool stop);

	std::vector<std::string> split(std::string str, std::string delimiter);

	bool isLetter(char c);
	bool isSpecial(char c);
	bool isDigit(char c);

	std::string toString(size_t var);

	bool strmatch(std::string str, std::string pattern);
}
#endif
