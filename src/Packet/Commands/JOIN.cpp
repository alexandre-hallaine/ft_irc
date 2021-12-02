#include "../PacketManager.hpp"
#include <sstream>

void irc::JOIN(struct irc::packetParams params)
{
	Channel &channel = params.channels->get(params.args[1]);
	channel.addUser(params.user);
	std::stringstream ss;
	ss << "001 " << params.args[1] << " :"
	   << "You are now on the \033[0;35m" << params.args[1] << "\033[0m channel"
	   << "\r\n";
	params.user->write(ss.str());
}
