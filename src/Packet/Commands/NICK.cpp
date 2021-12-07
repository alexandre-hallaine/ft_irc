#include "../PacketManager.hpp"
#include <vector>
#include <sstream>
#include <iostream>

void irc::NICK(struct irc::packetParams params)
{
	if (params.args[1].empty())
		return params.user->write(431);

	for (std::vector<User *>::iterator it = params.server->getUsers().begin(); it != params.server->getUsers().end(); ++it)
		if (params.args[1] == (*it)->getNickname())
			return params.user->write(433, (*it)->getNickname());

//need to check for allowed characters
	if (params.args[1].size() > 9)
		return params.user->write(432, params.args[1]);	

	bool init = false;
	if (params.user->getNickname() != "*")
	{
		std::stringstream ss;
		ss << ":" << params.user->getNickname() << " " << "NICK" << " " << params.args[1] << "\r\n";
		params.user->write(ss.str());
	}
	else
		init = true;
	params.user->setNickname(params.args[1]);
	if (init && params.user->getRegistered())
		CAP(params);
}
