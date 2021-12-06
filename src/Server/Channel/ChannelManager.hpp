#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include "Channel.hpp"
#include "../Display/Display.hpp"
#include <string>
#include <map>

namespace irc
{
	class ChannelManager
	{
	private:
		std::map<std::string, Channel> channels;
		Display &display;

		void displayChannels();

	public:
		ChannelManager(Display &display);
		bool contains(std::string name);
		Channel &get(std::string name);
		void del(std::string name);
	};
}
#endif
