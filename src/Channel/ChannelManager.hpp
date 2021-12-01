#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include "Channel.hpp"
#include <string>
#include <map>

namespace irc
{
	class ChannelManager
	{
	private:
		std::map<std::string, Channel> channels;

	public:
		ChannelManager();
		bool contains(std::string name);
		Channel &get(std::string name);
		void del(std::string name);
	};
}
#endif
