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
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;
		std::string nickname;
		std::string modes;

	public:
		User(int fd);

		std::string read();
		void write(std::string str);

		void setUsername(std::string username);
		void setHostname(std::string hostname);
		void setServername(std::string servername);
		void setRealname(std::string realname);
		void setNickname(std::string nickname);
		void setModes(std::string modes);
		std::string getUsername();
		std::string getHostname();
		std::string getServername();
		std::string getRealname();
		std::string getNickname();
		std::string getModes();

		bool operator==(const User &b) const;
	};
}
#endif
