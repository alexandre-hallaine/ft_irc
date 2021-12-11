#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"

void WHOWAS(class irc::Command *command)
{
	size_t pos = 0, tmp = 0;
	bool has_print = false;

	if (command->getParameters().size() == 0)
		return command->reply(431);

	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		while ((tmp = (*it)->getPastnick().find(command->getParameters()[0], pos)) != std::string::npos)
		{
			command->reply(314, command->getParameters()[0], (*it)->getUsername(), (*it)->getHostname(), (*it)->getRealname());
			pos = tmp + 1;
			has_print = true;
		}
		pos = 0, tmp = 0;
	}

	if (!has_print)
		return command->reply(406, command->getParameters()[0]);
	return command->reply(369);
}
