#include "Command.hpp"
#include "../User.hpp"

/******************************************************************************/
/*                                   0**                                      */
/******************************************************************************/
std::string RPL_WELCOME(std::string prefix) { return ":Welcome to the Internet Relay Network " + prefix; }
std::string RPL_YOURHOST(std::string servername, std::string ver) { return ":Your host is " + servername + ", running version " + ver; }
std::string RPL_CREATED(std::string date) { return ":This server was created " + date; }
std::string RPL_MYINFO(std::string servername, std::string version, std::string umodes, std::string cmodes) { return servername + " " + version + " " + umodes + " " + cmodes; }
std::string RPL_BOUNCE(std::string server, std::string port) { return ":Try server " + server + ", port " + port; }
/******************************************************************************/
/*                                   2**                                      */
/******************************************************************************/
std::string RPL_TRACELINK(std::string version, std::string destination, std::string server) { return "Link " + version + " " + destination + " " + server; }
std::string RPL_TRACECONNECTING(std::string class1, std::string server) { return "Try. " + class1 + " " + server; }
std::string RPL_TRACEHANDSHAKE(std::string class1, std::string server) { return "H.S. " + class1 + " " + server; }
std::string RPL_TRACEUNKNOWN(std::string class1, std::string ip) { return "???? " + class1 + " " + ip; }
std::string RPL_TRACEOPERATOR(std::string class1, std::string nick) { return "Oper " + class1 + " " + nick; }
std::string RPL_TRACEUSER(std::string class1, std::string nick) { return "User " + class1 + " " + nick; }
std::string RPL_TRACESERVER(std::string class1, std::string int1, std::string int2, std::string server, std::string nick, std::string user, std::string host) { return "Serv " + class1 + " " + int1 + "S " + int2 + "C " + server + " " + nick + "!" + user + "@ " + host; }
std::string RPL_TRACENEWTYPE(std::string type, std::string name) { return type + " 0 " + name; }
std::string RPL_STATSLINKINFO(std::string name, std::string q, std::string smessages, std::string sbytes, std::string rsmessages, std::string rbytes, std::string time) { return name + " " + q + " " + smessages + " " + sbytes + " " + rsmessages + " " + rbytes + " " + time; }
std::string RPL_STATSCOMMANDS(std::string command, std::string count) { return command + " " + count; }
std::string RPL_STATSCLINE(std::string host, std::string name, std::string port, std::string class1) { return "C " + host + " * " + name + " " + port + " " + class1; }
std::string RPL_STATSNLINE(std::string host, std::string name, std::string port, std::string class1) { return "N " + host + " * " + name + " " + port + " " + class1; }
std::string RPL_STATSILINE(std::string host1, std::string host2, std::string port, std::string class1) { return "I " + host1 + " * " + host2 + " " + port + " " + class1; }
std::string RPL_STATSKLINE(std::string host, std::string user, std::string port, std::string class1) { return "K " + host + " * " + user + " " + port + " " + class1; }
std::string RPL_STATSYLINE(std::string class1, std::string ping, std::string connect, std::string max) { return "Y " + class1 + " " + ping + " " + connect + " " + max; }
std::string RPL_ENDOFSTATS(std::string letter) { return letter + " :End of /STATS report"; }
std::string RPL_UMODEIS(std::string mode) { return mode; }
std::string RPL_STATSLLINE(std::string host, std::string name, std::string depth) { return "L " + host + " * " + name + " " + depth; }
std::string RPL_STATSUPTIME() { return ":Server Up %d days %d:%02d:%02d"; }
std::string RPL_STATSOLINE(std::string mask, std::string name) { return "O " + mask + " * " + name; }
std::string RPL_STATSHLINE(std::string mask, std::string name) { return "H " + mask + " * " + name; }
std::string RPL_LUSERCLIENT(std::string int1, std::string int2, std::string int3) { return ":There are " + int1 + " users and " + int2 + " invisible on " + int3 + " servers"; }
std::string RPL_LUSEROP(std::string int1) { return int1 + " :operator(s) online"; }
std::string RPL_LUSERUNKNOWN(std::string int1) { return int1 + " :unknown connection(s)"; }
std::string RPL_LUSERCHANNELS(std::string int1) { return int1 + " :channels formed"; }
std::string RPL_LUSERME(std::string int1, std::string int2) { return ":I have " + int1 + " clients and " + int2 + " servers"; }
std::string RPL_ADMINME(std::string server) { return server + " :Administrative info"; }
std::string RPL_ADMINLOC1(std::string info) { return ":" + info; }
std::string RPL_ADMINLOC2(std::string info) { return ":" + info; }
std::string RPL_ADMINEMAIL(std::string info) { return ":" + info; }
std::string RPL_TRACELOG(std::string file, std::string level) { return "File " + file + " " + level; }
std::string RPL_TRACEEND(std::string server, std::string version) { return server + " " + version + " :End of TRACE"; }
std::string RPL_TRYAGAIN(std::string cmd) { return cmd + " :Please wait a while and try again."; }
/******************************************************************************/
/*                                   3**                                      */
/******************************************************************************/
std::string RPL_NONE() { return ""; }
std::string RPL_AWAY(std::string nick, std::string message) { return nick + " :" + message; }
std::string RPL_USERHOST(std::string reply_list) { return ":" + reply_list; }
std::string RPL_ISON(std::string nick_list) { return ":" + nick_list; }
std::string RPL_UNAWAY() { return ":You are no longer marked as being away"; }
std::string RPL_NOWAWAY() { return ":You have been marked as being away"; }
std::string RPL_WHOISUSER(std::string nick, std::string user, std::string host, std::string real) { return nick + " " + user + " " + host + " * :" + real; }
std::string RPL_WHOISSERVER(std::string nick, std::string server, std::string info) { return nick + " " + server + " :" + info; }
std::string RPL_WHOISOPERATOR(std::string nick) { return nick + " :is an IRC operator"; }
std::string RPL_WHOWASUSER(std::string nick, std::string user, std::string host, std::string real) { return nick + " " + user + " " + host + " * :" + real; }
std::string RPL_ENDOFWHO(std::string name) { return name + " :End of /WHO list"; }
std::string RPL_WHOISIDLE(std::string nick, std::string integer) { return nick + " " + integer + " :seconds idle"; }
std::string RPL_ENDOFWHOIS(std::string nick) { return nick + " :End of /WHOIS list"; }
std::string RPL_WHOISCHANNELS(std::string nick, std::string channel) { return nick + " :" + channel; }
std::string RPL_LISTSTART() { return "Channel :Users  Name"; }
std::string RPL_LIST(std::string channel, std::string topic) { return channel + " :" + topic; }
std::string RPL_LISTEND() { return ":End of /LIST"; }
std::string RPL_CHANNELMODEIS(std::string channel, std::string mode, std::string params) { return channel + " " + mode + " " + params; }
std::string RPL_UNIQOPIS(std::string channel, std::string nick) { return channel + " " + nick; }
std::string RPL_NOTOPIC(std::string channel) { return channel + " :No topic is set"; }
std::string RPL_TOPIC(std::string channel, std::string topic) { return channel + " :" + topic; }
std::string RPL_INVITING(std::string channel, std::string nick) { return nick + " " + channel; }
std::string RPL_SUMMONING(std::string user) { return user + " :Summoning user to IRC"; }
std::string RPL_INVITELIST(std::string channel, std::string inviter) { return channel + " " + inviter; }
std::string RPL_ENDOFINVITELIST(std::string channel) { return channel + " :End of channel invite list"; }
std::string RPL_EXCEPTLIST(std::string channel, std::string mask) { return channel + " " + mask; }
std::string RPL_ENDOFEXCEPTLIST(std::string channel) { return channel + " :End of channel exception list"; }
std::string RPL_VERSION(std::string version, std::string server, std::string comments) { return version + " " + server + " :" + comments; }
std::string RPL_WHOREPLY(std::string channel, std::string user, std::string host, std::string server, std::string nick, std::string hopcout, std::string real) { return channel + " " + user + " " + host + " " + server + " " + nick + " H :" + hopcout + " " + real; }
std::string RPL_NAMREPLY(std::string channel, std::string nick_list) { return channel + " :" + nick_list; }
std::string RPL_LINKS(std::string mask, std::string server, std::string hopcount, std::string info) { return mask + " " + server + " :" + hopcount + " " + info; }
std::string RPL_ENDOFLINKS(std::string mask) { return mask + " :End of /LINKS list"; }
std::string RPL_ENDOFNAMES(std::string channel) { return channel + " :End of /NAMES list"; }
std::string RPL_BANLIST(std::string channel, std::string banip) { return channel + " " + banip; }
std::string RPL_ENDOFBANLIST(std::string channel) { return channel + " :End of channel ban list"; }
std::string RPL_ENDOFWHOWAS(std::string nick) { return nick + " :End of WHOWAS"; }
std::string RPL_INFO(std::string string) { return ":" + string; }
std::string RPL_MOTD(std::string text) { return ":- " + text; }
std::string RPL_ENDOFINFO() { return ":End of /INFO list"; }
std::string RPL_MOTDSTART(std::string server) { return ":- " + server + " Message of the day - "; }
std::string RPL_ENDOFMOTD() { return ":End of /MOTD command"; }
std::string RPL_YOUREOPER() { return ":You are now an IRC operator"; }
std::string RPL_REHASHING(std::string file) { return file + " :Rehashing"; }
std::string RPL_YOURESERVICE(std::string nick) { return ":You are service " + nick; }
std::string RPL_TIME(std::string server, std::string time) { return server + " :" + time; }
std::string RPL_USERSSTART() { return ":UserID Terminal Host"; }
std::string RPL_USERS() { return ":%-8s %-9s %-8s"; }
std::string RPL_ENDOFUSERS() { return ":End of users"; }
std::string RPL_NOUSERS() { return ":Nobody logged in"; }
/******************************************************************************/
/*                                   4**                                      */
/******************************************************************************/
std::string ERR_NOSUCHNICK(std::string nickname) { return nickname + " :No such nick/channel"; }
std::string ERR_NOSUCHSERVER(std::string server) { return server + " :No such server"; }
std::string ERR_NOSUCHCHANNEL(std::string channel) { return channel + " :No such channel"; }
std::string ERR_CANNOTSENDTOCHAN(std::string channel) { return channel + " :Cannot send to channel"; }
std::string ERR_TOOMANYCHANNELS(std::string channel) { return channel + " :You have joined too many channels"; }
std::string ERR_WASNOSUCHNICK(std::string nickname) { return nickname + " :There was no such nickname"; }
std::string ERR_TOOMANYTARGETS(std::string target) { return target + " :Duplicate recipients. No message delivered"; }
std::string ERR_NOSUCHSERVICE(std::string service) { return service + " :No such service"; }
std::string ERR_NOORIGIN() { return ":No origin specified"; }
std::string ERR_NORECIPIENT(std::string command) { return ":No recipient given (" + command + ")"; }
std::string ERR_NOTEXTTOSEND() { return ":No text to send"; }
std::string ERR_NOTOPLEVEL(std::string mask) { return mask + " :No toplevel domain specified"; }
std::string ERR_WILDTOPLEVEL(std::string mask) { return mask + " :Wildcard in toplevel domain"; }
std::string ERR_BADMASK(std::string mask) { return mask + " :Bad Server/host mask"; }
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
std::string ERR_BADCHANMASK(std::string channel) { return channel + " :Bad Channel Mask"; }
std::string ERR_NOCHANMODES(std::string channel) { return channel + " :Channel doesn't support modes"; }
std::string ERR_BANLISTFULL(std::string channel) { return channel + " :Channel list is full"; }
std::string ERR_NOPRIVILEGES() { return ":Permission Denied- You're not an IRC operator"; }
std::string ERR_UNIQOPRIVSNEEDED(std::string channel) { return channel + " :You're not channel operator"; }
std::string ERR_CANTKILLSERVER() { return ":You cant kill a server!"; }
std::string ERR_RESTRICTED() { return ":Your connection is restricted!"; }
std::string ERR_UNIQOPPRIVSNEEDED() { return ":You're not the original channel operator"; }
std::string ERR_NOOPERHOST() { return ":No O-lines for your host"; }
std::string ERR_UMODEUNKNOWNFLAG() { return ":Unknown MODE flag"; }
/******************************************************************************/
/*                                   5**                                      */
/******************************************************************************/
std::string ERR_USERSDONTMATCH() { return ":Cant change mode for other users"; }

//IRCv3
/******************************************************************************/
/*                                   6**                                      */
/******************************************************************************/
/*std::string RPL_STARTTLS() { return ":STARTTLS successful, proceed with TLS handshake"; }
std::string ERR_STARTTLS() { return ":STARTTLS failed (Wrong moon phase)"; }*/
/******************************************************************************/
/*                                   9**                                      */
/******************************************************************************/
/*std::string RPL_LOGGEDIN(std::string nick, std::string ident, std::string host) { return nick + "!" + ident + "@" + host + " :You are now logged in"; }
std::string RPL_LOGGEDOUT(std::string nick, std::string ident, std::string host) { return nick + "!" + ident + "@" + host + " :You are now logged out"; }
std::string ERR_NICKLOCKED() { return ":You must use a nick assigned to you"; }
std::string RPL_SASLSUCCESS() { return ":SASL authentication successful"; }
std::string ERR_SASLFAIL() { return ":SASL authentication failed"; }
std::string ERR_SASLTOOLONG() { return ":SASL message too long"; }
std::string ERR_SASLABORTED() { return ":SASL authentication aborted"; }
std::string ERR_SASLALREADY() { return ":You have already authenticated using SASL"; }
std::string RPL_SASLMECHS(std::string mecha) { return mecha + " :are available SASL mechanisms"; }*/

std::string irc::Command::getReplies(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7)
{
	std::string client;
	if (user->isRegistered())
		client = user->getNickname();
	else
		client = "*";
	client += " ";

	switch (code)
	{
	case 001:
		return client + RPL_WELCOME(arg1);
	case 002:
		return client + RPL_YOURHOST(arg1, arg2);
	case 003:
		return client + RPL_CREATED(arg1);
	case 004:
		return client + RPL_MYINFO(arg1, arg2, arg3, arg4);
	case 005:
		return client + RPL_BOUNCE(arg1, arg2);
	case 200:
		return client + RPL_TRACELINK(arg1, arg2, arg3);
	case 201:
		return client + RPL_TRACECONNECTING(arg1, arg2);
	case 202:
		return client + RPL_TRACEHANDSHAKE(arg1, arg2);
	case 203:
		return client + RPL_TRACEUNKNOWN(arg1, arg2);
	case 204:
		return client + RPL_TRACEOPERATOR(arg1, arg2);
	case 205:
		return client + RPL_TRACEUSER(arg1, arg2);
	case 206:
		return client + RPL_TRACESERVER(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	case 208:
		return client + RPL_TRACENEWTYPE(arg1, arg2);
	case 211:
		return client + RPL_STATSLINKINFO(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	case 212:
		return client + RPL_STATSCOMMANDS(arg1, arg2);
	case 213:
		return client + RPL_STATSCLINE(arg1, arg2, arg3, arg4);
	case 214:
		return client + RPL_STATSNLINE(arg1, arg2, arg3, arg4);
	case 215:
		return client + RPL_STATSILINE(arg1, arg2, arg3, arg4);
	case 216:
		return client + RPL_STATSKLINE(arg1, arg2, arg3, arg4);
	case 218:
		return client + RPL_STATSYLINE(arg1, arg2, arg3, arg4);
	case 219:
		return client + RPL_ENDOFSTATS(arg1);
	case 221:
		return client + RPL_UMODEIS(arg1);
	case 241:
		return client + RPL_STATSLLINE(arg1, arg2, arg3);
	case 242:
		return client + RPL_STATSUPTIME();
	case 243:
		return client + RPL_STATSOLINE(arg1, arg2);
	case 244:
		return client + RPL_STATSHLINE(arg1, arg2);
	case 251:
		return client + RPL_LUSERCLIENT(arg1, arg2, arg3);
	case 252:
		return client + RPL_LUSEROP(arg1);
	case 253:
		return client + RPL_LUSERUNKNOWN(arg1);
	case 254:
		return client + RPL_LUSERCHANNELS(arg1);
	case 255:
		return client + RPL_LUSERME(arg1, arg1);
	case 256:
		return client + RPL_ADMINME(arg1);
	case 257:
		return client + RPL_ADMINLOC1(arg1);
	case 258:
		return client + RPL_ADMINLOC2(arg1);
	case 259:
		return client + RPL_ADMINEMAIL(arg1);
	case 261:
		return client + RPL_TRACELOG(arg1, arg2);
	case 262:
		return client + RPL_TRACEEND(arg1, arg2);
	case 263:
		return client + RPL_TRYAGAIN(arg1);

	case 300:
		return client + RPL_NONE();
	case 301:
		return client + RPL_AWAY(arg1, arg2);
	case 302:
		return client + RPL_USERHOST(arg1);
	case 303:
		return client + RPL_ISON(arg1);
	case 305:
		return client + RPL_UNAWAY();
	case 306:
		return client + RPL_NOWAWAY();
	case 311:
		return client + RPL_WHOISUSER(arg1, arg2, arg3, arg4);
	case 312:
		return client + RPL_WHOISSERVER(arg1, arg2, arg3);
	case 313:
		return client + RPL_WHOISOPERATOR(arg1);
	case 314:
		return client + RPL_WHOWASUSER(arg1, arg2, arg3, arg4);
	case 315:
		return client + RPL_ENDOFWHO(arg1);
	case 317:
		return client + RPL_WHOISIDLE(arg1, arg2);
	case 318:
		return client + RPL_ENDOFWHOIS(arg1);
	case 319:
		return client + RPL_WHOISCHANNELS(arg1, arg2);
	case 321:
		return client + RPL_LISTSTART();
	case 322:
		return client + RPL_LIST(arg1, arg2);
	case 323:
		return client + RPL_LISTEND();
	case 324:
		return client + RPL_CHANNELMODEIS(arg1, arg2, arg3);
	case 325:
		return client + RPL_UNIQOPIS(arg1, arg2);
	case 331:
		return client + RPL_NOTOPIC(arg1);
	case 332:
		return client + RPL_TOPIC(arg1, arg2);
	case 341:
		return client + RPL_INVITING(arg1, arg2);
	case 342:
		return client + RPL_SUMMONING(arg1);
	case 346:
		return client + RPL_INVITELIST(arg1, arg2);
	case 347:
		return client + RPL_ENDOFINVITELIST(arg1);
	case 348:
		return client + RPL_EXCEPTLIST(arg1, arg2);
	case 351:
		return client + RPL_VERSION(arg1, arg2, arg3);
	case 352:
		return client + RPL_WHOREPLY(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	case 353:
		return client + RPL_NAMREPLY(arg1, arg2);
	case 364:
		return client + RPL_LINKS(arg1, arg2, arg3, arg4);
	case 365:
		return client + RPL_ENDOFLINKS(arg1);
	case 366:
		return client + RPL_ENDOFNAMES(arg1);
	case 367:
		return client + RPL_BANLIST(arg1, arg2);
	case 368:
		return client + RPL_ENDOFBANLIST(arg1);
	case 369:
		return client + RPL_ENDOFWHOWAS(arg1);
	case 371:
		return client + RPL_INFO(arg1);
	case 372:
		return client + RPL_MOTD(arg1);
	case 374:
		return client + RPL_ENDOFINFO();
	case 375:
		return client + RPL_MOTDSTART(arg1);
	case 376:
		return client + RPL_ENDOFMOTD();
	case 381:
		return client + RPL_YOUREOPER();
	case 382:
		return client + RPL_REHASHING(arg1);
	case 383:
		return client + RPL_YOURESERVICE(arg1);
	case 391:
		return client + RPL_TIME(arg1, arg2);
	case 392:
		return client + RPL_USERSSTART();
	case 393:
		return client + RPL_USERS();
	case 394:
		return client + RPL_ENDOFUSERS();
	case 395:
		return client + RPL_NOUSERS();

	case 401:
		return client + ERR_NOSUCHNICK(arg1);
	case 402:
		return client + ERR_NOSUCHSERVER(arg1);
	case 403:
		return client + ERR_NOSUCHCHANNEL(arg1);
	case 404:
		return client + ERR_CANNOTSENDTOCHAN(arg1);
	case 405:
		return client + ERR_TOOMANYCHANNELS(arg1);
	case 406:
		return client + ERR_WASNOSUCHNICK(arg1);
	case 407:
		return client + ERR_TOOMANYTARGETS(arg1);
	case 408:
		return client + ERR_NOSUCHSERVICE(arg1);
	case 409:
		return client + ERR_NOORIGIN();
	case 411:
		return client + ERR_NORECIPIENT(arg1);
	case 412:
		return client + ERR_NOTEXTTOSEND();
	case 413:
		return client + ERR_NOTOPLEVEL(arg1);
	case 414:
		return client + ERR_WILDTOPLEVEL(arg1);
	case 415:
		return client + ERR_BADMASK(arg1);
	case 421:
		return client + ERR_UNKNOWNCOMMAND(arg1);
	case 422:
		return client + ERR_NOMOTD();
	case 423:
		return client + ERR_NOADMININFO(arg1);
	case 424:
		return client + ERR_FILEERROR(arg1, arg2);
	case 431:
		return client + ERR_NONICKNAMEGIVEN();
	case 432:
		return client + ERR_ERRONEUSNICKNAME(arg1);
	case 433:
		return client + ERR_NICKNAMEINUSE(arg1);
	case 436:
		return client + ERR_NICKCOLLISION(arg1);
	case 441:
		return client + ERR_USERNOTINCHANNEL(arg1, arg2);
	case 442:
		return client + ERR_NOTONCHANNEL(arg1);
	case 443:
		return client + ERR_USERONCHANNEL(arg1, arg2);
	case 444:
		return client + ERR_NOLOGIN(arg1);
	case 445:
		return client + ERR_SUMMONDISABLED();
	case 446:
		return client + ERR_USERSDISABLED();
	case 451:
		return client + ERR_NOTREGISTERED();

	case 461:
		return client + ERR_NEEDMOREPARAMS(arg1);
	case 462:
		return client + ERR_ALREADYREGISTRED();
	case 463:
		return client + ERR_NOPERMFORHOST();
	case 464:
		return client + ERR_PASSWDMISMATCH();
	case 465:
		return client + ERR_YOUREBANNEDCREEP();
	case 467:
		return client + ERR_KEYSET(arg1);
	case 471:
		return client + ERR_CHANNELISFULL(arg1);
	case 472:
		return client + ERR_UNKNOWNMODE(arg1);
	case 473:
		return client + ERR_INVITEONLYCHAN(arg1);
	case 474:
		return client + ERR_BANNEDFROMCHAN(arg1);
	case 475:
		return client + ERR_BADCHANNELKEY(arg1);
	case 476:
		return client + ERR_BADCHANMASK(arg1);
	case 477:
		return client + ERR_NOCHANMODES(arg1);
	case 478:
		return client + ERR_BANLISTFULL(arg1);
	case 481:
		return client + ERR_NOPRIVILEGES();
	case 482:
		return client + ERR_UNIQOPRIVSNEEDED(arg1);
	case 483:
		return client + ERR_CANTKILLSERVER();
	case 484:
		return client + ERR_RESTRICTED();
	case 485:
		return client + ERR_UNIQOPPRIVSNEEDED();
	case 491:
		return client + ERR_NOOPERHOST();

	case 501:
		return client + ERR_UMODEUNKNOWNFLAG();
	case 502:
		return client + ERR_USERSDONTMATCH();

	/*IRCv3
	case 670:
		return client + RPL_STARTTLS();
		
	case 691:
		return client + ERR_STARTTLS();
		

	case 900:
		return client + RPL_LOGGEDIN(arg1, arg2, arg3);
		
	case 901:
		return client + RPL_LOGGEDOUT(arg1, arg2, arg3);
		
	case 902:
		return client + ERR_NICKLOCKED();
		
	case 903:
		return client + RPL_SASLSUCCESS();
		
	case 904:
		return client + ERR_SASLFAIL();
		
	case 905:
		return client + ERR_SASLTOOLONG();
		
	case 906:
		return client + ERR_SASLABORTED();
		
	case 907:
		return client + ERR_SASLALREADY();
		
	case 908:
		return client + RPL_SASLMECHS(arg1);
		*/
	default:
		return std::string();
	}
}
