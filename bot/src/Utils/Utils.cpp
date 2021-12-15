#include "Utils.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <sstream>

std::string Utils::currentTime()
{
	time_t t = std::time(0);
	struct tm *now = std::localtime(&t);
	std::string time(asctime(now));
	time.erase(--time.end());
	return time;
}

void Utils::error(std::string message, bool stop)
{
	std::cerr << "error: " << message << std::endl;
	if (stop)
		exit(EXIT_FAILURE);
}

std::vector<std::string> Utils::split(std::string str, std::string delimiter)
{
	std::vector<std::string> values = std::vector<std::string>();

	size_t position;
	while ((position = str.find(delimiter)) != std::string::npos)
	{
		values.push_back(str.substr(0, position));
		str.erase(0, position + delimiter.length());
	}
	values.push_back(str);

	return values;
}

bool Utils::isLetter(char c) { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); }
bool Utils::isSpecial(char c) { return (c >= '[' && c <= '`') || (c >= '{' && c <= '}'); }
bool Utils::isDigit(char c) { return (c >= '0' && c <= '9'); }

std::string Utils::toString(size_t var)
{
	std::stringstream stream;
	stream << var;
	return stream.str();
}

bool Utils::strmatch(std::string str, std::string pattern)
{
	size_t str_size = str.size();
	size_t pattern_size = pattern.size();

	if (str_size == 0 || pattern_size == 0)
		return false;
	std::vector<std::vector<bool> > lookup(str_size + 1, std::vector<bool>(pattern_size + 1, false));
 
	lookup[0][0] = true;
 
	for (size_t j = 1; j <= pattern_size; j++)
		if (pattern[j - 1] == '*')
			lookup[0][j] = lookup[0][j - 1];
 
	for (size_t i = 1; i <= str_size; i++) {
		for (size_t j = 1; j <= pattern_size; j++) {
			if (pattern[j - 1] == '*')
				lookup[i][j] = lookup[i][j - 1] || lookup[i - 1][j];
			else if (pattern[j - 1] == '?' || str[i - 1] == pattern[j - 1])
				lookup[i][j] = lookup[i - 1][j - 1];
			else
				lookup[i][j] = false;
		}
	}
 
	return lookup[str_size][pattern_size];
}
