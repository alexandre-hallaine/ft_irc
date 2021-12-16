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
		if (command->getServer().isChannel(channel))
		{
			irc::Channel &chan = command->getServer().getChannel(channel);
			if (!chan.isUser(command->getUser()))
			{
				command->reply(442, channel);
				continue;
			}
			chan.broadcast(command->getUser(), "PART " + channel + (command->getTrailer().size() ? " :" + command->getTrailer() : ""));
			chan.removeUser(command->getUser());
			if (chan.getUsers().size() == 0)
				command->getServer().delChannel(chan);
		}
		else
			command->reply(403, channel);
	}
}
