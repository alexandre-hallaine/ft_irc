#include "../PacketManager.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

void irc::NICK(struct irc::packetParams params)
{
	if (params.args[1].empty())
		return params.user->write(431);

	for (std::vector<User *>::iterator it = params.server->getUsers().begin(); it != params.server->getUsers().end(); ++it)
		if (params.args[1] == (*it)->getNickname())
			return params.user->write(433, (*it)->getNickname());

//need to check for allowed characters
	if (params.args[1].size() > 9)
		return params.user->write(432, params.args[1]);	

	bool init = false;
	if (params.user->getNickname() != "*")
	{
		std::stringstream ss;
		ss << ":" << params.user->getNickname() << " " << "NICK" << " " << params.args[1] << "\r\n";
		params.user->write(ss.str());
	}
	else
		init = true;
	params.user->setNickname(params.args[1]);
	if (init)
	{
		params.user->write(1, params.user->getNickname(), params.user->getUsername(), params.user->getHostname());
		params.user->write(2, params.server->getServername(), params.server->getVersion());
		params.user->write(3, params.server->getTime());
		params.user->write(4, params.server->getServername(), params.server->getVersion(), params.user->getUser_modes(), "");


		std::ifstream file("MOTD.txt");
		params.user->write(375, params.server->getServername());
		if (file.is_open())
		{
			std::string line;
			std::vector<std::string> motd;
			while (getline(file, line))
			{
				if (line.size() > 80)
				{
					params.user->write(422);
					return params.user->write(376);
				}	
				motd.push_back(line);
			}
			for (std::vector<std::string>::iterator it = motd.begin(); it != motd.end(); ++it)
				params.user->write(372, it->c_str());
			file.close();
		}
	}
}
