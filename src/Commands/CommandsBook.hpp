#ifndef COMMANDSBOOK_HPP
#define COMMANDSBOOK_HPP

#include <map>
#include <string>
namespace irc
{
	void CAP(std::string);

	class CommandsBook
	{
	private:
		typedef void (*cmd)(std::string);
		std::map<std::string, cmd> map;

	public:
		CommandsBook();
		void call(std::string name, std::string args);
	};
}
#endif
