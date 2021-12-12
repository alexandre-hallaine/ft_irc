#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include "Server.hpp"

namespace irc
{
	class Runtime
		: private Server
	{
	private:
		bool isInit;

	public:
		Runtime();

		void run();

		using Server::getConfig;
	};
}
#endif
