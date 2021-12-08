#include "Command.hpp"
#include "../User.hpp"
#include "../../Server/Server.hpp"
#include "../../utils/utils.hpp"

void MOTD(irc::Command *command);

void CAP(irc::Command *command)
{
	command->reply(1, command->getUser().getPrefix());
	command->reply(2, command->getUser().getHost(), command->getServer().getConfig().get("version"));
	command->reply(3, command->getServer().getUpTime());
	command->reply(4, command->getServer().getConfig().get("name"), command->getServer().getConfig().get("version"),
				   command->getServer().getConfig().get("user_mode"), command->getServer().getConfig().get("channel_mode"));

	MOTD(command);
}
