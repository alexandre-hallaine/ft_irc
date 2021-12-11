#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../../Utils/Utils.hpp"

void MOTD(irc::Command *command)
{
	if (!command->getServer().getConfig().get("motd").length())
		return command->reply(422);
	command->reply(375, command->getServer().getConfig().get("name"));

	std::vector<std::string> motd = irc::split(command->getServer().getConfig().get("motd"), "\n");
	for (std::vector<std::string>::iterator it = motd.begin(); it != motd.end(); ++it)
		command->reply(372, *it);
	command->reply(376);
}
