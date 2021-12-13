#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <map>
#include <vector>

namespace irc
{
	class User;

	class Channel
	{
	private:
		std::string name;
		std::string topic;
		std::map<int, User *> users;
		std::string mode;
		std::map<int, std::string> user_mode;
		std::string key;
		std::string max_users;
		std::vector<User *> invited;

	public:
		Channel();

		void setName(std::string name);
		std::string getName();

		void setTopic(std::string topic);
		std::string getTopic();

		void addUser(User &user);
		void removeUser(User &user);
		void removeUser(std::string const &nick);
		std::vector<User *> getUsers();
		bool isUser(User &user);
		bool isOnChannel(std::string const &nick);

		void setMode(std::string);
		std::string getMode();

		void setUserMode(User &user, std::string mode);
		std::string getUserMode(User &user);

		void setKey(std::string key);
		std::string getKey();

		void setMaxUsers(std::string max);
		std::string getMaxUsers();

		void addInvited(User &user);
		bool isInvited(User &user);
		void removeInvited(User &user);

		void broadcast(User &user, std::string message);
	};

}
#endif
