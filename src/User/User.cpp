#include "User.hpp"
#include "Command/Command.hpp"
#include "../utils/utils.hpp"
#include "../Server/Server.hpp"
#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <sys/socket.h>
#include <algorithm>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 4096
#define MESSAGE_END "\r\n"

void NICK(irc::Command *command);
void USER(irc::Command *command);
void MOTD(irc::Command *command);

void irc::User::push()
{
	std::string buffer;
	for (std::vector<std::string>::iterator it = pending.begin(); it != pending.end(); ++it)
	{
		if (DEBUG)
			std::cout << fd << " > " << *it << std::endl;
		buffer += *it + MESSAGE_END;
	}
	pending.clear();

	send(fd, buffer.c_str(), buffer.length(), 0);
}
void post_registration(irc::Command *command)
{
	command->reply(1, command->getUser().getPrefix());
	command->reply(2, command->getUser().getHost(), command->getServer().getConfig().get("version"));
	command->reply(3, command->getServer().getUpTime());
	command->reply(4, command->getServer().getConfig().get("name"), command->getServer().getConfig().get("version"),
				   command->getServer().getConfig().get("user_mode"), command->getServer().getConfig().get("channel_mode"));

	//not needed
	//lusers
	MOTD(command);
}
void irc::User::callCommands()
{
	bool registered = isRegistered();

	std::vector<Command *> remove = std::vector<Command *>();
	for (std::vector<Command *>::iterator it = commands.begin(); it != commands.end(); ++it)
	{
		Command *command = *it;
		if (registered || command->getPrefix() == "NICK" || command->getPrefix() == "USER")
		{
			if (command_function.count(command->getPrefix()))
				command_function[command->getPrefix()](command);
			else if (DEBUG)
				std::cout << "Unknown command: " << command->getPrefix() << std::endl;
			remove.push_back(command);
		}
	}
	push();

	for (std::vector<Command *>::iterator it = remove.begin(); it != remove.end(); ++it)
	{
		std::vector<Command *>::iterator item = std::find(commands.begin(), commands.end(), *it);
		if (item != commands.end())
			commands.erase(item);
	}

	if (!registered && isRegistered())
	{
		post_registration(*commands.begin());
		callCommands();
	}
}

irc::User::User(int fd, struct sockaddr_in address)
	: fd(fd)
{
	fcntl(fd, F_SETFL, O_NONBLOCK);

	char host[NI_MAXHOST];
	if (getnameinfo((struct sockaddr *)&address, sizeof(address), host, NI_MAXHOST, NULL, 0, NI_NUMERICSERV) != 0)
		error("getnameinfo");
	this->host = host;

	command_function["NICK"] = NICK;
	command_function["USER"] = USER;
	command_function["MOTD"] = MOTD;
}

void irc::User::pendingMessages(Server *server)
{
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;
	if (poll(&pfd, 1, 50) == -1)
		return;

	char buffer[BUFFER_SIZE + 1];
	ssize_t size;
	if ((size = recv(pfd.fd, &buffer, BUFFER_SIZE, 0)) == -1)
		return;
	buffer[size] = 0;

	std::string receive(buffer);
	packet += receive;
	std::string delimiter(MESSAGE_END);

	size_t position;
	while ((position = packet.find(delimiter)) != std::string::npos)
	{
		std::string message = packet.substr(0, position);
		packet.erase(0, position + delimiter.length());
		if (!message.length())
			continue;

		if (DEBUG)
			std::cout << fd << " < " << message << std::endl;
		commands.push_back(new Command(this, server, message));
	}
	callCommands();
}
void irc::User::write(std::string message) { pending.push_back(message); }

bool irc::User::isRegistered() { return nickname.length() && realname.length(); }

void irc::User::setNickname(std::string nickname) { this->nickname = nickname; }
void irc::User::setUsername(std::string username) { this->username = username; }
void irc::User::setRealname(std::string realname) { this->realname = realname; }
std::string irc::User::getHost() { return host; }
std::string irc::User::getPrefix()
{
	if (!nickname.length())
		return std::string();
	std::string prefix = nickname;
	if (host.length())
	{
		if (username.length())
			prefix += "!" + username;
		prefix += "@" + host;
	}
	return prefix;
}
std::string irc::User::getNickname() { return nickname; }
std::string irc::User::getUsername() { return username; }
std::string irc::User::getRealname() { return realname; }
