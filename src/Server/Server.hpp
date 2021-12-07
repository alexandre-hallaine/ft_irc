#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config/Config.hpp"
#include "Display/Display.hpp"

namespace irc
{
	class Server
	{
	private:
		Config config;
		Display display;
		int fd;
		std::string upTime;

		void init();

	public:
		Server();

		void loop();

		Config &getConfig();
	};
}
#endif
