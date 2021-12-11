#include "Channel.hpp"
#include "../Command.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"

void JOIN(irc::Command *command)
{
	if (command->getParameters().size() == 0)
	{
		command->reply(461, "JOIN", "Not enough parameters");
		return;
	}
	std::vector<std::string> channelsNames = irc::split(command->getParameters()[0], ",");
	for (std::vector<std::string>::iterator it = channelsNames.begin(); it != channelsNames.end(); ++it)
	{
		std::string channelName = *it;
		if (channelName.size() == 0)
			continue;
		if (channelName[0] != '#')
			channelName = "#" + channelName;
		if (command->getServer().getChannel(channelName) == NULL)
		{
			command->getServer().addChannel(channelName);
			command->getServer().getChannel(channelName)->addUser(&command->getUser());
			//command->reply(353, "=" + command->getUser()->getNickname() + channelName + ":" + command->getUser()->getNickname());
			command->reply(366, channelName, "End of /NAMES list");
		}
		else
			command->getServer().getChannel(channelName)->addUser(&command->getUser());
	}
}
