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
		std::map<int, std::string> modes;
		/*std::vector<std::string> bans;
		bool inviteOnly;
		std::string key;
		size_t max;*/

	public:
		Channel();

		void setName(std::string name);
		std::string getName();

		void setTopic(std::string topic);
		std::string getTopic();

		void addUser(User &user);
		void removeUser(User &user);
		std::vector<User *> getUsers();

		void setMode(User &user, std::string mode);
		std::string getMode(User &user);
	};

}
#endif
