#include "../PacketManager.hpp"

void irc::QUIT(struct irc::packetParams params) { params.server->kill(params.user); }
