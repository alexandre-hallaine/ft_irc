#include "../../Connection/Connection.hpp"
#include <sstream>

void irc::PART(std::string args, User *user) { user->leaveChannel(args); }
