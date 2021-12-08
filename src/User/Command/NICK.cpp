#include "Command.hpp"
#include "../User.hpp"

void NICK(irc::Command *command)
{
	if (!command->getParameters().size())
		return command->reply(431);

	/*for (std::vector<User *>::iterator it = params.server->getUsers().begin(); it != params.server->getUsers().end(); ++it)
		if (params.args[1] == (*it)->getNickname())
			return params.user->write(433, (*it)->getNickname());

	//need to check for allowed characters
	if (params.args[1].size() > 9)
		return params.user->write(432, params.args[1]);

	bool init = false;
	if (params.user->getNickname() != "*")
	{
		std::stringstream ss;
		ss << ":" << params.user->getNickname() << " "
		   << "NICK"
		   << " " << params.args[1] << "\r\n";
		params.user->write(ss.str());
	}
	else
		init = true;

	if (params.user->getNickname() != "*")
		params.user->setPastnick(" " + params.user->getNickname() + " " + params.user->getPastnick());*/
	command->getUser().setNickname(command->getParameters()[0]);
}
