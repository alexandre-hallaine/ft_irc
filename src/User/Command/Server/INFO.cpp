#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../../Utils/Utils.hpp"

void INFO(irc::Command *command)
{
	std::vector<std::string> motd = irc::split(command->getServer().getConfig().get("info"), "\n");
	for (std::vector<std::string>::iterator it = motd.begin(); it != motd.end(); ++it)
		command->reply(371, *it);
	command->reply(374);
}
