#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../struct/settings.hpp"

namespace irc
{
	class Connection
	{
	private:
		int tcp_socket;

	public:
		Connection(unsigned short port);
		void next();
	};
}
#endif
