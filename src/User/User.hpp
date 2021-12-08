#ifndef USER_HPP
#define USER_HPP

#include <netinet/in.h>
#include <string>
#include <vector>
#include <map>

namespace irc
{
	enum Status
	{
		online,
		away
	};

	class Command;
	class Server;

	class User
	{
	private:
		int fd;
		Status status;
		std::map<std::string, void (*)(Command *)> command_function;
		std::vector<Command *> commands;
		std::string packet;
		std::vector<std::string> pending;

		void push();
		void callCommands();

	public:
		User(int fd, struct sockaddr_in address);

		void pendingMessages(Server *server);
		void write(std::string message);

		std::string getPrefix();
	};
}
#endif
