#include "../Command.hpp"
#include "../../User.hpp"
#include <ctime>

void PONG(irc::Command *command) { command->getUser().setLastPing(std::time(0)); }
