#include "../../User/User.hpp"

void irc::JOIN(std::string args, User *user) { user->joinChannel(args); }
