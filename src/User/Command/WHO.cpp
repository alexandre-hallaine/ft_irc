#include "Command.hpp"
#include "../User.hpp"
#include "../../utils/utils.hpp"
#include "../../Server/Server.hpp"

void WHO(class irc::Command *command)
{
	//missing is hostname
	bool is_star = false;
	size_t pos = 0;

	if ((pos = command->getParameters()[0].find("*")) != std::string::npos)
		is_star = true;

	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
	{	// need to check channel first
		if ("missing" == command->getParameters()[0] || (*it)->getRealname() == command->getParameters()[0] || (*it)->getNickname() == command->getParameters()[0])
			command->reply(352, "*", command->getUser().getUsername(), command->getUser().getHost(), "missing", command->getUser().getNickname(), "0", command->getUser().getRealname());
		else if (is_star && (command->getParameters()[0].substr(0, pos) == std::string("missing").substr(0, pos) || command->getParameters()[0].substr(0, pos) == (*it)->getRealname().substr(0, pos) || command->getParameters()[0].substr(0, pos) == (*it)->getNickname().substr(0, pos) ))
			command->reply(352, "*", command->getUser().getUsername(), command->getUser().getHost(), "missing", command->getUser().getNickname(), "0", command->getUser().getRealname());
	}
	command->reply(315, command->getUser().getUsername());
}
