#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void WALLOPS(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "WALLOPS");
	if (command->getUser().getMode().find('o') == std::string::npos)
		return;

	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
		if ((*it)->getMode().find("w") != std::string::npos)
			command->getUser().sendTo(*(*it), "WALLOPS :" + command->getTrailer());
}
