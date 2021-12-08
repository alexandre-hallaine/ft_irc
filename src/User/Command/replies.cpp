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
/******************************************************************************/
/*                                   6**                                      */
/******************************************************************************/
std::string RPL_STARTTLS() { return ":STARTTLS successful, proceed with TLS handshake"; }
std::string ERR_STARTTLS() { return ":STARTTLS failed (Wrong moon phase)"; }
/******************************************************************************/
/*                                   9**                                      */
/******************************************************************************/
std::string RPL_LOGGEDIN(std::string nick, std::string ident, std::string host) { return nick + "!" + ident + "@" + host + " :You are now logged in"; }
std::string RPL_LOGGEDOUT(std::string nick, std::string ident, std::string host) { return nick + "!" + ident + "@" + host + " :You are now logged out"; }
std::string ERR_NICKLOCKED() { return ":You must use a nick assigned to you"; }
std::string RPL_SASLSUCCESS() { return ":SASL authentication successful"; }
std::string ERR_SASLFAIL() { return ":SASL authentication failed"; }
std::string ERR_SASLTOOLONG() { return ":SASL message too long"; }
std::string ERR_SASLABORTED() { return ":SASL authentication aborted"; }
std::string ERR_SASLALREADY() { return ":You have already authenticated using SASL"; }
std::string RPL_SASLMECHS(std::string mecha) { return mecha + " :are available SASL mechanisms"; }

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
	std::string params = user->getUsername() + " ";
	switch (code)
	{
	case 001:
		params += RPL_WELCOME(arg1);
		break;
	case 002:
		params += RPL_YOURHOST(arg1, arg2);
		break;
	case 003:
		params += RPL_CREATED(arg1);
		break;
	case 004:
		params += RPL_MYINFO(arg1, arg2, arg3, arg4);
		break;
	case 005:
		params += RPL_BOUNCE(arg1, arg2);
		break;

	case 200:
		params += RPL_TRACELINK(arg1, arg2, arg3);
		break;
	case 201:
		params += RPL_TRACECONNECTING(arg1, arg2);
		break;
	case 202:
		params += RPL_TRACEHANDSHAKE(arg1, arg2);
		break;
	case 203:
		params += RPL_TRACEUNKNOWN(arg1, arg2);
		break;
	case 204:
		params += RPL_TRACEOPERATOR(arg1, arg2);
		break;
	case 205:
		params += RPL_TRACEUSER(arg1, arg2);
		break;
	case 206:
		params += RPL_TRACESERVER(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		break;
	case 208:
		params += RPL_TRACENEWTYPE(arg1, arg2);
		break;
	case 211:
		params += RPL_STATSLINKINFO(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		break;
	case 212:
		params += RPL_STATSCOMMANDS(arg1, arg2);
		break;
	case 213:
		params += RPL_STATSCLINE(arg1, arg2, arg3, arg4);
		break;
	case 214:
		params += RPL_STATSNLINE(arg1, arg2, arg3, arg4);
		break;
	case 215:
		params += RPL_STATSILINE(arg1, arg2, arg3, arg4);
		break;
	case 216:
		params += RPL_STATSKLINE(arg1, arg2, arg3, arg4);
		break;
	case 218:
		params += RPL_STATSYLINE(arg1, arg2, arg3, arg4);
		break;
	case 219:
		params += RPL_ENDOFSTATS(arg1);
		break;
	case 221:
		params += RPL_UMODEIS(arg1);
		break;
	case 241:
		params += RPL_STATSLLINE(arg1, arg2, arg3);
		break;
	case 242:
		params += RPL_STATSUPTIME();
		break;
	case 243:
		params += RPL_STATSOLINE(arg1, arg2);
		break;
	case 244:
		params += RPL_STATSHLINE(arg1, arg2);
		break;
	case 251:
		params += RPL_LUSERCLIENT(arg1, arg2, arg3);
		break;
	case 252:
		params += RPL_LUSEROP(arg1);
		break;
	case 253:
		params += RPL_LUSERUNKNOWN(arg1);
		break;
	case 254:
		params += RPL_LUSERCHANNELS(arg1);
		break;
	case 255:
		params += RPL_LUSERME(arg1, arg1);
		break;
	case 256:
		params += RPL_ADMINME(arg1);
		break;
	case 257:
		params += RPL_ADMINLOC1(arg1);
		break;
	case 258:
		params += RPL_ADMINLOC2(arg1);
		break;
	case 259:
		params += RPL_ADMINEMAIL(arg1);
		break;
	case 261:
		params += RPL_TRACELOG(arg1, arg2);
		break;
	case 262:
		params += RPL_TRACEEND(arg1, arg2);
		break;
	case 263:
		params += RPL_TRYAGAIN(arg1);
		break;
	case 300:
		params += RPL_NONE();
		break;
	case 301:
		params += RPL_AWAY(arg1, arg2);
		break;
	case 302:
		params += RPL_USERHOST(arg1);
		break;
	case 303:
		params += RPL_ISON(arg1);
		break;
	case 305:
		params += RPL_UNAWAY();
		break;
	case 306:
		params += RPL_NOWAWAY();
		break;
	case 311:
		params += RPL_WHOISUSER(arg1, arg2, arg3, arg4);
		break;
	case 312:
		params += RPL_WHOISSERVER(arg1, arg2, arg3);
		break;
	case 313:
		params += RPL_WHOISOPERATOR(arg1);
		break;
	case 314:
		params += RPL_WHOWASUSER(arg1, arg2, arg3, arg4);
		break;
	case 315:
		params += RPL_ENDOFWHO(arg1);
		break;
	case 317:
		params += RPL_WHOISIDLE(arg1, arg2);
		break;
	case 318:
		params += RPL_ENDOFWHOIS(arg1);
		break;
	case 319:
		params += RPL_WHOISCHANNELS(arg1, arg2);
		break;
	case 321:
		params += RPL_LISTSTART();
		break;
	case 322:
		params += RPL_LIST(arg1, arg2);
		break;
	case 323:
		params += RPL_LISTEND();
		break;
	case 324:
		params += RPL_CHANNELMODEIS(arg1, arg2, arg3);
		break;
	case 325:
		params += RPL_UNIQOPIS(arg1, arg2);
		break;
	case 331:
		params += RPL_NOTOPIC(arg1);
		break;
	case 332:
		params += RPL_TOPIC(arg1, arg2);
		break;
	case 341:
		params += RPL_INVITING(arg1, arg2);
		break;
	case 342:
		params += RPL_SUMMONING(arg1);
		break;
	case 346:
		params += RPL_INVITELIST(arg1, arg2);
		break;
	case 347:
		params += RPL_ENDOFINVITELIST(arg1);
		break;
	case 348:
		params += RPL_EXCEPTLIST(arg1, arg2);
		break;
	case 351:
		params += RPL_VERSION(arg1, arg2, arg3);
		break;
	case 352:
		params += RPL_WHOREPLY(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		break;
	case 353:
		params += RPL_NAMREPLY(arg1, arg2);
		break;
	case 364:
		params += RPL_LINKS(arg1, arg2, arg3, arg4);
		break;
	case 365:
		params += RPL_ENDOFLINKS(arg1);
		break;
	case 366:
		params += RPL_ENDOFNAMES(arg1);
		break;
	case 367:
		params += RPL_BANLIST(arg1, arg2);
		break;
	case 368:
		params += RPL_ENDOFBANLIST(arg1);
		break;
	case 369:
		params += RPL_ENDOFWHOWAS(arg1);
		break;
	case 371:
		params += RPL_INFO(arg1);
		break;
	case 372:
		params += RPL_MOTD(arg1);
		break;
	case 374:
		params += RPL_ENDOFINFO();
		break;
	case 375:
		params += RPL_MOTDSTART(arg1);
		break;
	case 376:
		params += RPL_ENDOFMOTD();
		break;
	case 381:
		params += RPL_YOUREOPER();
		break;
	case 382:
		params += RPL_REHASHING(arg1);
		break;
	case 383:
		params += RPL_YOURESERVICE(arg1);
		break;
	case 391:
		params += RPL_TIME(arg1, arg2);
		break;
	case 392:
		params += RPL_USERSSTART();
		break;
	case 393:
		params += RPL_USERS();
		break;
	case 394:
		params += RPL_ENDOFUSERS();
		break;
	case 395:
		params += RPL_NOUSERS();
		break;

	case 401:
		params += ERR_NOSUCHNICK(arg1);
		break;
	case 402:
		params += ERR_NOSUCHSERVER(arg1);
		break;
	case 403:
		params += ERR_NOSUCHCHANNEL(arg1);
		break;
	case 404:
		params += ERR_CANNOTSENDTOCHAN(arg1);
		break;
	case 405:
		params += ERR_TOOMANYCHANNELS(arg1);
		break;
	case 406:
		params += ERR_WASNOSUCHNICK(arg1);
		break;
	case 407:
		params += ERR_TOOMANYTARGETS(arg1);
		break;
	case 408:
		params += ERR_NOSUCHSERVICE(arg1);
		break;
	case 409:
		params += ERR_NOORIGIN();
		break;
	case 411:
		params += ERR_NORECIPIENT(arg1);
		break;
	case 412:
		params += ERR_NOTEXTTOSEND();
		break;
	case 413:
		params += ERR_NOTOPLEVEL(arg1);
		break;
	case 414:
		params += ERR_WILDTOPLEVEL(arg1);
		break;
	case 415:
		params += ERR_BADMASK(arg1);
		break;
	case 421:
		params += ERR_UNKNOWNCOMMAND(arg1);
		break;
	case 422:
		params += ERR_NOMOTD();
		break;
	case 423:
		params += ERR_NOADMININFO(arg1);
		break;
	case 424:
		params += ERR_FILEERROR(arg1, arg2);
		break;
	case 431:
		params += ERR_NONICKNAMEGIVEN();
		break;
	case 432:
		params += ERR_ERRONEUSNICKNAME(arg1);
		break;
	case 433:
		params += ERR_NICKNAMEINUSE(arg1);
		break;
	case 436:
		params += ERR_NICKCOLLISION(arg1);
		break;
	case 441:
		params += ERR_USERNOTINCHANNEL(arg1, arg2);
		break;
	case 442:
		params += ERR_NOTONCHANNEL(arg1);
		break;
	case 443:
		params += ERR_USERONCHANNEL(arg1, arg2);
		break;
	case 444:
		params += ERR_NOLOGIN(arg1);
		break;
	case 445:
		params += ERR_SUMMONDISABLED();
		break;
	case 446:
		params += ERR_USERSDISABLED();
		break;
	case 451:
		params += ERR_NOTREGISTERED();
		break;
	case 461:
		params += ERR_NEEDMOREPARAMS(arg1);
		break;
	case 462:
		params += ERR_ALREADYREGISTRED();
		break;
	case 463:
		params += ERR_NOPERMFORHOST();
		break;
	case 464:
		params += ERR_PASSWDMISMATCH();
		break;
	case 465:
		params += ERR_YOUREBANNEDCREEP();
		break;
	case 467:
		params += ERR_KEYSET(arg1);
		break;
	case 471:
		params += ERR_CHANNELISFULL(arg1);
		break;
	case 472:
		params += ERR_UNKNOWNMODE(arg1);
		break;
	case 473:
		params += ERR_INVITEONLYCHAN(arg1);
		break;
	case 474:
		params += ERR_BANNEDFROMCHAN(arg1);
		break;
	case 475:
		params += ERR_BADCHANNELKEY(arg1);
		break;
	case 476:
		params += ERR_BADCHANMASK(arg1);
		break;
	case 477:
		params += ERR_NOCHANMODES(arg1);
		break;
	case 478:
		params += ERR_BANLISTFULL(arg1);
		break;
	case 481:
		params += ERR_NOPRIVILEGES();
		break;
	case 482:
		params += ERR_UNIQOPRIVSNEEDED(arg1);
		break;
	case 483:
		params += ERR_CANTKILLSERVER();
		break;
	case 484:
		params += ERR_RESTRICTED();
		break;
	case 485:
		params += ERR_UNIQOPPRIVSNEEDED();
		break;
	case 491:
		params += ERR_NOOPERHOST();
		break;

	case 501:
		params += ERR_UMODEUNKNOWNFLAG();
		break;
	case 502:
		params += ERR_USERSDONTMATCH();
		break;

		/*IRCv3
	case 670:
		params += RPL_STARTTLS();
		break;
	case 691:
		params += ERR_STARTTLS();
		break;

	case 900:
		params += RPL_LOGGEDIN(arg1, arg2, arg3);
		break;
	case 901:
		params += RPL_LOGGEDOUT(arg1, arg2, arg3);
		break;
	case 902:
		params += ERR_NICKLOCKED();
		break;
	case 903:
		params += RPL_SASLSUCCESS();
		break;
	case 904:
		params += ERR_SASLFAIL();
		break;
	case 905:
		params += ERR_SASLTOOLONG();
		break;
	case 906:
		params += ERR_SASLABORTED();
		break;
	case 907:
		params += ERR_SASLALREADY();
		break;
	case 908:
		params += RPL_SASLMECHS(arg1);
		break;*/
	}
	return params;
}
