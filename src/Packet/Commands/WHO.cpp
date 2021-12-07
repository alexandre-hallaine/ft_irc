#include "../PacketManager.hpp"
#include <iostream>
#include <vector>

void irc::WHO(struct irc::packetParams params)
{
	bool is_star = false;
	size_t pos = 0;

	if ((pos = params.args[1].find("*")) != std::string::npos)
		is_star = true;

	for (std::vector<User *>::iterator it = params.server->getUsers().begin(); it != params.server->getUsers().end(); it++)
	{	// need to check channel first
		if ((*it)->getHostname() == params.args[1] || (*it)->getRealname() == params.args[1] || (*it)->getNickname() == params.args[1])
			params.user->write(352, "*", params.user->getUsername(), params.user->getHote(), params.user->getHostname(), params.user->getNickname(), "0", params.user->getRealname());
		else if (is_star && (params.args[1].substr(0, pos) == (*it)->getHostname().substr(0, pos) || params.args[1].substr(0, pos) == (*it)->getRealname().substr(0, pos) || params.args[1].substr(0, pos) == (*it)->getNickname().substr(0, pos) ))
			params.user->write(352, "*", params.user->getUsername(), params.user->getHote(), params.user->getHostname(), params.user->getNickname(), "0", params.user->getRealname());
	}
	params.user->write(315, params.user->getUsername());
}
