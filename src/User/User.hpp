#ifndef USER_HPP
#define USER_HPP

#include <netinet/in.h>
#include <string>

namespace irc
{
	class Server;
	class User
	{
	private:
		int fd;
		struct sockaddr_in address;
		std::string nick;
		Server *server;

	public:
		User();
		User(int fd, struct sockaddr_in address);
		User(const User &other);
		User &operator=(const User &other);

		void setServer(Server *server);
		void setNick(std::string nick);

		int getFd();
		struct sockaddr_in getAddress();
		std::string getNick();

		void joinChannel(std::string name);
		void leaveChannel(std::string name);
	};
}
#include "../Server/Server.hpp"
#endif
