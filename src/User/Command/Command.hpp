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
		std::vector<std::string> parameters;
		std::string trailer;
		std::string query;

		bool stop;

		std::string getReplies(unsigned short code, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7);

	public:
		Command(User *user, Server *server, std::string message);

		User &getUser();
		Server &getServer();

		std::string getPrefix();
		std::vector<std::string> getParameters();
		std::string getTrailer();
		std::string getQuery();

		void setStop(bool stop);
		bool getStop();

		void reply(User &user, unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "");
		void reply(unsigned short code, std::string arg1 = "", std::string arg2 = "", std::string arg3 = "", std::string arg4 = "", std::string arg5 = "", std::string arg6 = "", std::string arg7 = "");
	};
}
#endif
