#include "../PacketManager.hpp"
#include <sstream>

void irc::CAP(struct irc::packetParams params)
{
	if (params.args[1] == "LS")
		params.user->write("CAP * LS :\r\n");
	else if (params.args[1] == "END")
		params.user->write(1, params.user->getNickname(), params.user->getUsername(), params.user->getHostname());
}
