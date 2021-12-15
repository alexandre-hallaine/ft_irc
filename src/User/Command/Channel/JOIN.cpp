#include <cstdlib>
#include "../Command.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"
#include "../../User.hpp"

std::string getUsersString(irc::Channel channel)
{
	std::vector<irc::User *> users = channel.getUsers();
	std::string users_string = "";

	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (users_string.length())
			users_string += " ";
		if (channel.getUserMode(*(*it)).find('O') != std::string::npos || channel.getUserMode(*(*it)).find('o') != std::string::npos || (*it)->getMode().find('o') != std::string::npos)
			users_string += "@";
		users_string += (*it)->getNickname();
	}
	return users_string;
}

void leaveAllChannels(irc::Command *command)
{
	std::vector<irc::Channel *> channels = command->getServer().getChannels();
	for (std::vector<irc::Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		(*it)->broadcast(command->getUser(), "PART " + (*it)->getName() + (command->getParameters().size() > 1 ? " :" + command->getParameters()[1] : ""));
		(*it)->removeUser(command->getUser());
		if ((*it)->getUsers().size() == 0)
			command->getServer().delChannel(*(*it));
	}
}

void JOIN(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "JOIN");
	if (command->getParameters()[0] == "0")
		return leaveAllChannels(command);
	std::vector<std::string> channelsNames = irc::split(command->getParameters()[0], ",");
	std::vector<std::string> keys = command->getParameters().size() > 1 ? irc::split(command->getParameters()[1], ",") : std::vector<std::string>();
	std::vector<std::string>::iterator it_keys = keys.begin();
	for (std::vector<std::string>::iterator it = channelsNames.begin(); it != channelsNames.end(); ++it)
	{
		if (it->c_str()[0] != '#')
		{
			command->reply(476, *it);
			continue;
		}
		irc::Channel &channel = command->getServer().getChannel(*it);
		if (channel.getUsers().size() == 0)
		{
			channel.addUser(command->getUser());
			channel.setUserMode(command->getUser(), "O");
		}
		else
		{
			std::string key = it_keys != keys.end() ? *it_keys++ : "";
			if (channel.getMode().find('k') != std::string::npos && channel.getKey() != key)
			{
				command->reply(475, *it);
				continue;
			}
			if (channel.getMode().find('l') != std::string::npos && channel.getUsers().size() >= (size_t)atoi(channel.getMaxUsers().c_str()))
			{
				command->reply(471, *it);
				continue;
			}
			if (channel.getMode().find('i') != std::string::npos && !channel.isInvited(command->getUser()) && command->getUser().getMode().find('o') == std::string::npos)
			{
				command->reply(473, *it);
				continue;
			}
			channel.removeInvited(command->getUser());
			channel.addUser(command->getUser());
		}
		std::string channel_mode;
		if (channel.getMode().find('p') != std::string::npos)
			channel_mode = "*";
		else if (channel.getMode().find('s') != std::string::npos)
			channel_mode = "@";
		else
			channel_mode = "=";
		if (channel.getTopic().length())
			command->reply(332, *it, channel.getTopic());
		command->reply(353, channel_mode, *it, getUsersString(channel));
		command->reply(366, *it);
		channel.broadcast(command->getUser(), "JOIN :" + channel.getName());
		if (channel.getMode().find('p') == std::string::npos)
			command->getUser().setLastChannel(channel.getName());
	}
}
