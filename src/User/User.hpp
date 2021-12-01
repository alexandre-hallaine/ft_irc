#ifndef USER_HPP
#define USER_HPP

#include <string>

#define BUFFER_SIZE 4096

namespace irc
{
	class User
	{
	private:
		int fd;
		std::string nickname;

	public:
		User(int fd);

		std::string read();
		void write(std::string str);

		void setNickname(std::string nick);
		std::string getNickname();
	};
}
#endif
