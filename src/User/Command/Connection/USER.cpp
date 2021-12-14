#include "../Command.hpp"
#include "../../User.hpp"

void USER(irc::Command *command)
{
	if (command->getParameters().size() < 3)
		return command->reply(461, command->getPrefix());
	if (command->getUser().getStatus() != irc::REGISTER)
		return command->reply(462);

	command->getUser().setUsername(command->getParameters()[0]);
	command->getUser().setRealname(command->getTrailer());
}
