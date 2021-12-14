#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../../Utils/Utils.hpp"

void ADMIN(irc::Command *command)
{
	command->reply(256, command->getServer().getConfig().get("name"));

	std::vector<std::string> admin = irc::split(command->getServer().getConfig().get("admin"), "\n");
	command->reply(257, admin[0]);
	command->reply(258, admin[1]);

	command->reply(259, command->getServer().getConfig().get("admin_email"));
}
