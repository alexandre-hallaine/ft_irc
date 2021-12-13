#include "../Command.hpp"
#include "../../User.hpp"

void QUIT(irc::Command *command)
{
	command->getUser().deleteLater();
	//command->getParameters()[0]); need to get msg for channel
}
