#include "CommandsBook.hpp"
#include <iostream>

irc::CommandsBook::CommandsBook()
	: map()
{
	map["CAP"] = &CAP;
}

void irc::CommandsBook::call(std::string name, std::string args)
{
	if (name.empty())
		return;
	if (map.count(name))
		map[name](args);
	else
		std::cout << "Unknown command: " << name << std::endl;
}
