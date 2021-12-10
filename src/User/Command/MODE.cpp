#include "Command.hpp"
#include "../User.hpp"
#include "../../utils/utils.hpp"
#include "../../Server/Server.hpp"

void check_mode(std::string *mode, char option, bool is_minus)
{
	if (mode->find(option) != std::string::npos && is_minus)
		mode->erase(mode->begin() + mode->find(option));
	else if (mode->find(option) == std::string::npos && !is_minus)
		mode->insert(mode->end(), option);
}

void MODE(class irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "MODE");

	std::string mode = command->getUser().getMode();
	bool is_minus = false;

	if (command->getParameters()[0] != command->getUser().getNickname())
		return command->reply(502);

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

	command->getUser().setMode(mode);
	return command->reply(221, "+" + mode);
}
