#include "../Command.hpp"
#include "../../User.hpp"

void QUIT(irc::Command *command)
{
	if (command->getParameters().size() > 1)
		command->getUser().setDeleteMessage(command->getParameters()[1]);
	else
		command->getUser().setDeleteMessage("Client Quit");
	command->getUser().setStatus(irc::DELETE);
}
