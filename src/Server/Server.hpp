#ifndef SERVER_HPP
#define SERVER_HPP

#include "../User/User.hpp"
#include "../Channel/ChannelManager.hpp"
#include "../Packet/PacketManager.hpp"
#include "../Display/Display.hpp"
#include <string>
#include <vector>

namespace irc
{
	class Server
	{
	private:
		int tcp_socket;
		std::vector<User *> users;
		Display display;
		ChannelManager channels;
		PacketManager packet;

	private:
		void pending();
		void displayUsers();
		void registerUsers();

	public:
		Server(unsigned short port, std::string password);
		~Server();

		void run();
		void kill(User *user);
	};
}
#endif
