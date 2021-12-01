#include "../CommandsBook.hpp"
#include "../../Connection/Connection.hpp"
#include <sstream>
#include <iostream>

void irc::CAP(std::string args, struct user *user)
{
	if (args == "LS")
		write(user->fd, "CAP * LS :\r\n");
	else if (args == "END")
	{
		std::string motd("Work :D");

		std::stringstream stream;
		stream << "001 " << user->nick << " :" << motd << "\r\n";
		write(user->fd, stream.str());
	}
}
