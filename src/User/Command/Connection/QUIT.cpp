#include "../Command.hpp"
#include "../../User.hpp"

void QUIT(irc::Command *command)
{
	if (command->getTrailer().length() > 1)
		command->getUser().setDeleteMessage(command->getTrailer());
	command->getUser().setStatus(irc::DELETE);
}
