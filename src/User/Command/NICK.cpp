#include "Command.hpp"
#include "../User.hpp"

void NICK(irc::Command *command) { command->getUser().setNickname(command->getParameters()[0]); }
