#include "../PacketManager.hpp"
#include <sstream>

void irc::PING(struct irc::packetParams params)
{
	if (params.args.size() == 1)
		return params.user->write(409);
	std::stringstream ss;
	ss << "PONG " << params.args[1] << "\r\n";
	params.user->write(ss.str());
}
