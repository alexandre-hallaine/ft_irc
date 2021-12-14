#ifndef USER_HPP
#define USER_HPP

#include <netinet/in.h>
#include <string>
#include <vector>
#include <map>

namespace irc
{
	enum UserStatus
	{
		PASSWORD,
		REGISTER,
		ONLINE,
		DELETE
	};

	class Command;
	class Server;

	class User
	{
		friend class Server;

	private:
		std::map<std::string, void (*)(Command *)> command_function;

		int fd;
		std::string buffer;
		std::vector<Command *> commands;
		std::vector<std::string> waitingToSend;

		UserStatus status;
		time_t last_ping;
		std::string hostaddr;
		std::string hostname;
		std::string nickname;
		std::string username;
		std::string realname;

		std::string mode;
		std::string pastnick;
		std::string lastChannel;
		std::string deleteMessage;
		std::string awayMessage;

		void dispatch();
		void receive(Server *server);
		void write(std::string message);
		void push();

	public:
		User(int fd, struct sockaddr_in address);
		~User();

		void sendTo(User &toUser, std::string message);

		void setStatus(UserStatus status);
		void setLastPing(time_t last_ping);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setRealname(std::string realname);

		int getFd();
		UserStatus getStatus();
		time_t getLastPing();
		std::string getPrefix();
		std::string getHostaddr();
		std::string getHostname();
		std::string getHost();
		std::string getNickname();
		std::string getUsername();
		std::string getRealname();

		void setMode(std::string mode);
		void setPastnick(std::string pastnick);
		void setLastChannel(std::string lastChannel);
		void setDeleteMessage(std::string message);
		void setAwayMessage(std::string message);

		std::string getMode();
		std::string getPastnick();
		std::string getLastChannel();
		std::string getDeleteMessage();
		std::string getAwayMessage();
	};
}
#endif
