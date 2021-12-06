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
		std::string hote;
		std::string mode;
		std::string user_modes;

		std::string generate(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7);

	public:
		User(int fd, std::string hote);
		~User();

		std::string read();
		void write(std::string query);
		void write(unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "");

		void setUsername(std::string username);
		void setHostname(std::string hostname);
		void setServername(std::string servername);
		void setRealname(std::string realname);
		void setNickname(std::string nickname);
		void setMode(std::string mode);
		std::string getUsername();
		std::string getHostname();
		std::string getServername();
		std::string getRealname();
		std::string getNickname();
		std::string getHote();
		std::string getMode();
		std::string getUser_modes();

		bool operator==(const User &user) const;
	};
}
#endif
