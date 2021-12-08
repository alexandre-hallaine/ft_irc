#include "Command.hpp"
#include <sstream>

std::vector<std::string> irc::Command::split(std::string str, std::string delimiter)
{
	std::vector<std::string> values = std::vector<std::string>();

	size_t position;
	while ((position = str.find(delimiter)) != std::string::npos)
	{
		values.push_back(str.substr(0, position));
		str.erase(0, position + delimiter.length());
	}
	values.push_back(str);

	return values;
}

irc::Command::Command(User *user, Server *server, std::string message)
	: user(user), server(server)
{
	std::string delimiter(":");
	size_t position;
	if ((position = message.find(delimiter)) != std::string::npos)
	{
		std::string tmp = message.substr(0, position);
		message.erase(0, position + delimiter.length());
		trailer = message;
		message = tmp;
	}

	parameters = split(message, " ");
	prefix = *(parameters.begin());
	parameters.erase(parameters.begin());
}

irc::User &irc::Command::getUser() { return *user; }
irc::Server &irc::Command::getServer() { return *server; }

std::string irc::Command::getPrefix() { return prefix; }
std::vector<std::string> irc::Command::getParameters() { return parameters; }
std::string irc::Command::getTrailer() { return trailer; }

void reply(unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "")
{
	std::stringstream sscode;
	sscode << code;
	std::string scode = sscode.str();
	while (scode.length() < 3)
		scode = "0" + scode;

	(void)arg1;
	(void)arg2;
	(void)arg3;
	(void)arg4;
	(void)arg5;
	(void)arg6;
	(void)arg7;
	//user->write(":" + servername + " " + scode + " " + nickname + " " + getReplies(code, arg1, arg2, arg3, arg4, arg5, arg6, arg7) + "\r\n");
}
