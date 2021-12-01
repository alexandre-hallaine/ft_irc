#include "../PacketManager.hpp"
#include <sstream>

void irc::CAP(struct irc::packetParams params)
{
	if (params.args[1] == "LS")
		params.user->write("CAP * LS :\r\n");
	else if (params.args[1] == "END")
	{
		std::stringstream ss;
		ss << "001 " << params.user->getNickname() << " :"
		   << "Hello, World!"
		   << "\r\n";
		params.user->write(ss.str());
	}
}
