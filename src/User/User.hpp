#ifndef USER_HPP
#define USER_HPP

#include <netinet/in.h>
#include <string>
#include <vector>
#include <map>

namespace irc
{
	class Command;
	class Server;

	class User
	{
	private:
		int fd;
		std::string host;
		std::map<std::string, void (*)(Command *)> command_function;
		std::vector<Command *> commands;
		std::string packet;
		std::vector<std::string> pending;

		std::string nickname;
		std::string username;
		std::string realname;

		void push();
		void callCommands();

	public:
		User(int fd, struct sockaddr_in address);
		~User();

		void pendingMessages(Server *server);
		void write(std::string message);

		bool isRegistered();

		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		std::string getHost();
		std::string getPrefix();
		std::string getNickname();
		std::string getUsername();
		std::string getRealname();
		int getFd();
	};
}
#endif
