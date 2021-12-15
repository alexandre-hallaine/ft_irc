#include "../Command.hpp"
#include "../../User.hpp"
#include <ctime>

void PONG(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(409);
	command->getUser().setLastPing(std::time(0));
}
