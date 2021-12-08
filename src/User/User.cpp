#include "User.hpp"
#include "Command/Command.hpp"
#include "../utils/utils.hpp"
#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <sys/socket.h>
#include <algorithm>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 4096
#define MESSAGE_END "\r\n"

void irc::User::push()
{
	std::string buffer;
	std::vector<std::string>::iterator it = pending.begin();
	std::vector<std::string>::iterator ite = pending.end();
	while (it != ite)
	{
		if (DEBUG)
			std::cout << fd << " > " << *it << std::endl;
		buffer += *it + MESSAGE_END;
		++it;
	}
	pending.clear();

	send(fd, buffer.c_str(), buffer.length(), 0);
}
void irc::User::callCommands()
{
	std::vector<Command *> remove = std::vector<Command *>();

	std::vector<Command *>::iterator it = commands.begin();
	std::vector<Command *>::iterator ite = commands.end();
	while (it != ite)
	{
		Command *command = *it;
		if (command_function.count(command->getPrefix()))
			command_function[command->getPrefix()](command);
		else if (DEBUG)
			std::cout << "Unknown command: " << command->getPrefix() << std::endl;
		++it;
	}
	push();

	it = remove.begin();
	ite = remove.end();
	while (it != ite)
	{
		std::vector<Command *>::iterator item = std::find(commands.begin(), commands.end(), *it);
		if (item != commands.end())
			commands.erase(item);
		++it;
	}
}

void CAP(irc::Command *command);
void NICK(irc::Command *command);

irc::User::User(int fd, struct sockaddr_in address)
	: fd(fd), status(online)
{
	fcntl(fd, F_SETFL, O_NONBLOCK);

	struct addrinfo hints, *result;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	if (getaddrinfo(inet_ntoa(address.sin_addr), "", &hints, &result) != 0)
		error("getaddrinfo");

	std::cout << "ai_canonname: " << result->ai_canonname << std::endl;
	(void)status;

	command_function["CAP"] = CAP;
	command_function["NICK"] = NICK;
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

std::string getPrefix()
{
	return "";
}
