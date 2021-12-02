#include "../PacketManager.hpp"
#include <sstream>

void irc::QUIT(struct irc::packetParams params) { params.server->kill(params.user); }
