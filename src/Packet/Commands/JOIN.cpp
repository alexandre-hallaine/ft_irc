#include "../PacketManager.hpp"
#include <sstream>

void irc::JOIN(struct irc::packetParams params)
{
	Channel &channel = params.channels->get(params.args[1]);
	channel.addUser(params.user);
}
