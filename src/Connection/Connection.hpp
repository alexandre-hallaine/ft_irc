#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../struct/settings.hpp"
#include "../struct/user.hpp"

#define BUF_SIZE 4096

namespace irc
{
	class Connection
	{
	private:
		int tcp_socket;

	public:
		Connection(unsigned short port);
		struct user next();
		std::string read(int fd);
	};
}
#endif
