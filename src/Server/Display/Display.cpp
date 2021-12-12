#include "Display.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>

void irc::Display::clearScreen() { std::cout << "\033[2J" << std::flush; }

void irc::Display::update()
{
	if (DEBUG)
		return;

	clearScreen();

	for (std::map<unsigned char, std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
		std::cout << it->second << "\033[0m" << std::endl;
}

irc::Display::Display() { update(); }

void irc::Display::set(unsigned char pos, std::string line)
{
	if (lines[pos] == line)
		return;
	lines[pos] = line;
	update();
}
void irc::Display::remove(unsigned char pos)
{
	lines.erase(pos);
	update();
}
