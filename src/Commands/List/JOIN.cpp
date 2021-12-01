#include "../../Connection/Connection.hpp"
#include <sstream>

void irc::JOIN(std::string args, User *user) { user->joinChannel(args); }
