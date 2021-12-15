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
		int fd;
		std::string upTime;
		time_t last_ping;
		std::vector<pollfd> pfds;

		void acceptUser();
		void sendPing();

		void displayUsers();
		void displayChannels();

	public:
		Server();
		~Server();

		void init();
		void execute();

		Config &getConfig();
		std::string getUpTime();

		User *getUser(std::string const &nick);
		void delUser(User &user);
		std::vector<User *> getUsers();

		bool isChannel(std::string const &name);
		Channel &getChannel(std::string name);
		void delChannel(Channel channel);
		std::vector<Channel *> getChannels();
	};
}
#endif
