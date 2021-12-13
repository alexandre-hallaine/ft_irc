#ifndef USER_HPP
#define USER_HPP

#include <netinet/in.h>
#include <string>
#include <vector>
#include <map>

namespace irc
{
	class Command;
	class Server;

	class User
	{
	private:
		int fd;
		std::map<std::string, void (*)(Command *)> command_function;
		std::vector<Command *> commands;
		std::string packet;
		std::vector<std::string> pending;
		time_t last_ping;
		bool needDelete;

		std::string hostaddr;
		std::string hostname;
		bool password;
		std::string nickname;
		std::string username;
		std::string realname;
		std::string mode;
		std::string pastnick;

		std::string lastChannel;

		void callCommands();

	public:
		User(int fd, struct sockaddr_in address);
		~User();

		void pendingMessages(Server *server);
		void write(std::string message);
		void sendTo(User &toUser, std::string message);
		void push();

		bool isRegistered();
		void deleteLater();
		bool toDelete();

		void setLastPing(time_t last_ping);
		void setPassword();
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);
		void setMode(std::string mode);
		void setPastnick(std::string pastnick);
		void setLastChannel(std::string lastChannel);

		int getFd();
		time_t getLastPing();
		std::string getHostaddr();
		std::string getHostname();
		std::string getHost();
		std::string getPrefix();
		std::string getNickname();
		std::string getUsername();
		std::string getRealname();
		std::string getMode();
		std::string getPastnick();
		std::string getLastChannel();
	};
}
#endif
