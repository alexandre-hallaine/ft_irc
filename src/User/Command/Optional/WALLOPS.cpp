#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"
#include <iostream>

void WALLOPS(irc::Command *command) 
{
	if (command->getTrailer() == "")
		return command->reply(461, "WALLOPS");

	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if ((*it)->getMode().find("w") != std::string::npos)
			(*it)->write(command->getTrailer());
	}
}
