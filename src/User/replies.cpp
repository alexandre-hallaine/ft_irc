#include "User.hpp"

std::string RPL_NONE();
std::string RPL_USERHOST(std::string reply, std::string space);
std::string RPL_ISON(std::string nick, std::string space);
std::string RPL_AWAY(std::string nick, std::string message);
std::string RPL_UNAWAY();
std::string RPL_NOWAWAY();
std::string RPL_WHOISUSER(std::string nick, std::string user, std::string host, std::string real);
std::string RPL_WHOISSERVER(std::string nick, std::string server, std::string info);
std::string RPL_WHOISOPERATOR(std::string nick);
std::string RPL_WHOISIDLE(std::string nick, std::string integer);
std::string RPL_ENDOFWHOIS(std::string nick);
std::string RPL_WHOISCHANNELS(std::string nick, std::string channel, std::string space);
std::string RPL_WHOWASUSER(std::string nick, std::string user, std::string host, std::string real);
std::string RPL_ENDOFWHOWAS(std::string nick);
std::string RPL_LISTSTART();
std::string RPL_LIST(std::string channel, std::string topic);
std::string RPL_LISTEND();
std::string RPL_CHANNELMODEIS(std::string channel, std::string mode, std::string params);
std::string RPL_NOTOPIC(std::string channel);
std::string RPL_TOPIC(std::string channel, std::string topic);
std::string RPL_INVITING(std::string channel, std::string nick);
std::string RPL_SUMMONING(std::string user);
std::string RPL_VERSION(std::string version, std::string debuglevel, std::string server, std::string comments);
std::string RPL_WHOREPLY(std::string channel, std::string user, std::string host, std::string server, std::string nick, std::string hopcout, std::string real);
std::string RPL_ENDOFWHO(std::string name);
std::string RPL_NAMREPLY(std::string channel, std::string nick_list);
std::string RPL_ENDOFNAMES(std::string channel);
std::string RPL_LINKS(std::string mask, std::string server, std::string hopcount, std::string info);
std::string RPL_ENDOFLINKS(std::string mask);
std::string RPL_BANLIST(std::string channel, std::string banip);
std::string RPL_ENDOFBANLIST(std::string channel);
std::string RPL_INFO(std::string string);
std::string RPL_ENDOFINFO();
std::string RPL_MOTDSTART(std::string server);
std::string RPL_MOTD(std::string text);
std::string RPL_ENDOFMOTD();
std::string RPL_YOUREOPER();
std::string RPL_REHASHING(std::string file);
std::string RPL_TIME(std::string server, std::string time);
std::string RPL_USERSSTART();
std::string RPL_USERS();
std::string RPL_ENDOFUSERS();
std::string RPL_NOUSERS();
std::string RPL_TRACELINK(std::string version, std::string destination, std::string server);
std::string RPL_TRACECONNECTING(std::string class1, std::string server);
std::string RPL_TRACEHANDSHAKE(std::string class1, std::string server);
std::string RPL_TRACEUNKNOWN(std::string class1, std::string ip);
std::string RPL_TRACEOPERATOR(std::string class1, std::string nick);
std::string RPL_TRACEUSER(std::string class1, std::string nick);
std::string RPL_TRACESERVER(std::string class1, std::string int1, std::string int2, std::string server, std::string nick, std::string host);
std::string RPL_TRACENEWTYPE(std::string type, std::string name);
std::string RPL_TRACELOG(std::string file, std::string level);
std::string RPL_STATSLINKINFO(std::string name, std::string q, std::string smessages, std::string sbytes, std::string rsmessages, std::string rbytes, std::string time);
std::string RPL_STATSCOMMANDS(std::string command, std::string count);
std::string RPL_STATSCLINE(std::string host, std::string name, std::string port, std::string class1);
std::string RPL_STATSNLINE(std::string host, std::string name, std::string port, std::string class1);
std::string RPL_STATSILINE(std::string host1, std::string host2, std::string port, std::string class1);
std::string RPL_STATSKLINE(std::string host, std::string user, std::string port, std::string class1);
std::string RPL_STATSYLINE(std::string class1, std::string ping, std::string connect, std::string max);
std::string RPL_ENDOFSTATS(std::string letter);
std::string RPL_STATSLLINE(std::string host, std::string name, std::string depth);
std::string RPL_STATSUPTIME();
std::string RPL_STATSOLINE(std::string mask, std::string name);
std::string RPL_STATSHLINE(std::string mask, std::string name);
std::string RPL_UMODEIS(std::string mode);

std::string ERR_NOSUCHNICK(std::string nickname) { return nickname + " :No such nick/channel"; }
std::string ERR_NOSUCHSERVER(std::string server) { return server + " :No such server"; }
std::string ERR_NOSUCHCHANNEL(std::string channel) { return channel + " :No such channel"; }
std::string ERR_CANNOTSENDTOCHAN(std::string channel) { return channel + " :Cannot send to channel"; }
std::string ERR_TOOMANYCHANNELS(std::string channel) { return channel + " :You have joined too many channels"; }
std::string ERR_WASNOSUCHNICK(std::string nickname) { return nickname + " :There was no such nickname"; }
std::string ERR_TOOMANYTARGETS(std::string target) { return target + " :Duplicate recipients. No message delivered"; }
std::string ERR_NOORIGIN() { return ":No origin specified"; }
std::string ERR_NORECIPIENT(std::string command) { return ":No recipient given (" + command + ")"; }
std::string ERR_NOTEXTTOSEND() { return ":No text to send"; }
std::string ERR_NOTOPLEVEL(std::string mask) { return mask + " :No toplevel domain specified"; }
std::string ERR_WILDTOPLEVEL(std::string mask) { return mask + " :Wildcard in toplevel domain"; }
std::string ERR_UNKNOWNCOMMAND(std::string command) { return command + " :Unknown command"; }
std::string ERR_NOMOTD() { return ":MOTD File is missing"; }
std::string ERR_NOADMININFO(std::string server) { return server + " :No administrative info available"; }
std::string ERR_FILEERROR(std::string op, std::string file) { return ":File error doing " + op + " on " + file; }
std::string ERR_NONICKNAMEGIVEN() { return ":No nickname given"; }
std::string ERR_ERRONEUSNICKNAME(std::string nick) { return nick + " :Erroneus nickname"; }
std::string ERR_NICKNAMEINUSE(std::string nick) { return nick + " :Nickname is already in use"; }
std::string ERR_NICKCOLLISION(std::string nick) { return nick + " :Nickname collision KILL"; }
std::string ERR_USERNOTINCHANNEL(std::string nick, std::string channel) { return nick + " " + channel + " :They aren't on that channel"; }
std::string ERR_NOTONCHANNEL(std::string channel) { return channel + " :You're not on that channel"; }
std::string ERR_USERONCHANNEL(std::string user, std::string channel) { return user + " " + channel + " :is already on channel"; }
std::string ERR_NOLOGIN(std::string user) { return user + " :User not logged in"; }
std::string ERR_SUMMONDISABLED() { return ":SUMMON has been disabled"; }
std::string ERR_USERSDISABLED() { return ":USERS has been disabled"; }
std::string ERR_NOTREGISTERED() { return ":You have not registered"; }
std::string ERR_NEEDMOREPARAMS(std::string command) { return command + " :Not enough parameters"; }
std::string ERR_ALREADYREGISTRED() { return ":You may not reregister"; }
std::string ERR_NOPERMFORHOST() { return ":Your host isn't among the privileged"; }
std::string ERR_PASSWDMISMATCH() { return ":Password incorrect"; }
std::string ERR_YOUREBANNEDCREEP() { return ":You are banned from this server"; }
std::string ERR_KEYSET(std::string channel) { return channel + " :Channel key already set"; }
std::string ERR_CHANNELISFULL(std::string channel) { return channel + " :Cannot join channel (+l)"; }
std::string ERR_UNKNOWNMODE(std::string c) { return c + " :is unknown mode char to me"; }
std::string ERR_INVITEONLYCHAN(std::string channel) { return channel + " :Cannot join channel (+i)"; }
std::string ERR_BANNEDFROMCHAN(std::string channel) { return channel + " :Cannot join channel (+b)"; }
std::string ERR_BADCHANNELKEY(std::string channel) { return channel + " :Cannot join channel (+k)"; }
std::string ERR_NOPRIVILEGES() { return ":Permission Denied- You're not an IRC operator"; }
std::string ERR_CHANOPRIVSNEEDED(std::string channel) { return channel + " :You're not channel operator"; }
std::string ERR_CANTKILLSERVER() { return ":You cant kill a server!"; }
std::string ERR_NOOPERHOST() { return ":No O-lines for your host"; }
std::string ERR_UMODEUNKNOWNFLAG() { return ":Unknown MODE flag"; }
std::string ERR_USERSDONTMATCH() { return ":Cant change mode for other users"; }

std::string irc::User::generate(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7)
{
	(void)arg3;
	(void)arg4;
	(void)arg5;
	(void)arg6;
	(void)arg7;
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
