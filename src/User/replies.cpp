#include "replies.hpp"

std::string irc::generate(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
	(void)arg4;
	switch (code)
	{
	case 401:
		return ERR_NOSUCHNICK(arg1);
	case 402:
		return ERR_NOSUCHSERVER(arg1);
	case 403:
		return ERR_NOSUCHCHANNEL(arg1);
	case 404:
		return ERR_CANNOTSENDTOCHAN(arg1);
	case 405:
		return ERR_TOOMANYCHANNELS(arg1);
	case 406:
		return ERR_WASNOSUCHNICK(arg1);
	case 407:
		return ERR_TOOMANYTARGETS(arg1);
	case 409:
		return ERR_NOORIGIN();
	case 411:
		return ERR_NORECIPIENT(arg1);
	case 412:
		return ERR_NOTEXTTOSEND();
	case 413:
		return ERR_NOTOPLEVEL(arg1);
	case 414:
		return ERR_WILDTOPLEVEL(arg1);
	case 421:
		return ERR_UNKNOWNCOMMAND(arg1);
	case 422:
		return ERR_NOMOTD();
	case 423:
		return ERR_NOADMININFO(arg1);
	case 424:
		return ERR_FILEERROR(arg1, arg2);
	case 431:
		return ERR_NONICKNAMEGIVEN();
	case 432:
		return ERR_ERRONEUSNICKNAME(arg1);
	case 433:
		return ERR_NICKNAMEINUSE(arg1);
	case 436:
		return ERR_NICKCOLLISION(arg1);
	case 441:
		return ERR_USERNOTINCHANNEL(arg1, arg2);
	case 442:
		return ERR_NOTONCHANNEL(arg1);
	case 443:
		return ERR_USERONCHANNEL(arg1, arg2);
	case 444:
		return ERR_NOLOGIN(arg1);
	case 445:
		return ERR_SUMMONDISABLED();
	case 446:
		return ERR_USERSDISABLED();
	case 451:
		return ERR_NOTREGISTERED();
	case 461:
		return ERR_NEEDMOREPARAMS(arg1);
	case 462:
		return ERR_ALREADYREGISTRED();
	case 463:
		return ERR_NOPERMFORHOST();
	case 464:
		return ERR_PASSWDMISMATCH();
	case 465:
		return ERR_YOUREBANNEDCREEP();
	case 467:
		return ERR_KEYSET(arg1);
	case 471:
		return ERR_CHANNELISFULL(arg1);
	case 472:
		return ERR_UNKNOWNMODE(arg1);
	case 473:
		return ERR_INVITEONLYCHAN(arg1);
	case 474:
		return ERR_BANNEDFROMCHAN(arg1);
	case 475:
		return ERR_BADCHANNELKEY(arg1);
	case 481:
		return ERR_NOPRIVILEGES();
	case 482:
		return ERR_CHANOPRIVSNEEDED(arg1);
	case 483:
		return ERR_CANTKILLSERVER();
	case 491:
		return ERR_NOOPERHOST();
	case 501:
		return ERR_UMODEUNKNOWNFLAG();
	case 502:
		return ERR_USERSDONTMATCH();
	}
	return std::string();
}

std::string irc::ERR_NOSUCHNICK(std::string nickname) { return nickname + " :No such nick/channel"; }
std::string irc::ERR_NOSUCHSERVER(std::string server) { return server + " :No such server"; }
std::string irc::ERR_NOSUCHCHANNEL(std::string channel) { return channel + " :No such channel"; }
std::string irc::ERR_CANNOTSENDTOCHAN(std::string channel) { return channel + " :Cannot send to channel"; }
std::string irc::ERR_TOOMANYCHANNELS(std::string channel) { return channel + " :You have joined too many channels"; }
std::string irc::ERR_WASNOSUCHNICK(std::string nickname) { return nickname + " :There was no such nickname"; }
std::string irc::ERR_TOOMANYTARGETS(std::string target) { return target + " :Duplicate recipients. No message delivered"; }
std::string irc::ERR_NOORIGIN() { return ":No origin specified"; }
std::string irc::ERR_NORECIPIENT(std::string command) { return ":No recipient given (" + command + ")"; }
std::string irc::ERR_NOTEXTTOSEND() { return ":No text to send"; }
std::string irc::ERR_NOTOPLEVEL(std::string mask) { return mask + " :No toplevel domain specified"; }
std::string irc::ERR_WILDTOPLEVEL(std::string mask) { return mask + " :Wildcard in toplevel domain"; }
std::string irc::ERR_UNKNOWNCOMMAND(std::string command) { return command + " :Unknown command"; }
std::string irc::ERR_NOMOTD() { return ":MOTD File is missing"; }
std::string irc::ERR_NOADMININFO(std::string server) { return server + " :No administrative info available"; }
std::string irc::ERR_FILEERROR(std::string op, std::string file) { return ":File error doing " + op + " on " + file; }
std::string irc::ERR_NONICKNAMEGIVEN() { return ":No nickname given"; }
std::string irc::ERR_ERRONEUSNICKNAME(std::string nick) { return nick + " :Erroneus nickname"; }
std::string irc::ERR_NICKNAMEINUSE(std::string nick) { return nick + " :Nickname is already in use"; }
std::string irc::ERR_NICKCOLLISION(std::string nick) { return nick + " :Nickname collision KILL"; }
std::string irc::ERR_USERNOTINCHANNEL(std::string nick, std::string channel) { return nick + " " + channel + " :They aren't on that channel"; }
std::string irc::ERR_NOTONCHANNEL(std::string channel) { return channel + " :You're not on that channel"; }
std::string irc::ERR_USERONCHANNEL(std::string user, std::string channel) { return user + " " + channel + " :is already on channel"; }
std::string irc::ERR_NOLOGIN(std::string user) { return user + " :User not logged in"; }
std::string irc::ERR_SUMMONDISABLED() { return ":SUMMON has been disabled"; }
std::string irc::ERR_USERSDISABLED() { return ":USERS has been disabled"; }
std::string irc::ERR_NOTREGISTERED() { return ":You have not registered"; }
std::string irc::ERR_NEEDMOREPARAMS(std::string command) { return command + " :Not enough parameters"; }
std::string irc::ERR_ALREADYREGISTRED() { return ":You may not reregister"; }
std::string irc::ERR_NOPERMFORHOST() { return ":Your host isn't among the privileged"; }
std::string irc::ERR_PASSWDMISMATCH() { return ":Password incorrect"; }
std::string irc::ERR_YOUREBANNEDCREEP() { return ":You are banned from this server"; }
std::string irc::ERR_KEYSET(std::string channel) { return channel + " :Channel key already set"; }
std::string irc::ERR_CHANNELISFULL(std::string channel) { return channel + " :Cannot join channel (+l)"; }
std::string irc::ERR_UNKNOWNMODE(std::string c) { return c + " :is unknown mode char to me"; }
std::string irc::ERR_INVITEONLYCHAN(std::string channel) { return channel + " :Cannot join channel (+i)"; }
std::string irc::ERR_BANNEDFROMCHAN(std::string channel) { return channel + " :Cannot join channel (+b)"; }
std::string irc::ERR_BADCHANNELKEY(std::string channel) { return channel + " :Cannot join channel (+k)"; }
std::string irc::ERR_NOPRIVILEGES() { return ":Permission Denied- You're not an IRC operator"; }
std::string irc::ERR_CHANOPRIVSNEEDED(std::string channel) { return channel + " :You're not channel operator"; }
std::string irc::ERR_CANTKILLSERVER() { return ":You cant kill a server!"; }
std::string irc::ERR_NOOPERHOST() { return ":No O-lines for your host"; }
std::string irc::ERR_UMODEUNKNOWNFLAG() { return ":Unknown MODE flag"; }
std::string irc::ERR_USERSDONTMATCH() { return ":Cant change mode for other users"; }
