#include "Config.hpp"
#include <fstream>
#include <cstdlib>

void irc::Config::init(std::string config)
{
	std::ifstream ifs(config.c_str(), std::ifstream::in);
	if (!ifs.good())
		exit(EXIT_FAILURE);

	std::string delimiter = "=";
	size_t position;
	std::string line;
	while (!ifs.eof())
	{
		std::getline(ifs, line);
		if ((position = line.find('=')) == std::string::npos)
			continue;
		std::string key = line.substr(0, position);
		line.erase(0, position + delimiter.length());
		values[key] = line;
	}
	ifs.close();
}

irc::Config::Config()
	: values() { init("configs/default.config"); }
irc::Config::Config(std::string config)
	: values() { init(config); }

void irc::Config::set(std::string key, std::string value) { values[key] = value; }
std::string irc::Config::get(std::string key) { return values[key]; }
