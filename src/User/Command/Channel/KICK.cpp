#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../User.hpp"

void KICK(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "KICK");

	std::vector<std::string> channels = irc::split(command->getParameters()[0], ",");
	std::vector<std::string> users = irc::split(command->getParameters()[1], ",");
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (!command->getServer().isChannel(*it))
		{
			command->reply(403, *it);
			continue;
		}
		irc::Channel &channel = command->getServer().getChannel(*it);
		if (channel.getUserMode(command->getUser()).find('O') == std::string::npos && channel.getUserMode(command->getUser()).find('o') == std::string::npos && command->getUser().getMode().find('o') == std::string::npos)
		{
			command->reply(482, *it);
			continue;
		}
		for (std::vector<std::string>::iterator it2 = users.begin(); it2 != users.end(); ++it2)
		{
			if (!channel.isOnChannel(*it2))
			{
				command->reply(441, *it2, *it);
				continue;
			}
			channel.broadcast(command->getUser(), "KICK " + *it + " " + *it2 + " :" + command->getParameters()[2]);
			channel.removeUser(*it2);
		}
	}
}
