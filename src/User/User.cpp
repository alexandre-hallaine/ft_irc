#include "User.hpp"
#include "Command/Command.hpp"
#include "../utils/utils.hpp"
#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <sys/socket.h>

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
	std::vector<Command *>::iterator it = commands.begin();
	std::vector<Command *>::iterator ite = commands.end();
	while (it != ite)
	{
		Command *command = *it;
		command_function[command->getPrefix()](command);
		++it;
	}
	push();
}

void irc::CAP(irc::Command *command);

irc::User::User(int fd, struct sockaddr_in address)
	: fd(fd), status(registration), command_function(), commands(), packet(), pending()
{
	fcntl(fd, F_SETFL, O_NONBLOCK);
	(void)address;
	(void)status;

	command_function["CAP"] = CAP;
}

void irc::User::pendingMessages(Server *server)
{
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events = POLLIN;
	if (poll(&pfd, 1, 50) == -1)
		return;

	char buffer[BUFFER_SIZE + 1];
	ssize_t msg_len = recv(pfd.fd, &buffer, BUFFER_SIZE, 0);
	if (msg_len == -1)
		return;
	buffer[msg_len] = 0;

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
