#include "../Command.hpp"

void USERS(irc::Command *command)
{
	command->reply(446, "Command USERS is disabled for safety reasons");
}
