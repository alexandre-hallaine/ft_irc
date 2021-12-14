#include "../Command.hpp"
#include "../../User.hpp"

void AWAY(irc::Command *command)
{
	if (command->getParameters().size() == 0)
	{
		if (command->getUser().getMode().find('a') == std::string::npos)
			return;
		command->getUser().setMode(command->getUser().getMode().erase(command->getUser().getMode().find('a'), 1));
		return command->reply(305);
	}
	if (command->getUser().getMode().find('a') == std::string::npos)
		command->getUser().setMode(command->getUser().getMode() + 'a');
	command->getUser().setAwayMessage(command->getTrailer());
	return command->reply(306);
}
