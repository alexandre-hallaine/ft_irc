#include "replies.hpp"

std::string irc::generate(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
	(void)arg4;
	switch (code)
	{
	case 1:
		return RPL_WELCOME(arg1, arg2, arg3);
	case 221:
		return RPL_UMODEIS(arg1);
	case 331:
		return RPL_NOTOPIC(arg1);
	case 332:
		return RPL_TOPIC(arg1, arg2);
	case 472:
		return ERR_UNKNOWNMODE(arg1);
	}
	return std::string();
}

std::string irc::RPL_WELCOME(std::string nick, std::string user, std::string host) { return ":Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host; }
std::string irc::RPL_TOPIC(std::string channel, std::string topic) { return channel + " :" + topic; }
std::string irc::RPL_NOTOPIC(std::string channel) { return channel + " :No topic is set"; }
std::string irc::RPL_UMODEIS(std::string mode) { return ":" + mode; }
std::string irc::ERR_UNKNOWNMODE(std::string mode) { return mode + " :is unknown mode char to me"; }
