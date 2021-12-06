#include "../PacketManager.hpp"

void irc::WHOIS(struct irc::packetParams params)
{
	params.user->write(311, params.user->getUsername(), params.user->getHostname(), params.user->getHote(), params.user->getRealname());
	params.user->write(318, params.user->getUsername());
	return ;
}
