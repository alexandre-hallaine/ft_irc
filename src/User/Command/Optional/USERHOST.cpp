#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void USERHOST(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "USERHOST");

	//command->reply(302, ((*it)->getNickname() + "=+~" + (*it)->getUsername() + "@" + (*it)->getHost()));
}
