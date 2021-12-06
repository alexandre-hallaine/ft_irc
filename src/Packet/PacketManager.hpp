#ifndef PACKETMANAGER_HPP
#define PACKETMANAGER_HPP

#include "../User/User.hpp"
#include "../Server/Channel/ChannelManager.hpp"
#include <vector>
#include <string>

#define DEBUG false

namespace irc
{
	class Server;

	struct packetParams
	{
		std::vector<std::string> args;
		std::string value;
		User *user;
		ChannelManager *channels;
		Server *server;
	};

	void CAP(struct packetParams params);
	void NICK(struct packetParams params);
	void QUIT(struct packetParams params);
	void USER(struct packetParams params);
	void PING(struct packetParams params);
	void JOIN(struct packetParams params);
	void MODE(struct packetParams params);
	void WHOIS(struct packetParams params);

	class PacketManager
	{
	private:
		ChannelManager &channels;
		Server &server;
		std::map<std::string, void (*)(struct packetParams)> functions;

		std::vector<std::string> split(std::string str, std::string delimiter);
		void call(std::string line, User *user);

	public:
		PacketManager(ChannelManager &channels, Server &server);

		void request(std::string query, User *user);
	};
}
#include "../Server/Server.hpp"
#endif
