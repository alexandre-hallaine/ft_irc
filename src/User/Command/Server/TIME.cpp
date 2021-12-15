#include "../Command.hpp"
#include "../../../Server/Server.hpp"

void TIME(irc::Command *command)
{
	time_t get_time;
	time(&get_time);

	command->reply(391, command->getServer().getConfig().get("name"), ctime(&get_time));
}
