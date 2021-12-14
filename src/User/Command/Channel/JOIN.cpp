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
		if (channel.getUserMode(*(*it)).find('O') != std::string::npos)
			users_string += "@";
		users_string += (*it)->getNickname();
	}
	return users_string;
}

void JOIN(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "JOIN");

	std::vector<std::string> channelsNames = irc::split(command->getParameters()[0], ",");
	for (std::vector<std::string>::iterator it = channelsNames.begin(); it != channelsNames.end(); ++it)
	{
		if (it->c_str()[0] != '#')
			*it = "#" + *it;
		irc::Channel &channel = command->getServer().getChannel(*it);
		if (channel.getUsers().size() == 0)
		{
			channel.addUser(command->getUser());
			channel.setUserMode(command->getUser(), "O");
		}
		else
		{
			if (channel.getMode().find('k') != std::string::npos && channel.getKey() != command->getParameters()[1])
				return command->reply(475, *it);
			if (channel.getMode().find('l') != std::string::npos && channel.getUsers().size() >= (size_t)atoi(channel.getMaxUsers().c_str()))
				return command->reply(471, *it);
			if (channel.getMode().find('i') != std::string::npos && !channel.isInvited(command->getUser()))
				return command->reply(473, *it);
			channel.removeInvited(command->getUser());
			channel.addUser(command->getUser());
		}
		command->reply(332, *it, channel.getTopic());
		command->reply(353, "=", *it, getUsersString(channel));
		command->reply(366, *it);
		channel.broadcast(command->getUser(), "JOIN :" + channel.getName());
		command->getUser().setLastChannel(channel.getName());
	}
}
