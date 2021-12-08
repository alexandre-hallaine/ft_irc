#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config/Config.hpp"
#include "Display/Display.hpp"
#include <string>
#include <map>

namespace irc
{
	class User;

	class Server
	{
	private:
		Config config;
		Display display;
		std::map<int, User *> users;
		std::string upTime;
		bool stop;
		int fd;

		void init();
		void displayUsers();
		void checkConnection();

	public:
		Server();

		void loop();

		Config &getConfig();
	};
}
#endif
