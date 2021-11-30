#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Connection/Connection.hpp"
#include "../Commands/CommandsBook.hpp"

namespace irc
{
	class Server
	{
	private:
		settings settings;
		Connection connection;
		CommandsBook commands;

	public:
		Server(unsigned short port, std::string password);
		void run();
	};
}
#endif
