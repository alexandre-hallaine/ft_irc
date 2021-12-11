#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void ISON(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "USERHOST");

	std::string ison = ""; 
	std::vector<irc::User *> users = command->getServer().getUsers();
	for (size_t i = 0; i != command->getParameters().size(); i++)
		for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it ++)
			if ((*it)->getNickname() == command->getParameters()[i])
				ison += (*it)->getNickname() + " ";
	command->reply(303, ison);
}
