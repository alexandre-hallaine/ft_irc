#include "../PacketManager.hpp"
#include <sstream>

void irc::PRIVMSG(struct irc::packetParams params)
{
	std::stringstream ss;
	ss << params.args[0] << " " << params.user->getNickname() << " :" << params.value;
	params.channels->get(params.args[1]).broadcast(ss.str());
}
