#include "Command.hpp"
#include "../../Server/Server.hpp"
#include "../../utils/utils.hpp"

void MOTD(irc::Command *command)
{
	if (!command->getServer().getConfig().get("motd").length())
		return command->reply(422);
	command->reply(375, command->getServer().getConfig().get("name"));

	std::vector<std::string> motd = irc::split(command->getServer().getConfig().get("motd"), "\n");
	std::vector<std::string>::iterator it = motd.begin();
	std::vector<std::string>::iterator ite = motd.end();
	while (it != ite)
	{
		command->reply(372, *it);
		++it;
	}
	command->reply(376);
}
