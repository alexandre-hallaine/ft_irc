#include "../CommandsBook.hpp"
#include "../../Connection/Connection.hpp"
#include <iostream>

void irc::NICK(std::string args, User &user) { user.setNick(args); }
