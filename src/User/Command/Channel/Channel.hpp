#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <map>
#include <vector>
#include <string>

namespace irc
{
	class User;

	class Channel
	{
		public:
			Channel(std::string const &name);
			~Channel();

			void addUser(User *user);
			void removeUser(User *user);

		private:
			std::string name;
			std::map<std::string, User*> users;
			std::map<std::string, std::string> modes;
	};

}

#endif
