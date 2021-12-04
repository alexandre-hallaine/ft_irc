#include "../PacketManager.hpp"
#include <vector>

void irc::NICK(struct irc::packetParams params)
{
	if (params.args[1].empty())
	{
		params.user->write(431);
		return ;
	}
	//for (std::vector<User *>::iterator it = params.server->getUsers().begin(); it != params.server->getUsers().end(); it++)
	//{
	//	if (params.args[1] == (*it).getNickname())
	//	{
	//		params.user->write(436, params.user->getNickname());
	//		return ;
	//	}
	//}
	params.user->setNickname(params.args[1]);
}
