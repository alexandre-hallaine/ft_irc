#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"
#include <algorithm>

void QUIT(irc::Command *command)
{
	if (command->getParameters().size() > 1)
		command->getUser().setDeleteMessage(command->getParameters()[1]);
	else
		command->getUser().setDeleteMessage("Client Quit");
}
