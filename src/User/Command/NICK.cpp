#include "Command.hpp"
#include "../User.hpp"
#include "../../utils/utils.hpp"
#include "../../Server/Server.hpp"
#include <iostream>

void NICK(irc::Command *command)
{
	if (!command->getParameters().size())
		return command->reply(431);
	const char *nickname = command->getParameters()[0].c_str();

	//check valid nick
	std::cout << 1 << std::endl;
	if (command->getParameters()[0].length() > 9)
		return command->reply(432, nickname);
	size_t index = 0;
	std::cout << 2 << std::endl;
	if (!irc::isLetter(nickname[index]) && !irc::isSpecial(nickname[index]))
		return command->reply(432, nickname);
	++index;
	while (index < command->getParameters()[0].length())
	{
		std::cout << 3 << std::endl;
		if (!irc::isLetter(nickname[index]) && !irc::isSpecial(nickname[index]) && !irc::isDigit(nickname[index]) && nickname[index] != '-')
			return command->reply(432, nickname);
		++index;
	}

	std::vector<irc::User *> users = command->getServer().getUsers();
	std::vector<irc::User *>::iterator it = users.begin();
	std::vector<irc::User *>::iterator ite = users.end();
	while (it != ite)
	{
		if (nickname == (*it)->getNickname())
			return command->reply(433, nickname);
		++it;
	}

	command->getUser().setNickname(command->getParameters()[0]);
	command->getUser().write(":" + command->getUser().getPrefix() + " NICK " + nickname);
}
