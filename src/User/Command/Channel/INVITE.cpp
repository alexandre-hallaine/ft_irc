#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"

void INVITE(irc::Command *command)
{
	if (command->getParameters().size() < 2)
	{
		command->reply(461, "INVITE");
		return;
	}
	if (command->getServer().isUser(command->getParameters()[1]))
	{
		command->reply(401, command->getParameters()[1]);
		return;
	}
	if (command->getServer().getChannel(command->getParameters()[0]).isOnChannel(command->getParameters()[1]))
	{
		command->reply(443, command->getParameters()[0], command->getParameters()[1]);
		return;
	}
	if (command->getServer().isChannel(command->getParameters()[1]))
	{
		irc::Channel &channel = command->getServer().getChannel(command->getParameters()[1]);
		if (channel.getMode().find('i') != std::string::npos && channel.getUserMode(command->getUser()).find('O') == std::string::npos)
		{
			command->reply(482, command->getParameters()[1]);
			return;
		}
		else if (!channel.isOnChannel(command->getUser().getNickname()))
		{
			command->reply(442, command->getParameters()[1]);
			return;
		}
	}
	command->getServer().sendOne(command->getUser(), "INVITE " + command->getParameters()[0] + command->getParameters()[1]);
	command->reply(341, command->getParameters()[0], command->getParameters()[1]);
}
