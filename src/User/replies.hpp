#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

namespace irc
{
	std::string generate(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);

	std::string RPL_WELCOME(std::string nick, std::string user, std::string host);
	std::string RPL_TOPIC(std::string channel, std::string topic);
	std::string RPL_NOTOPIC(std::string channel);
	std::string RPL_UMODEIS(std::string mode);
	std::string ERR_UNKNOWNMODE(std::string mode);
}
#endif
