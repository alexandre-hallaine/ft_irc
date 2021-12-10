#include "Command.hpp"
#include "../User.hpp"
#include "../../utils/utils.hpp"
#include "../../Server/Server.hpp"

void WHOIS(class irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(431);

	std::vector<irc::User *>users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
		if (command->getParameters()[0] == (*it)->getNickname())
		{
			//need to check for channels
			command->reply(311, command->getParameters()[0], command->getUser().getUsername(), command->getUser().getHostname(), command->getUser().getRealname());
			return command->reply(318, command->getParameters()[0]);
		}

	return command->reply(401, command->getParameters()[0]);
}
