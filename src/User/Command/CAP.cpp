#include "../PacketManager.hpp"
#include <fstream>

void irc::CAP(struct irc::packetParams params)
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
