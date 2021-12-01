#include "../CommandsBook.hpp"
#include "../../Connection/Connection.hpp"
#include <sstream>
#include <iostream>

void irc::CAP(std::string args, struct user *user)
{
	if (args == "LS")
	{
		write(user->fd, "CAP * LS :\r\n");
		write(user->fd, "NOTICE * :Connection...\r\n");
	}
	else if (args == "END")
	{
		std::string motd("Hello, World!");

		std::stringstream stream;
		stream << user->fd - 3 << " " << user->nick << " :" << motd << "\r\n";

		stream << "MODE " << user->nick << " :"
			   << "+i"
			   << "\r\n";

		write(user->fd, stream.str());
	}
}
