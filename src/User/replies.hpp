#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

namespace irc
{
	std::string generate(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);

	std::string ERR_NOSUCHNICK(std::string nickname);
	std::string ERR_NOSUCHSERVER(std::string server);
	std::string ERR_NOSUCHCHANNEL(std::string channel);
	std::string ERR_CANNOTSENDTOCHAN(std::string channel);
	std::string ERR_TOOMANYCHANNELS(std::string channel);
	std::string ERR_WASNOSUCHNICK(std::string nickname);
	std::string ERR_TOOMANYTARGETS(std::string target);
	std::string ERR_NOORIGIN();
	std::string ERR_NORECIPIENT(std::string command);
	std::string ERR_NOTEXTTOSEND();
	std::string ERR_NOTOPLEVEL(std::string mask);
	std::string ERR_WILDTOPLEVEL(std::string mask);
	std::string ERR_UNKNOWNCOMMAND(std::string command);
	std::string ERR_NOMOTD();
	std::string ERR_NOADMININFO(std::string server);
	std::string ERR_FILEERROR(std::string op, std::string file);
	std::string ERR_NONICKNAMEGIVEN();
	std::string ERR_ERRONEUSNICKNAME(std::string nick);
	std::string ERR_NICKNAMEINUSE(std::string nick);
	std::string ERR_NICKCOLLISION(std::string nick);
	std::string ERR_USERNOTINCHANNEL(std::string nick, std::string channel);
	std::string ERR_NOTONCHANNEL(std::string channel);
	std::string ERR_USERONCHANNEL(std::string user, std::string channel);
	std::string ERR_NOLOGIN(std::string user);
	std::string ERR_SUMMONDISABLED();
	std::string ERR_USERSDISABLED();
	std::string ERR_NOTREGISTERED();
	std::string ERR_NEEDMOREPARAMS(std::string command);
	std::string ERR_ALREADYREGISTRED();
	std::string ERR_NOPERMFORHOST();
	std::string ERR_PASSWDMISMATCH();
	std::string ERR_YOUREBANNEDCREEP();
	std::string ERR_KEYSET(std::string channel);
	std::string ERR_CHANNELISFULL(std::string channel);
	std::string ERR_UNKNOWNMODE(std::string c);
	std::string ERR_INVITEONLYCHAN(std::string channel);
	std::string ERR_BANNEDFROMCHAN(std::string channel);
	std::string ERR_BADCHANNELKEY(std::string channel);
	std::string ERR_NOPRIVILEGES();
	std::string ERR_CHANOPRIVSNEEDED(std::string channel);
	std::string ERR_CANTKILLSERVER();
	std::string ERR_NOOPERHOST();
	std::string ERR_UMODEUNKNOWNFLAG();
	std::string ERR_USERSDONTMATCH();
}
#endif
