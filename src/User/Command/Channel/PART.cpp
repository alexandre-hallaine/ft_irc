#include "../Command.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"

void PART(irc::Command *command)
{
	if (command->getParameters().size() == 0)
	{
		command->reply(461, "PART");
		return;
	}
	std::vector<std::string> channels = irc::split(command->getParameters()[0], ",");
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::string &channel = *it;
		if (channel.size() == 0)
			continue;
		if (channel[0] != '#')
			channel = "#" + channel;
		if (command->getServer().isChannel(channel))
		{
			irc::Channel &chan = command->getServer().getChannel(channel);
			if (!chan.isMember(command->getUser()))
			{
				command->reply(442, channel);
				continue;
			}
			chan.write(&command->getUser(), ":" + command->getUser().getPrefix() + " PART " + channel + (command->getParameters().size() > 1 ?  " :" + command->getParameters()[1] : ""));
			chan.removeUser(command->getUser());
			if (chan.getUsers().size() == 0)
				command->getServer().delChannel(chan);
		}
		else
			command->reply(403, channel);
	}
}
