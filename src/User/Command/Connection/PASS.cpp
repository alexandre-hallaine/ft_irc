#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void PASS(irc::Command *command)
{
	if (!command->getParameters().size())
		return command->reply(461);
	if (command->getUser().getStatus() != irc::PASSWORD)
		return command->reply(462);

	if (command->getServer().getConfig().get("password") == command->getParameters()[0])
		command->getUser().setStatus(irc::REGISTER);
}
