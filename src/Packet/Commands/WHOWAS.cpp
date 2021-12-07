#include "../PacketManager.hpp"

void irc::WHOWAS(struct irc::packetParams params)
{
	if (params.args.size() == 1)
		return params.user->write(431);
}
