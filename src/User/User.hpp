#ifndef USER_HPP
#define USER_HPP

#include <netinet/in.h>
#include <string>

namespace irc
{
	class User
	{
	private:
		int fd;
		struct sockaddr_in address;
		std::string nick;

	public:
		User();
		User(int fd, struct sockaddr_in address);
		User(const User &other);
		User &operator=(const User &other);

		void setNick(std::string nick);

		int getFd();
		struct sockaddr_in getAddress();
		std::string getNick();
	};
}
#endif
