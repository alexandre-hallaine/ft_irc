#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config/Config.hpp"
#include "Display/Display.hpp"
#include "Channel/Channel.hpp"
#include <string>
#include <map>
#include <vector>

namespace irc
{
	class User;

	class Server
	{
	private:
		Config config;
		Display display;
		std::map<int, User *> users;
		std::map<std::string, Channel> channels;
		std::string upTime;
		bool stop;
		int fd;

		void init();
		void pendingConnection();

	public:
		Server();

		void loop();

		Config &getConfig();
		std::string getUpTime();

		std::vector<User *> getUsers();
		void delUser(User &user);

		bool isChannel(std::string name);
		Channel &getChannel(std::string name);
		void delChannel(Channel channel);
	};
}
#endif
