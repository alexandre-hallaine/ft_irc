#include "User.hpp"
#include "Command/Command.hpp"
#include "../Utils/Utils.hpp"
#include "../Server/Server.hpp"
#include <fcntl.h>
#include <iostream>
#include <sys/socket.h>
#include <algorithm>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>

#define BUFFER_SIZE 4096
#define MESSAGE_END "\r\n"

void CAP(irc::Command *command);
void PASS(irc::Command *command);
void NICK(irc::Command *command);
void USER(irc::Command *command);
void OPER(irc::Command *command);
void MODE(irc::Command *command);
void SERVICE(irc::Command *command);
void QUIT(irc::Command *command);
void SQUIT(irc::Command *command);

void JOIN(irc::Command *command);
void PART(irc::Command *command);
void TOPIC(irc::Command *command);
void NAMES(irc::Command *command);
void LIST(irc::Command *command);
void INVITE(irc::Command *command);
void KICK(irc::Command *command);

void PRIVMSG(irc::Command *command);
void NOTICE(irc::Command *command);

void MOTD(irc::Command *command);
void LUSERS(irc::Command *command);
void VERSION(irc::Command *command);
void STATS(irc::Command *command);
void LINKS(irc::Command *command);
void TIME(irc::Command *command);
void CONNECT(irc::Command *command);
void TRACE(irc::Command *command);
void ADMIN(irc::Command *command);
void INFO(irc::Command *command);
void SERVLIST(irc::Command *command);
void SQUERY(irc::Command *command);

void WHO(irc::Command *command);
void WHOIS(irc::Command *command);
void WHOWAS(irc::Command *command);

void KILL(irc::Command *command);
void PING(irc::Command *command);
void PONG(irc::Command *command);
void ERROR(irc::Command *command);

void AWAY(irc::Command *command);
void REHASH(irc::Command *command);
void DIE(irc::Command *command);
void RESTART(irc::Command *command);
void SUMMON(irc::Command *command);
void USERS(irc::Command *command);
void WALLOPS(irc::Command *command);
void USERHOST(irc::Command *command);
void ISON(irc::Command *command);

void post_registration(irc::Command *command)
{
	command->reply(1, command->getUser().getPrefix());
	command->reply(2, command->getUser().getHostname(), command->getServer().getConfig().get("version"));
	command->reply(3, command->getServer().getUpTime());
	command->reply(4, command->getServer().getConfig().get("name"), command->getServer().getConfig().get("version"), command->getServer().getConfig().get("user_mode"), command->getServer().getConfig().get("channel_givemode") + command->getServer().getConfig().get("channel_togglemode") + command->getServer().getConfig().get("channel_setmode"));

	LUSERS(command);
	MOTD(command);
}
void irc::User::dispatch()
{
	UserStatus last_status = status;

	if (last_status == DELETE)
		return;

	std::vector<Command *> remove = std::vector<Command *>();
	for (std::vector<Command *>::iterator it = commands.begin(); it != commands.end(); ++it)
	{
		if (last_status == CAPLS)
		{
			if ((*it)->getPrefix() != "CAP")
				continue;
		}
		else if (last_status == PASSWORD)
		{
			if ((*it)->getPrefix() != "PASS")
				continue;
		}
		else if (last_status == REGISTER)
		{
			if ((*it)->getPrefix() != "NICK" && (*it)->getPrefix() != "USER")
				continue;
		}
		if (command_function.count((*it)->getPrefix()))
			command_function[(*it)->getPrefix()]((*it));
		else if (DEBUG) {
			time_t t = time(0);
			struct tm * now = localtime( & t );
			char buffer[80];
			strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", now);
			std::cout << "[" << buffer << "] " << "Unknown command: " << (*it)->getPrefix() << std::endl;
		}
		remove.push_back((*it));
	}

	for (std::vector<Command *>::iterator it = remove.begin(); it != remove.end(); ++it)
		if (std::find(commands.begin(), commands.end(), *it) != commands.end())
		{
			commands.erase(std::find(commands.begin(), commands.end(), *it));
			delete *it;
		}
	remove.clear();

	if (last_status == REGISTER)
		if (nickname.length() && realname.length())
			status = ONLINE;

	if (last_status != status)
	{
		if (status == ONLINE) {
			Command *command = new Command(this, server, "");
			post_registration(command);
			delete command;
		}
		dispatch();
	}
}
void irc::User::receive()
{
	{
		char buffer[BUFFER_SIZE + 1];
		ssize_t size;
		if ((size = recv(fd, &buffer, BUFFER_SIZE, 0)) == -1)
			return;

		if (size == 0)
		{
			status = DELETE;
			return;
		}
		buffer[size] = 0;

		this->buffer += buffer;
	}

	std::string delimiter(MESSAGE_END);
	size_t position;
	while ((position = buffer.find(delimiter)) != std::string::npos)
	{
		std::string message = buffer.substr(0, position);
		buffer.erase(0, position + delimiter.length());
		if (!message.length())
			continue;

		if (DEBUG)
		{
			time_t t = time(0);
			struct tm * now = localtime( & t );
			char buffer[80];
			strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", now);
			std::cout << "[" << buffer << "] " << fd << " < " << message << std::endl;
		}
		commands.push_back(new Command(this, server, message));
	}
	dispatch();
}
void irc::User::write(std::string message) { waitingToSend.push_back(message); }
void irc::User::push()
{
	if (!waitingToSend.size())
		return;

	std::string buffer;
	for (std::vector<std::string>::iterator it = waitingToSend.begin(); it != waitingToSend.end(); ++it)
	{
		if (DEBUG)
		{
			time_t t = time(0);
			struct tm * now = localtime( & t );
			char buffer[80];
			strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", now);
			std::cout << "[" << buffer << "] " << fd << " > " << *it << std::endl;
		}
		buffer += *it + MESSAGE_END;
	}
	waitingToSend.clear();

	if (buffer.length())
		if (send(fd, buffer.c_str(), buffer.length(), 0) == -1)
			error("send", false);
}

irc::User::User(int fd, Server *server, struct sockaddr_in address): command_function(),

													  fd(fd),
													  buffer(),
													  commands(),
													  waitingToSend(),

													  server(server),
													  status(CAPLS),
													  last_ping(std::time(0)),
													  hostaddr(),
													  hostname(),
													  nickname(),
													  username(),
													  realname(),

													  mode("w"),
													  pastnick(),
													  lastChannel("*"),
													  deleteMessage(),
													  awayMessage()
{
	fcntl(fd, F_SETFL, O_NONBLOCK);

	hostaddr = inet_ntoa(address.sin_addr);
	char hostname[NI_MAXHOST];
	if (getnameinfo((struct sockaddr *)&address, sizeof(address), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) != 0)
		error("getnameinfo", false);
	else
		this->hostname = hostname;

	command_function["CAP"] = CAP;
	command_function["PASS"] = PASS;
	command_function["NICK"] = NICK;
	command_function["USER"] = USER;
	command_function["OPER"] = OPER;
	command_function["MODE"] = MODE;
	command_function["SERVICE"] = SERVICE;
	command_function["QUIT"] = QUIT;
	command_function["SQUIT"] = SQUIT;

	command_function["JOIN"] = JOIN;
	command_function["PART"] = PART;
	command_function["TOPIC"] = TOPIC;
	command_function["NAMES"] = NAMES;
	command_function["LIST"] = LIST;
	command_function["INVITE"] = INVITE;
	command_function["KICK"] = KICK;

	command_function["PRIVMSG"] = PRIVMSG;
	command_function["NOTICE"] = NOTICE;

	command_function["MOTD"] = MOTD;
	command_function["LUSERS"] = LUSERS;
	command_function["VERSION"] = VERSION;
	command_function["STATS"] = STATS;
	command_function["LINKS"] = LINKS;
	command_function["TIME"] = TIME;
	command_function["CONNECT"] = CONNECT;
	command_function["TRACE"] = TRACE;
	command_function["ADMIN"] = ADMIN;
	command_function["INFO"] = INFO;

	command_function["SERVLIST"] = SERVLIST;
	command_function["SQUERY"] = SQUERY;

	command_function["WHO"] = WHO;
	command_function["WHOIS"] = WHOIS;
	command_function["WHOWAS"] = WHOWAS;

	command_function["KILL"] = KILL;
	command_function["PING"] = PING;
	command_function["PONG"] = PONG;
	command_function["ERROR"] = ERROR;

	command_function["AWAY"] = AWAY;
	command_function["REHASH"] = REHASH;
	command_function["DIE"] = DIE;
	command_function["RESTART"] = RESTART;
	command_function["SUMMON"] = SUMMON;
	command_function["USERS"] = USERS;
	command_function["WALLOPS"] = WALLOPS;
	command_function["USERHOST"] = USERHOST;
	command_function["ISON"] = ISON;
}
irc::User::~User() { close(fd); }

void irc::User::sendTo(irc::User &toUser, std::string message, std::string delimiter)
{
	if (!delimiter.length())
		return toUser.write(message);
	toUser.write(delimiter + this->getPrefix() + " " + message);
}

void irc::User::setStatus(UserStatus status) { this->status = status; }
void irc::User::setLastPing(time_t last_ping) { this->last_ping = last_ping; }
void irc::User::setNickname(std::string nickname) { this->nickname = nickname; }
void irc::User::setUsername(std::string username) { this->username = username; }
void irc::User::setRealname(std::string realname) { this->realname = realname; }

int irc::User::getFd() { return fd; }
irc::UserStatus irc::User::getStatus() { return status; }
time_t irc::User::getLastPing() { return last_ping; }
std::string irc::User::getPrefix()
{
	if (status == CAPLS || status == PASSWORD || status == REGISTER)
		return std::string("");

	std::string prefix = nickname;
	if (getHost().length())
	{
		if (username.length())
			prefix += "!" + username;
		prefix += "@" + getHost();
	}
	return prefix;
}
std::string irc::User::getHostaddr() { return hostname; }
std::string irc::User::getHostname() { return hostname; }
std::string irc::User::getHost()
{
	if (hostname.size())
		return hostname;
	return hostaddr;
}
std::string irc::User::getNickname() { return nickname; }
std::string irc::User::getUsername() { return username; }
std::string irc::User::getRealname() { return realname; }

void irc::User::setMode(std::string mode) { this->mode = mode; }
void irc::User::setPastnick(std::string pastnick) { this->pastnick = pastnick; }
void irc::User::setLastChannel(std::string lastChannel) { this->lastChannel = lastChannel; }
void irc::User::setDeleteMessage(std::string message) { deleteMessage = message; }
void irc::User::setAwayMessage(std::string message) { awayMessage = message; }

std::string irc::User::getMode() { return mode; }
std::string irc::User::getPastnick() { return pastnick; }
std::string irc::User::getLastChannel() { return lastChannel; }
std::string irc::User::getDeleteMessage()
{
	if (!deleteMessage.length())
		return "Client Quit";
	return deleteMessage;
}
std::string irc::User::getAwayMessage() { return awayMessage; }
