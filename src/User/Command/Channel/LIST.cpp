#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../User.hpp"
#include <iostream>

void LIST(irc::Command *command)
{
	std::vector<irc::Channel *> channels = command->getServer().getChannels();
	if (command->getParameters().size() == 1 && command->getParameters()[0] != "")
	{
		for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
			if (irc::strmatch((*it)->getName(), command->getParameters()[0]))
				command->reply(322, (*it)->getName(), (*it)->getTopic());
	}
	else
		for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
			command->reply(322, (*it)->getName(), (*it)->getTopic());
	command->reply(323);
}
