#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"

void WHOWAS(class irc::Command *command)
{
	size_t pos = 0, tmp = 0, count = 0;
	bool has_print = false, has_count = false;

	if (command->getParameters().size() == 0)
		return command->reply(431);

	if (command->getParameters().size() > 1)
	{
		for (size_t index = 0; index != command->getParameters()[1].length(); index++)
		{
			if (!irc::isDigit(command->getParameters()[1][index]))
				break ;
			count += count * 10;
			count += command->getParameters()[1][index] - 48;
			has_count = true;
		}
	}
	
	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if (!has_count || (has_count && count != 0))
		{
			while ((tmp = (*it)->getPastnick().find(command->getParameters()[0], pos)) != std::string::npos)
			{
				command->reply(314, command->getParameters()[0], (*it)->getUsername(), (*it)->getHostname(), (*it)->getRealname());
				has_print = true;
				if (has_count && count != 0)
					count--;
				if (has_count && count == 0)
					break ;
				pos = tmp + 1;
			}
			pos = 0, tmp = 0;
		}
		else
			break ;
	}

	if (!has_print)
		command->reply(406, command->getParameters()[0]);
	return command->reply(369, command->getParameters()[0]);
}
