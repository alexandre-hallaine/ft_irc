#include "../../Connection/Connection.hpp"

void irc::PING(std::string args, User *user)
{
	std::stringstream stream;
	stream << "PONG " << args << "\r\n";
	write(user->getFd(), stream.str());
}
