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
		if (channel.getMode(*(*it)).find('o') != std::string::npos)
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
		irc::Channel &channel = command->getServer().getChannel(*it);
		if (channel.getUsers().size() == 0)
		{
			channel.addUser(command->getUser());
			channel.setMode(command->getUser(), "o");
		}
		else
			channel.addUser(command->getUser());
		command->reply(332, *it, channel.getTopic());
		command->reply(353, "=", *it, getUsersString(channel));
		command->reply(366, *it);
		channel.write(&command->getUser(), ":" + command->getUser().getPrefix() + " JOIN :" + channel.getName());
	}
}
