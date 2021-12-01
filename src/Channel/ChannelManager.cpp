#include "ChannelManager.hpp"

irc::ChannelManager::ChannelManager()
	: channels() {}

bool irc::ChannelManager::contains(std::string name) { return channels.count(name); }
irc::Channel &irc::ChannelManager::get(std::string name) { return channels[name]; }
void irc::ChannelManager::del(std::string name) { channels.erase(channels.find(name)); }
