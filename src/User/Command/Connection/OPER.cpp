#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"

void OPER(irc::Command *command)
{
	if (command->getParameters().size() < 2)
		return command->reply(461, "OPER");

	if (command->getParameters()[0] != command->getServer().getConfig().get("oper_user"))
		return command->reply(464);
	if (command->getParameters()[1] != command->getServer().getConfig().get("oper_password"))
		return command->reply(464);

	command->reply(381);
	if (command->getUser().getMode().find('o') == std::string::npos)
	{
		command->getUser().setMode(command->getUser().getMode() + "o");
		command->reply(221, "+" + command->getUser().getMode());
	}
}
