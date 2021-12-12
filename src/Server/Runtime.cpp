#include "Runtime.hpp"

irc::Runtime::Runtime()
	: isInit(false) {}

void irc::Runtime::run()
{
	if (!isInit)
	{
		init();
		isInit = true;
	}
	execute();
}
