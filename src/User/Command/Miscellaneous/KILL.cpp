#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void KILL(irc::Command *command)
{
	if (command->getParameters().size() == 0 || command->getTrailer().length() == 0)
		return command->reply(461, "KILL");
	if (command->getUser().getMode().find('o') == std::string::npos)
		return command->reply(481);

	irc::User *user = command->getServer().getUser(command->getParameters()[0]);
	if (!user)
		return command->reply(401, command->getParameters()[0]);
	user->setDeleteMessage(command->getTrailer());
	user->setStatus(irc::DELETE);
	command->getUser().sendTo(*user, "KILL :" + command->getTrailer());
}
