#include "Display.hpp"
#include "../../utils/utils.hpp"
#include <iostream>

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

irc::Display::Display()
	: lines() { update(); }

void irc::Display::setLine(unsigned char pos, std::string line)
{
	lines[pos] = line;
	update();
}
