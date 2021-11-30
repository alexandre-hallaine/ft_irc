#include "Server.hpp"

irc::Server::Server(unsigned short port, std::string password)
	: settings(), connection(port)
{
	settings.port = port;
	settings.password = password;
}

void irc::Server::run()
{
	connection.next();
}
