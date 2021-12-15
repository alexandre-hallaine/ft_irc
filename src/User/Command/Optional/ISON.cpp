#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"
#include "../../../Utils/Utils.hpp"
#include <algorithm>

void ISON(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "USERHOST");

	std::vector<std::string> nicknames = irc::split(command->getTrailer(), " ");
	std::string ison = "";
	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
		if (std::find(nicknames.begin(), nicknames.end(), (*it)->getNickname()) != nicknames.end())
			ison += (*it)->getNickname() + " ";
	command->reply(303, ison);
}
