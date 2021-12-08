#include "../PacketManager.hpp"

void irc::WHOWAS(struct irc::packetParams params)
{
	size_t pos = 0, tmp = 0;
	bool has_print = false;

	if (params.args.size() == 1)
		return params.user->write(431);

	for (std::vector<User *>::iterator it = params.server->getUsers().begin(); it != params.server->getUsers().end(); it++)
	{
		while ((tmp = (*it)->getPastnick().find(params.args[1], pos)) != std::string::npos)
		{
			params.user->write(314, params.args[1], (*it)->getUsername(), (*it)->getHote(), (*it)->getRealname());
			pos = tmp + 1;
			has_print = true;
		}
		pos = 0, tmp = 0;
	}
	if (!has_print)
		return params.user->write(406, params.args[1]);
	return params.user->write(369);
}
