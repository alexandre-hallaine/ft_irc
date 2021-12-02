#include "../PacketManager.hpp"
#include <sstream>

void irc::PING(struct irc::packetParams params)
{
	std::stringstream ss;
	ss << "PONG " << params.args[1] << "\r\n";
	params.user->write(ss.str());
}
