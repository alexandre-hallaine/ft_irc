#include "Display.hpp"
#include "../../utils/utils.hpp"
#include <iostream>
#include <sstream>

void irc::Display::clearScreen() { std::cout << "\033[2J" << std::flush; }

void irc::Display::update()
{
	if (DEBUG)
		return;

	clearScreen();

	std::map<unsigned char, std::string>::iterator it = lines.begin();
	std::map<unsigned char, std::string>::iterator ite = lines.end();
	while (it != ite)
	{
		std::cout << it->second << "\033[0m" << std::endl;
		it++;
	}
}
void irc::Display::write(unsigned char pos, std::string prefix, std::string line)
{
	std::stringstream ss;
	ss << prefix << line;
	write(pos, ss.str());
}

irc::Display::Display()
	: lines() { update(); }

void irc::Display::write(unsigned char pos, std::string line)
{
	lines[pos] = line;
	update();
}
void irc::Display::warning(unsigned char pos, std::string line) { write(pos, "\033[0;33mWarning ", line); }
void irc::Display::error(unsigned char pos, std::string line) { write(pos, "\033[0;31mError ", line); }
