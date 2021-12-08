#include "Command.hpp"
#include "../User.hpp"
#include <iostream>

void USER(irc::Command *command)
{
	command->getUser().setUsername(command->getParameters()[0]);
	command->getUser().setRealname(command->getTrailer());
}
