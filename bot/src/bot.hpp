#ifndef BOT_HPP
# define BOT_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <cerrno>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <iostream>
# include <unistd.h>
# include <poll.h>
# include <vector>

#define DEBUG true

class Bot
{
	private:
		std::string addr;
		int sock;
		struct sockaddr_in serv_addr;

		std::string pass;
		std::string nick;
		bool connected;

		std::string receive;
		std::vector<std::string> messages;

		void send_msg(std::string msg);
		void recv_msg();
		void send_pass();
		void send_nick();
	public:
		Bot(std::string addr, int port = 6667, std::string pass = std::string(), std::string nick = "bot");
		~Bot();
		
		void run();
};


#endif
