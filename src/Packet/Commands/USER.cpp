#include "../PacketManager.hpp"

void irc::USER(struct irc::packetParams params)
{
	params.user->setUsername(params.args[1]);
	params.user->setHostname(params.args[2]);
	params.user->setServername(params.args[3]);
	params.user->setRealname(params.args[4].erase(0, 1));
}
