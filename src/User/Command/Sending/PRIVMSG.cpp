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
			users = command->getServer().getChannel(recipient).getUsers();
			std::vector<irc::User *>::iterator it = std::find(users.begin(), users.end(), &command->getUser());
			if (it != users.end())
				users.erase(it);
		}
		else
			return command->reply(404);
	else
	{
		std::vector<irc::User *> all_users = command->getServer().getUsers();
		for (std::vector<irc::User *>::iterator it = all_users.begin(); it != all_users.end(); ++it)
			if ((*it)->getNickname() == recipient)
			{
				users.push_back(*it);
				break;
			}
		if (!users.size())
			return command->reply(401, recipient);
	}

	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
		if ((*it)->getMode().find('a') != std::string::npos)
			command->reply(301);
		else
		{
			(*it)->write(":" + command->getUser().getPrefix() + " PRIVMSG " + recipient + " :" + command->getTrailer());
			(*it)->push();
		}
}
