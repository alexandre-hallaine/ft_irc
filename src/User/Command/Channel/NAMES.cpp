#include "../Command.hpp"
#include <algorithm>
#include "../../../Server/Server.hpp"
#include "../../User.hpp"
#include <iostream>

std::string getUsersToString(irc::Channel channel)
{
	std::vector<irc::User *> users = channel.getUsers();
	std::string users_string = "";

	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if ((*it)->getMode().find('i') != std::string::npos)
			continue;
		if (users_string.length())
			users_string += " ";
		if (channel.getUserMode(*(*it)).find('O') != std::string::npos || channel.getUserMode(*(*it)).find('o') != std::string::npos || (*it)->getMode().find('o') != std::string::npos)
			users_string += "@";
		users_string += (*it)->getNickname();
	}
	return users_string;
}

void NAMES(irc::Command *command)
{
	std::vector<irc::Channel *> channels = command->getServer().getChannels();
	if (command->getParameters().size() == 1)
	{
		irc::Channel *channel = NULL;
		for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
			if ((*it)->getName() == command->getParameters()[0])
			{
				channel = *it;
				if (channel != NULL && channel->getMode().find('p') != std::string::npos)
					channel = NULL;
				break;
			}
		if (channel != NULL)
		{
			std::string channel_mode;
			if (channel->getMode().find('p') != std::string::npos)
				channel_mode = "*";
			else if (channel->getMode().find('s') != std::string::npos)
				channel_mode = "@";
			else
				channel_mode = "=";
			std::string users_string = getUsersToString(*channel);
			if (users_string.length())
				command->reply(353, channel_mode, channel->getName(), getUsersToString(*channel));
		}
		command->reply(366, command->getParameters()[0]);
	}
	else
	{
		for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			irc::Channel *channel = *it;
			if (channel->getMode().find('p') != std::string::npos)
				continue;
			std::string channel_mode;
			if (channel->getMode().find('p') != std::string::npos)
				channel_mode = "*";
			else if (channel->getMode().find('s') != std::string::npos)
				channel_mode = "@";
			else
				channel_mode = "=";
			std::string users_string = getUsersToString(*channel);
			if (users_string.length())
				command->reply(353, channel_mode, channel->getName(), users_string);
			command->reply(366, channel->getName());
		}
		std::vector<irc::User *> users = command->getServer().getUsers();
		std::string users_not_in_channels = "";
		for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
			if ((*it)->getLastChannel() == "*")
			{
				if (users_not_in_channels.length())
					users_not_in_channels += " ";
				users_not_in_channels += (*it)->getNickname();
			}
		if (users_not_in_channels.length())
		{
			command->reply(353, "", "*", users_not_in_channels);
			command->reply(366, "*");
		}
	}
}
