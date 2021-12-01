#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../User/User.hpp"
#include <vector>
#include <string>

namespace irc
{
	class Channel
	{
	private:
		std::vector<User *> users;

	public:
		Channel();

		void addUser(User *user);
		void delUser(User *user);

		void broadcast(std::string str);
	};
}
#endif
