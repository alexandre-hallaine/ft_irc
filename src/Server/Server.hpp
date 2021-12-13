#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config/Config.hpp"
#include "Display/Display.hpp"
#include "Channel/Channel.hpp"
#include <string>
#include <map>
#include <vector>
#include <poll.h>

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
		int fd;
		time_t last_ping;

		void pendingConnection();
		void sendPing();

		void updateUsers();
		void updateChannels();

	public:
		Server();
		~Server();

		void init();
		void execute();

		Config &getConfig();
		std::string getUpTime();

		std::vector<User *> getUsers();
		User *getUser(std::string const &nick);
		void delUser(User &user);

		bool isChannel(std::string const &name);
		Channel &getChannel(std::string name);
		std::vector<Channel *> getChannels();
		void delChannel(Channel channel);
	};
}
#endif
