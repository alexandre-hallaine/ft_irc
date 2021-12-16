#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"

void TOPIC(irc::Command *command)
{
	if (!command->getParameters().size())
		return command->reply(461, command->getPrefix());

	if (!command->getServer().isChannel(command->getParameters()[0]))
		return command->reply(442, command->getParameters()[0]);
	irc::Channel &channel = command->getServer().getChannel(command->getParameters()[0]);
	if (!channel.isUser(command->getUser()))
		return command->reply(442, command->getParameters()[0]);

	if (command->getQuery().find(':') != std::string::npos)
	{
		bool canEdit = false;
		if (channel.getMode().find('t') == std::string::npos)
			canEdit = true;
		else if (command->getUser().getMode().find('o') != std::string::npos)
			canEdit = true;
		else if (channel.getUserMode(command->getUser()).find('O') != std::string::npos || channel.getUserMode(command->getUser()).find('o') != std::string::npos)
			canEdit = true;

		if (!canEdit)
			return command->reply(482, channel.getName());
		channel.setTopic(command->getTrailer());
		return channel.broadcast(command->getUser(), "TOPIC " + channel.getName() + " :" + channel.getTopic());
	}

	if (!channel.getTopic().length())
		return command->reply(331, channel.getName());
	return command->reply(332, channel.getName(), channel.getTopic());
}
