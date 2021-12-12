#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void USERHOST(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "USERHOST");

	size_t len = (command->getParameters().size() > 5) ? 5 : command->getParameters().size();
	std::vector<irc::User *> users = command->getServer().getUsers();
	for (size_t i = 0; i != len; i++)
		for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
			if ((*it)->getNickname() == command->getParameters()[i])
			{
				command->reply(302, ((*it)->getNickname() + "=+~" + (*it)->getUsername() + "@" + (*it)->getHost()));
				break;
			}
}
