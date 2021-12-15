#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"

void WHO(class irc::Command *command)
{
	bool is_star = false;
	bool is_op = false;
	size_t pos = 0;

	if (command->getParameters().size() == 0)
		return ;
	
	if ((pos = command->getParameters()[0].find("*")) != std::string::npos)
		is_star = true;
	
	if (command->getParameters().size() > 1 && command->getParameters()[1] == "o")
		is_op = true;

	std::vector<irc::User *> users = command->getServer().getUsers();

	if (command->getParameters()[0][0] == '#')
	{
		if (!command->getServer().isChannel(command->getParameters()[0]))
			command->reply(315, command->getUser().getUsername());

		irc::Channel channel = command->getServer().getChannel(command->getParameters()[0]);

		for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
		{
			if (channel.isOnChannel((*it)->getNickname()))
			{
				if (command->getUser().getMode().find('o') == std::string::npos && (*it)->getMode().find('i') != std::string::npos)
					continue;
				std::string state;
				if ((*it)->getMode().find('a') != std::string::npos)
					state = "G";
				else
					state = "H";
				if ((*it)->getMode().find('o') != std::string::npos)
					state += "@";
				if (is_op && (*it)->getMode().find('o') != std::string::npos)
					command->reply(352, (*it)->getLastChannel(), (*it)->getUsername(), (*it)->getHostname(), "", (*it)->getNickname(), state, (*it)->getRealname());
				else if (!is_op)
					command->reply(352, (*it)->getLastChannel(), (*it)->getUsername(), (*it)->getHostname(), "", (*it)->getNickname(), state, (*it)->getRealname());
			}
		}
		return command->reply(315, command->getUser().getUsername());
	}
	
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		std::string state;
		if ((*it)->getMode().find('a') != std::string::npos)
			state = "G";
		else
			state = "H";
		if ((*it)->getMode().find('o') != std::string::npos)
			state += "@";
		if (is_op && (*it)->getMode().find("o") != std::string::npos && ((*it)->getHostname() == command->getParameters()[0] || (*it)->getRealname() == command->getParameters()[0] || (*it)->getNickname() == command->getParameters()[0]))
			command->reply(352, (*it)->getLastChannel(), (*it)->getUsername(), (*it)->getHostname(), "", (*it)->getNickname(), state, (*it)->getRealname());
		else if (!is_op && ((*it)->getHostname() == command->getParameters()[0] || (*it)->getRealname() == command->getParameters()[0] || (*it)->getNickname() == command->getParameters()[0]))
			command->reply(352, (*it)->getLastChannel(), (*it)->getUsername(), (*it)->getHostname(), "", (*it)->getNickname(), state, (*it)->getRealname());
		else if (is_op && (*it)->getMode().find("o") != std::string::npos && is_star && (command->getParameters()[0].substr(0, pos) == (*it)->getHostname().substr(0, pos) || command->getParameters()[0].substr(0, pos) == (*it)->getRealname().substr(0, pos) || command->getParameters()[0].substr(0, pos) == (*it)->getNickname().substr(0, pos)))
			command->reply(352, (*it)->getLastChannel(), (*it)->getUsername(), (*it)->getHostname(), "", (*it)->getNickname(), state, (*it)->getRealname());
		else if (!is_op && is_star && (command->getParameters()[0].substr(0, pos) == (*it)->getHostname().substr(0, pos) || command->getParameters()[0].substr(0, pos) == (*it)->getRealname().substr(0, pos) || command->getParameters()[0].substr(0, pos) == (*it)->getNickname().substr(0, pos)))
			command->reply(352, (*it)->getLastChannel(), (*it)->getUsername(), (*it)->getHostname(), "", (*it)->getNickname(), state, (*it)->getRealname());
	}
	command->reply(315, command->getUser().getUsername());
}
