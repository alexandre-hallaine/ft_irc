#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"
#include <algorithm>

void PRIVMSG(irc::Command *command)
{
	if (!command->getParameters().size())
		return command->reply(411);
	if (!command->getTrailer().length())
		return command->reply(412);

	std::string recipient = command->getParameters()[0];
	std::vector<irc::User *> users;

	if (*recipient.begin() == '#')
		if (command->getServer().isChannel(recipient))
		{
			irc::Channel &channel = command->getServer().getChannel(recipient);

			if (channel.getMode().find('n') != std::string::npos)
				if (!channel.isUser(command->getUser()))
					return command->reply(404, channel.getName());

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
					return command->reply(404, channel.getName());
			}

			users = channel.getUsers();
			std::vector<irc::User *>::iterator it = std::find(users.begin(), users.end(), &command->getUser());
			if (it != users.end())
				users.erase(it);
		}
		else
			return command->reply(404, recipient);
	else
	{
		if (command->getServer().getUser(recipient))
			users.push_back(command->getServer().getUser(recipient));
		else
			return command->reply(401, recipient);
	}

	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if ((*it)->getMode().find('a') != std::string::npos)
			command->reply(301, (*it)->getNickname(), (*it)->getAwayMessage());
		command->getUser().sendTo(*(*it), "PRIVMSG " + recipient + " :" + command->getTrailer());
	}
}
