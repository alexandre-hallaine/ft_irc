#include "../CommandsBook.hpp"
#include "../../Connection/Connection.hpp"
#include <sstream>
#include <iostream>

void irc::CAP(std::string args, User &user)
{
	if (args == "LS")
		write(user.getFd(), "CAP * LS :\r\n");
	else if (args == "END")
	{
		std::string motd("Work :D");

		std::stringstream stream;
		stream << "001 " << user.getNick() << " :" << motd << "\r\n";
		write(user.getFd(), stream.str());
	}
}
