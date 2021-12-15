#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"

void check_togglemode(std::string *mode, char option, bool is_minus)
{
	if (is_minus && mode->find(option) != std::string::npos)
		mode->erase(mode->find(option), 1);
	else if (!is_minus && mode->find(option) == std::string::npos)
		mode->push_back(option);
}

void check_setmode(std::string *mode, char option, bool is_minus, class irc::Command *command, size_t count)
{
	if (is_minus && mode->find(option) != std::string::npos)
	{
		if (option == 'l')
			command->getServer().getChannel(command->getParameters()[0]).setMaxUsers("");
		else if (option == 'k' && command->getParameters()[count] != command->getServer().getChannel(command->getParameters()[0]).getKey())
			return;
		else if (option == 'k' && command->getParameters()[count] == command->getServer().getChannel(command->getParameters()[0]).getKey())
			command->getServer().getChannel(command->getParameters()[0]).setKey("");
		mode->erase(mode->find(option), 1);
	}
	else if (!is_minus && mode->find(option) == std::string::npos)
	{
		if (option == 'k')
			command->getServer().getChannel(command->getParameters()[0]).setKey(command->getParameters()[count]);
		else
		{
			for (size_t index = 0; index != command->getParameters()[count].length(); index++)
				if (!irc::isDigit(command->getParameters()[count][index]))
					return;
			command->getServer().getChannel(command->getParameters()[0]).setMaxUsers(command->getParameters()[count]);
		}
		mode->push_back(option);
	}
	else if (!is_minus && option == 'k' && mode->find(option) != std::string::npos)
		command->reply(467, command->getParameters()[0]);
	else if (!is_minus && option == 'l' && mode->find(option) != std::string::npos)
	{
		for (size_t index = 0; index != command->getParameters()[count].length(); index++)
			if (!irc::isDigit(command->getParameters()[count][index]))
				return;
		command->getServer().getChannel(command->getParameters()[0]).setMaxUsers(command->getParameters()[count]);
	}
}

void check_givemode(char option, bool is_minus, class irc::Command *command, size_t count)
{
	irc::User *user = 0;
	std::vector<irc::User *> users = command->getServer().getChannel(command->getParameters()[0]).getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); it++)
		if ((*it)->getNickname() == command->getParameters()[count])
		{
			user = (*it);
			break;
		}
	if (!user)
		return command->reply(441, command->getParameters()[count], command->getParameters()[0]);

	std::string mode = command->getServer().getChannel(command->getParameters()[0]).getUserMode(*user);
	if (is_minus && mode.find(option) != std::string::npos)
		mode.erase(mode.find(option), 1);
	else if (!is_minus && mode.find(option) == std::string::npos)
		mode.push_back(option);

	command->getServer().getChannel(command->getParameters()[0]).setUserMode(*user, mode);
	if (!is_minus)
		return command->reply(324, command->getParameters()[0], "+" + std::string(1, option), command->getParameters()[count]);
	else
		return command->reply(324, command->getParameters()[0], "-" + std::string(1, option), command->getParameters()[count]);
}

void MODE_channel(class irc::Command *command)
{
	if (!command->getServer().isChannel(command->getParameters()[0]))
		return command->reply(403, command->getParameters()[0]);

	if (command->getParameters()[0] == "b")
		return;

	std::string mode = command->getServer().getChannel(command->getParameters()[0]).getMode();
	bool is_minus = false;
	size_t count = 2;
	if (command->getParameters().size() > 1)
	{
		std::string request = command->getParameters()[1];
		for (size_t i = 0; i != request.size(); ++i)
		{
			if (request[i] == '-')
				is_minus = true;
			else if (request[i] == '+')
				is_minus = false;
			else if (command->getServer().getConfig().get("channel_togglemode").find(request[i]) == std::string::npos && command->getServer().getConfig().get("channel_setmode").find(request[i]) == std::string::npos && command->getServer().getConfig().get("channel_givemode").find(request[i]) == std::string::npos)
				command->reply(472, std::string(1, request[i]));
			else if (command->getServer().getConfig().get("channel_togglemode").find(request[i]) != std::string::npos && (command->getUser().getMode().find("o") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("O") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("o") != std::string::npos))
			{
				if (command->getUser().getMode().find("o") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("O") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("o") != std::string::npos)
					check_togglemode(&mode, request[i], is_minus);
				else
					command->reply(482, command->getParameters()[0]);
			}
			else if (command->getParameters().size() == count && (request[i] != 'l' || !is_minus) && command->getServer().getConfig().get("channel_setmode").find(request[i]) != std::string::npos)
				command->reply(461, "MODE");
			else if ((command->getParameters().size() > 2 || (request[i] == 'l' && is_minus)) && command->getServer().getConfig().get("channel_setmode").find(request[i]) != std::string::npos)
			{
				if (command->getUser().getMode().find("o") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("O") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("o") != std::string::npos)
					check_setmode(&mode, request[i], is_minus, command, count);
				else
					command->reply(482, command->getParameters()[0]);
				if (request[i] != 'l')
					count++;
				else if (request[i] == 'l' && !is_minus)
					count++;
			}
			else if (command->getParameters().size() == count && command->getServer().getConfig().get("channel_givemode").find(request[i]) != std::string::npos)
				command->reply(461, "MODE");
			else if (command->getParameters().size() > 2 && command->getServer().getConfig().get("channel_givemode").find(request[i]) != std::string::npos)
			{
				if (request[i] != 'O' && (command->getUser().getMode().find("o") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("O") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("o") != std::string::npos))
					check_givemode(request[i], is_minus, command, count);
				else if (request[i] != 'O')
					command->reply(482, command->getParameters()[0]);
				count++;
			}
		}
	}
	command->getServer().getChannel(command->getParameters()[0]).setMode(mode);
	std::string options = command->getServer().getChannel(command->getParameters()[0]).getKey();
	if (options.size() > 0)
		options += " ";
	options += command->getServer().getChannel(command->getParameters()[0]).getMaxUsers();
	if (command->getUser().getMode().find("o") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("O") != std::string::npos || command->getServer().getChannel(command->getParameters()[0]).getUserMode(command->getUser()).find("o") != std::string::npos)
		return command->reply(324, command->getParameters()[0], "+" + mode, options);
	return command->reply(324, command->getParameters()[0], "+" + mode, "");
}

void MODE_user(class irc::Command *command)
{
	irc::User *user = 0;

	if (command->getParameters()[0] == command->getUser().getNickname())
		user = &command->getUser();
	else
	{
		if (command->getUser().getMode().find("o") == std::string::npos)
			return command->reply(502);

		user = command->getServer().getUser(command->getParameters()[0]);
		if (!user)
			return;
	}

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
			else if (request[i] == 'a')
				continue;
			else if (request[i] == 'o' && command->getUser().getMode().find("o") == std::string::npos)
				continue;
			else if (request[i] == 'r' && is_minus && command->getUser().getMode().find("o") == std::string::npos)
				continue;
			else
				check_togglemode(&mode, request[i], is_minus);
	}

	user->setMode(mode);
	return command->reply(*user, 221, "+" + mode);
}

void MODE(class irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "MODE");

	if (command->getParameters()[0].find("#") != std::string::npos)
		return MODE_channel(command);
	return MODE_user(command);
}
