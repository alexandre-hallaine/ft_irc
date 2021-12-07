#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config/Config.hpp"
#include "Display/Display.hpp"

namespace irc
{
	class Server
	{
	protected:
		Config config;

	private:
		Display display;
		int fd;
		std::string upTime;

		void init();

	public:
		Server();

		void loop();
	};
}
#endif
