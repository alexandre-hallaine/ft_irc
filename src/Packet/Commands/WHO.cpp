#include "../PacketManager.hpp"
#include <iostream>

void irc::WHO(struct irc::packetParams params)
{
	params.user->write(352, "*", params.user->getUsername(), params.user->getHote(), params.user->getHostname(), params.user->getNickname(), "0", params.user->getRealname());
	params.user->write(315, params.user->getUsername());
}
