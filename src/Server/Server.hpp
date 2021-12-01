#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Connection/Connection.hpp"
#include "../Commands/CommandsBook.hpp"
#include <vector>

namespace irc
{
	class Server
	{
	private:
		settings settings;
		Connection connection;
		CommandsBook commands;
		std::vector<User> users;

	public:
		Server(unsigned short port, std::string password);
		void run();
	};
}
#endif
