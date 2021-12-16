#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"
#include <algorithm>

void NICK(irc::Command *command)
{
	if (!command->getParameters().size())
		return command->reply(431);

	if (command->getUser().getMode().find('r') != std::string::npos)
		return command->reply(484);

	std::string nickname = command->getParameters()[0];

	if (nickname.length() > 9)
		return command->reply(432, nickname);
	size_t index = 0;
	if (!irc::isLetter(nickname[index]) && !irc::isSpecial(nickname[index]))
		return command->reply(432, nickname);
	++index;
	for (; index < nickname.length(); ++index)
		if (!irc::isLetter(nickname[index]) && !irc::isSpecial(nickname[index]) && !irc::isDigit(nickname[index]) && nickname[index] != '-')
			return command->reply(432, nickname);

	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
		if (nickname == (*it)->getNickname())
			return command->reply(433, nickname);

	if (command->getUser().getNickname().length())
		command->getUser().setPastnick(" " + command->getUser().getNickname() + " " + command->getUser().getPastnick());

	std::vector<irc::User *> broadcast_users = std::vector<irc::User *>();
	broadcast_users.push_back(&command->getUser());

	std::vector<irc::Channel *> channels = command->getServer().getChannels();
	for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
		if ((*it)->isUser(command->getUser()))
		{
			std::vector<irc::User *> users = (*it)->getUsers();
			for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
				if (std::find(broadcast_users.begin(), broadcast_users.end(), *it) == broadcast_users.end())
					broadcast_users.push_back(*it);
		}

	std::string message = "NICK :" + nickname;
	for (std::vector<irc::User *>::iterator it = broadcast_users.begin(); it != broadcast_users.end(); ++it)
		command->getUser().sendTo(*(*it), message);
	command->getUser().setNickname(nickname);
}
