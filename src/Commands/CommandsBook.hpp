#ifndef COMMANDSBOOK_HPP
#define COMMANDSBOOK_HPP

#include "../User/User.hpp"
#include <map>
#include <string>

#define DEBUG 0

namespace irc
{
	void CAP(std::string, User *user);
	void NICK(std::string, User *user);
	void USER(std::string, User *user);
	void JOIN(std::string, User *user);
	void PART(std::string, User *user);
	void PRIVMSG(std::string, User *user);

	class CommandsBook
	{
	private:
		typedef void (*cmd)(std::string, User *user);
		std::map<std::string, cmd> map;

	public:
		CommandsBook();
		void call(std::string name, std::string args, User *user);
	};
}
#endif
