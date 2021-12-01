#ifndef COMMANDSBOOK_HPP
#define COMMANDSBOOK_HPP

#include "../struct/user.hpp"
#include <map>
#include <string>

#define DEBUG 0

namespace irc
{
	void CAP(std::string, struct user *user);
	void NICK(std::string, struct user *user);
	void USER(std::string, struct user *user);

	class CommandsBook
	{
	private:
		typedef void (*cmd)(std::string, struct user *user);
		std::map<std::string, cmd> map;

	public:
		CommandsBook();
		void call(std::string name, std::string args, struct user *user);
	};
}
#endif
