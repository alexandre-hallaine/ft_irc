#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"

void INVITE(irc::Command *command)
{
	if (command->getParameters().size() < 2)
		return command->reply(461, "INVITE");

	if (command->getServer().getUser(command->getParameters()[0]) == NULL)
		return command->reply(401, command->getParameters()[1]);

	if (command->getServer().getChannel(command->getParameters()[0]).isOnChannel(command->getParameters()[1]))
		command->reply(443, command->getParameters()[0], command->getParameters()[1]);

	if (command->getServer().isChannel(command->getParameters()[1]))
	{
		irc::Channel &channel = command->getServer().getChannel(command->getParameters()[1]);
		if (channel.getMode().find('i') != std::string::npos && channel.getUserMode(command->getUser()).find('O') == std::string::npos && channel.getUserMode(command->getUser()).find('o') == std::string::npos && command->getUser().getMode().find('o') == std::string::npos)
		{
			command->reply(482, command->getParameters()[1]);
			return;
		}
		else if (!channel.isOnChannel(command->getUser().getNickname()))
		{
			command->reply(442, command->getParameters()[1]);
			return;
		}
		channel.addInvited(*command->getServer().getUser(command->getParameters()[0]));
	}
	command->getUser().sendTo(*command->getServer().getUser(command->getParameters()[0]), "INVITE " + command->getParameters()[0] + " " + command->getParameters()[1]);
	command->reply(341, command->getParameters()[0], command->getParameters()[1]);
	if (command->getServer().getUser(command->getParameters()[0])->getMode().find('a') != std::string::npos)
		command->reply(301, command->getParameters()[0], command->getServer().getUser(command->getParameters()[0])->getAwayMessage());
}
