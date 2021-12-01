#ifndef SERVER_HPP
#define SERVER_HPP

#include "../struct/settings.hpp"
#include <list>
#include <map>

namespace irc
{
	class Connection;
	class CommandsBook;
	class User;
	class Server
	{
	private:
		settings settings;
		Connection *connection;
		CommandsBook *commands;
		std::list<User *> users;
		std::map<std::string, std::list<User *> > channels;

	public:
		Server(unsigned short port, std::string password);
		~Server();
		void run();

		void addUser(User *user);
		void rmUser(User *user);
		void addChannel(std::string name, User *user);
		void rmChannel(std::string name, User *user);
		std::list<User *> getChannel(std::string name);
	};
}
#include "../Connection/Connection.hpp"
#include "../Commands/CommandsBook.hpp"
#endif
