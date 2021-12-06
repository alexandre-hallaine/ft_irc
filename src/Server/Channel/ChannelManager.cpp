#include "ChannelManager.hpp"
#include <sstream>

void irc::ChannelManager::displayChannels()
{
	std::stringstream ss;
	ss << "Channels: " << channels.size();
	display.setLine(2, ss.str());
}

irc::ChannelManager::ChannelManager(Display &display)
	: channels(), display(display) { displayChannels(); }

bool irc::ChannelManager::contains(std::string name) { return channels.count(name); }
irc::Channel &irc::ChannelManager::get(std::string name)
{
	Channel &channel = channels[name];
	displayChannels();
	return channel;
}
void irc::ChannelManager::del(std::string name)
{
	channels.erase(channels.find(name));
	displayChannels();
}
