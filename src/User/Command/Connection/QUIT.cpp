#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void QUIT(irc::Command *command)
{
	command->getServer().quitUser(command->getUser());
	//command->getParameters()[0]); need to get msg for channel
}
