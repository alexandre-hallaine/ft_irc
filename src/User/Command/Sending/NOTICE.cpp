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
			users = command->getServer().getChannel(recipient).getUsers();
			std::vector<irc::User *>::iterator it = std::find(users.begin(), users.end(), &command->getUser());
			if (it != users.end())
				users.erase(it);
		}
		else
			return;
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
			return;
	}

	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
		if ((*it)->getMode().find('a') == std::string::npos)
		{
			(*it)->write(":" + command->getUser().getPrefix() + " NOTICE " + recipient + " :" + command->getTrailer());
			(*it)->push();
		}
}
