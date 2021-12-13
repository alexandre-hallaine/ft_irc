#include "../Command.hpp"
#include "../../../Server/Server.hpp"

void VERSION(irc::Command *command) { command->reply(351, command->getServer().getConfig().get("version"), command->getServer().getConfig().get("name"), "boo"); }
