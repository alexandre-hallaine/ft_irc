#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"
#include <algorithm>

void NOTICE(irc::Command *command)
{
	if (!command->getParameters().size())
		return;
	if (!command->getTrailer().length())
		return;

	std::string recipient = command->getParameters()[0];
	std::vector<irc::User *> users;

	if (*recipient.begin() == '#')
		if (command->getServer().isChannel(recipient))
		{
			irc::Channel &channel = command->getServer().getChannel(recipient);

			if (channel.getMode().find('n') != std::string::npos)
				if (!channel.isUser(command->getUser()))
					return;

			if (channel.getMode().find('m') != std::string::npos)
			{
				if (command->getUser().getMode().find('o') != std::string::npos)
					;
				else if (channel.getUserMode(command->getUser()).find('O') != std::string::npos)
					;
				else if (channel.getUserMode(command->getUser()).find('o') != std::string::npos)
					;
				else if (channel.getUserMode(command->getUser()).find('v') != std::string::npos)
					;
				else
					return;
			}

			users = channel.getUsers();
			std::vector<irc::User *>::iterator it = std::find(users.begin(), users.end(), &command->getUser());
			if (it != users.end())
				users.erase(it);
		}
		else
			return;
	else
	{
		if (command->getServer().getUser(recipient))
			users.push_back(command->getServer().getUser(recipient));
		else
			return;
	}

	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
		command->getUser().sendTo(*(*it), "NOTICE " + recipient + " :" + command->getTrailer());
}
