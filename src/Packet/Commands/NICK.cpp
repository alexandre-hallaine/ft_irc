#include "../PacketManager.hpp"
#include <sstream>

void irc::NICK(struct irc::packetParams params) { params.user->setNickname(params.args[1]); }
