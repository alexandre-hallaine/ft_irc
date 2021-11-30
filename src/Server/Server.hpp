#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Connection/Connection.hpp"

#define BUF_SIZE 4096

namespace irc
{
	class Server
	{
	private:
		settings settings;
		Connection connection;

	public:
		Server(unsigned short port, std::string password);
		void run();
	};
}
#endif
