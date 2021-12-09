#include "Command.hpp"
#include "../User.hpp"
#include "../../utils/utils.hpp"
#include "../../Server/Server.hpp"

void PING(class irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(409);
	command->getUser().write("PONG " + command->getParameters()[0]);
}
