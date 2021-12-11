#include "../Command.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"
#include "../../../Server/Channel/Channel.hpp"

void JOIN(irc::Command *command)
{
	if (command->getParameters().size() == 0)
		return command->reply(461, "JOIN");

	std::vector<std::string> channelsNames = irc::split(command->getParameters()[0], ",");
	for (std::vector<std::string>::iterator it = channelsNames.begin(); it != channelsNames.end(); ++it)
	{
		if (command->getServer().getChannel(*it).getUsers().size() == 0)
		{
			command->getServer().getChannel(*it).addUser(command->getUser());
			command->getServer().getChannel(*it).setMode(command->getUser(), "+o");
		}
		else
			command->getServer().getChannel(*it).addUser(command->getUser());
		command->reply(332, *it, command->getServer().getChannel(*it).getTopic());
		command->reply(353, "=", *it, command->getServer().getChannel(*it).getUsersString());
		command->reply(366, *it);
	}
	
}
