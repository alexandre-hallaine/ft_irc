#include "Runtime.hpp"

irc::Runtime::Runtime()
	: Server() {}

void irc::Runtime::run() { loop(); }

irc::Config &irc::Runtime::getConfig() { return config; }
