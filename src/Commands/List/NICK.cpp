#include "../../User/User.hpp"

void irc::NICK(std::string args, User *user) { user->setNick(args); }
