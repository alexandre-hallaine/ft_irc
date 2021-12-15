#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"

void WHOIS(class irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(431);

	std::string channels_names;
	std::vector<irc::Channel *> channels = command->getServer().getChannels();

	std::vector<irc::User *>users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
		if (command->getParameters()[0] == (*it)->getNickname())
		{
			command->reply(311, command->getParameters()[0], command->getUser().getUsername(), command->getUser().getHostname(), command->getUser().getRealname());
			for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
				if ((*it)->isOnChannel(command->getParameters()[0]))
					channels_names += (*it)->getName() + " ";
			if (channels_names.length())
				command->reply(319, command->getParameters()[0], channels_names);
			if ((*it)->getMode().find('o') != std::string::npos)
				command->reply(313, (*it)->getNickname());
			return command->reply(318, command->getParameters()[0]);
		}

	command->reply(401, command->getParameters()[0]);
	return command->reply(318, command->getParameters()[0]);
}
