#include "../PacketManager.hpp"
#include <vector>

void irc::WHOIS(struct irc::packetParams params)
{
	if (params.args.size() == 1)
		return params.user->write(431);

	for (std::vector<User *>::iterator it = params.server->getUsers().begin(); it != params.server->getUsers().end(); it++)
		if (params.args[1] == (*it)->getNickname())
		{
			//need to check for channels
			params.user->write(311, params.args[1], params.user->getHostname(), params.user->getHote(), params.user->getRealname());
			return params.user->write(318, params.args[1]);
		}

	return params.user->write(401, params.args[1]);
}
