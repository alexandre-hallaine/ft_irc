#include "Command.hpp"
#include "../User.hpp"
#include "../../utils/utils.hpp"
#include "../../Server/Server.hpp"

void check_mode(std::string *mode, char option, bool is_minus, std::string options)
{
	size_t i = 0;

	while (i != options.size())
	{
		if (option == options[i])
		{
			if (mode->find(options[i]) != std::string::npos && is_minus)
				mode->erase(mode->begin() + mode->find(options[i]));
			else if (mode->find(options[i]) == std::string::npos && !is_minus)
				mode->insert(mode->end(), options[i]);
		}
		i++;
	}
}

void MODE(class irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "MODE");

	std::string mode = command->getUser().getMode(); 
	bool is_minus = false;
	size_t i = 0;

	if (mode.size() == 0)
		mode = "+";

	if (command->getParameters()[0] != command->getUser().getNickname())
		return command->reply(502);

	while (command->getParameters().back() != command->getParameters()[0] && i != command->getParameters()[1].size())
	{
		if (command->getParameters()[1][i] == '-')
			is_minus = true;
		else if (command->getParameters()[1][i] == '+')
			is_minus = false;
		else if (command->getParameters()[1][i] == 'i')
			check_mode(&mode, 'i', is_minus, command->getServer().getConfig().get("user_mode")); 
		else if (command->getParameters()[1][i] == 's')
			check_mode(&mode, 's', is_minus, command->getServer().getConfig().get("user_mode")); 
		else if (command->getParameters()[1][i] == 'w')
			check_mode(&mode, 'w', is_minus, command->getServer().getConfig().get("user_mode")); 
		else
			command->reply(472, std::string(1, command->getParameters()[1][i]));
		i++;
	}

	command->getUser().setMode(mode);
	command->reply(221, mode);
}
