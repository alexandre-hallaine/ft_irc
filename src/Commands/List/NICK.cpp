#include "../CommandsBook.hpp"
#include "../../Connection/Connection.hpp"
#include <iostream>

void irc::NICK(std::string args, struct user *user) { user->nick = args; }
