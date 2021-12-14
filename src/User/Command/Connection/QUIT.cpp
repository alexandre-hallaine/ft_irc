#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"
#include <algorithm>
#include <iostream>

void QUIT(irc::Command *command)
{
	std::string message = ":" + command->getUser().getPrefix() + " QUIT :";
	if (command->getParameters().size() > 1)
		message += command->getParameters()[1];
	else
		message += "Client Quit";

	std::vector<irc::User *> broadcast_users = std::vector<irc::User *>();
	std::vector<irc::Channel *> channels = command->getServer().getChannels();
	for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
		if ((*it)->isUser(command->getUser()))
		{
			std::vector<irc::User *> users = (*it)->getUsers();
			for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
				if (std::find(broadcast_users.begin(), broadcast_users.end(), *it) == broadcast_users.end())
					broadcast_users.push_back(*it);
		}

	for (std::vector<irc::User *>::iterator it = broadcast_users.begin(); it != broadcast_users.end(); ++it)
	{
		(*it)->write(message);
		if ((*it)->getFd() != command->getUser().getFd())
			(*it)->push();
	}
	command->getUser().deleteLater();
}
