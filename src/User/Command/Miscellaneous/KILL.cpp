#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void KILL(irc::Command *command)
{
	if (command->getParameters().size() == 0 || command->getTrailer().length() == 0)
		return command->reply(461, "KILL");
	if (command->getUser().getMode().find('o') == std::string::npos)
		return command->reply(481);
	irc::User *user = 0;
	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if ((*it)->getNickname() == command->getParameters()[0])
		{
			user = *it;
			break ;
		}
	}
	if (!user)
		return command->reply(401, command->getParameters()[0]);
	user->setDeleteMessage(command->getTrailer());
	user->setStatus(irc::DELETE);
}
