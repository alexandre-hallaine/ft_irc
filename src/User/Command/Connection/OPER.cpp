#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void OPER(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "OPER");

	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if ((*it)->getNickname() == command->getParameters()[0] && command->getParameters().size() > 1 && command->getServer().getConfig().get("oper_password") == command->getParameters()[1])
		{
			if ((*it)->getMode().find("o") == std::string::npos)
			{
				(*it)->setMode((*it)->getMode() + "o");
				command->reply(381);
			}
			return command->reply(221, "+" + (*it)->getMode());
		}
	}
	return command->reply(464);
}
