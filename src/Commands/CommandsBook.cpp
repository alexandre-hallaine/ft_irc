#include "CommandsBook.hpp"
#include <iostream>

irc::CommandsBook::CommandsBook()
	: map()
{
	map["CAP"] = &CAP;
	map["NICK"] = &NICK;
	map["USER"] = &USER;
	map["JOIN"] = &JOIN;
	map["PART"] = &PART;
	map["PRIVMSG"] = &PRIVMSG;
}

void irc::CommandsBook::call(std::string name, std::string args, User *user)
{
	if (name.empty())
		return;
	if (DEBUG)
		std::cout << "cmd: " << name << ", args: " << args << std::endl;
	if (map.count(name))
		map[name](args, user);
	else
		std::cout << "Unknown command: " << name << std::endl;
}
