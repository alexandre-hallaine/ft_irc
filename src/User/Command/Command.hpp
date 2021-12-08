#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

namespace irc
{
	class User;
	class Server;

	class Command
	{
	private:
		User *user;
		Server *server;

		std::string prefix;
		std::vector<std::string> args;
		std::string value;

		std::vector<std::string> split(std::string str, std::string delimiter);
		std::string getReplies(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7);

	public:
		Command(User *user, Server *server, std::string message);

		User &getUser();
		Server &getServer();

		std::string getPrefix();
		std::vector<std::string> getArgs();
		std::string getValue();

		void reply(unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "");
	};

	void CAP(Command *command);
}
#endif
