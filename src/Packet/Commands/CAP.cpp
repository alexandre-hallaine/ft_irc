#include "../PacketManager.hpp"
#include <sstream>
#include <ctime>

void irc::CAP(struct irc::packetParams params)
{
	if (params.args[1] == "LS")
		params.user->write("CAP * LS :\r\n");
	else if (params.args[1] == "END")
	{
		params.user->write(1, params.user->getNickname(), params.user->getUsername(), params.user->getHostname());
		params.user->write(2, params.server->getServername(), params.server->getVersion());
		params.user->write(3, params.server->getTime());
		params.user->write(4, params.server->getServername(), params.server->getVersion(), "iws", "");
	}
}
