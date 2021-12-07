#include "../PacketManager.hpp"

void irc::WHOIS(struct irc::packetParams params)
{
	params.user->write(311, params.args[1], params.user->getHostname(), params.user->getHote(), params.user->getRealname());
	params.user->write(318, params.args[1]);
}
