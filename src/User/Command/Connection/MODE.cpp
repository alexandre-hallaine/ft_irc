#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"

void check_mode(std::string *mode, char option, bool is_minus)
{
	if (is_minus && mode->find(option) != std::string::npos)
		mode->erase(mode->begin() + mode->find(option));
	else if (!is_minus && mode->find(option) == std::string::npos)
		mode->insert(mode->end(), option);
}

void MODE(class irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "MODE");

	irc::User *user = 0;

	if (command->getParameters()[0] != command->getUser().getNickname())
	{
		if (command->getUser().getMode().find("o") == std::string::npos)
			return command->reply(502);
				
		std::vector<irc::User *> users = command->getServer().getUsers();
		for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
			if ((*it)->getNickname() == command->getParameters()[0])
			{
				user = (*it);
				break ;
			}
		if (!user)
			return ;
	}
	else
		user = &command->getUser();

	std::string mode = user->getMode();
	bool is_minus = false;

	if (command->getParameters().size() > 1)
	{
		std::string request = command->getParameters()[1];
		for (size_t i = 0; i != request.size(); ++i)
			if (request[i] == '-')
				is_minus = true;
			else if (request[i] == '+')
				is_minus = false;
			else if (command->getServer().getConfig().get("user_mode").find(request[i]) == std::string::npos)
				return command->reply(501);
			else if (request[i] != 'a' && !(!is_minus && (request[i] == 'o' || request[i] == 'O')))
				check_mode(&mode, request[i], is_minus);
	}

	user->setMode(mode);
	return command->reply(221, "+" + mode);
}
