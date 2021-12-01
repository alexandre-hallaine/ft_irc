#include "../../User/User.hpp"

void irc::PART(std::string args, User *user) { user->leaveChannel(args); }
