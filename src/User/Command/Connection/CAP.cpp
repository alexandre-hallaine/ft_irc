#include "../Command.hpp"
#include "../../User.hpp"
#include "../../../Server/Server.hpp"

void CAP(irc::Command *command)
{
    if (command->getParameters()[0] != "LS" && command->getParameters()[0] != "END")
    {
        return command->getUser().sendTo(command->getUser(), "CAP * NAK :");
    }
    else if (command->getParameters()[0] == "LS")
    {
        command->getUser().sendTo(command->getUser(), "CAP * LS :");
    }
    else if (command->getParameters()[0] == "END")
    {
        command->getUser().sendTo(command->getUser(), "CAP * END :");
        command->getUser().setStatus(irc::PASSWORD);
    }
}
