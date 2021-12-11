#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"

void PRIVMSG(irc::Command *command)
{
	std::string recipient = command->getParameters()[0];
	if (*recipient.begin() == '#')
	{
		irc::Channel channel = command->getServer().getChannel(recipient);
		std::vector<irc::User *> users = channel.getUsers();
		for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
			if ((*it)->getFd() != command->getUser().getFd())
			{
				(*it)->write(":" + command->getUser().getPrefix() + " PRIVMSG " + recipient + " :" + command->getTrailer());
				(*it)->push();
			}
	}
}
