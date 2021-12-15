#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Utils/Utils.hpp"
#include "../../../Server/Server.hpp"

void LUSERS(irc::Command *command)
{
	size_t vis_users = 0, invis_users = 0, op_users = 0, unk_users = 0, channels;

	std::vector<irc::User *> users = command->getServer().getUsers();
	for (std::vector<irc::User *>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (command->getUser().getStatus() != irc::ONLINE)
		{
			unk_users++;
			continue;
		}
		if ((*it)->getMode().find("i") != std::string::npos)
			invis_users++;
		else
			vis_users++;
		if ((*it)->getMode().find("o") != std::string::npos)
			op_users++;
	}
	channels = command->getServer().getChannels().size();

	command->reply(251, irc::toString(vis_users), irc::toString(invis_users), "1");
	command->reply(252, irc::toString(op_users));
	command->reply(253, irc::toString(unk_users));
	command->reply(254, irc::toString(channels));
	command->reply(255, irc::toString(vis_users + invis_users), "0");
}
