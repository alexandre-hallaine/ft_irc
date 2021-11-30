#include "../CommandsBook.hpp"
#include "../../Connection/Connection.hpp"
#include <sstream>

void irc::USER(std::string args, struct user *user)
{
	std::string motd("Hello, World!");

	(void)args;
	std::stringstream stream;
	stream << user->fd - 3 << " " << user->nick << " :" << motd << "\r\n";
	write(user->fd, stream.str());
}
