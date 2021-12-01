#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../struct/settings.hpp"
#include "../User/User.hpp"

#define BUF_SIZE 4096

namespace irc
{
	class Connection
	{
	private:
		int tcp_socket;

	public:
		Connection(unsigned short port);
		User *waiting();
		User *force_waiting();
	};

	std::string read(int fd);
	void write(int fd, std::string);
	std::string next(std::string &str, std::string delimiter);
	std::string line(std::string &str);
}
#endif
