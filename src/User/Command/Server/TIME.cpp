#include "../Command.hpp"
#include "../../../Server/Server.hpp"

void TIME(irc::Command *command)
{
	std::string now;
	time_t get_time;

	time(&get_time);
	now = ctime(&get_time);
	command->reply(391, command->getServer().getConfig().get("name"), now);
}
