#include "../Command.hpp"
#include "../../../Server/Server.hpp"
#include "../../../Utils/Utils.hpp"

void TIME(irc::Command *command) { command->reply(391, command->getServer().getConfig().get("name"), irc::currentTime()); }
