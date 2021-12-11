#include "Config.hpp"
#include "../../Utils/Utils.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>

void irc::Config::init(std::string config)
{
	std::ifstream ifs(config.c_str(), std::ifstream::in);
	if (!ifs.good())
		error("ifstream", true);

	std::string delimiter = "=";
	size_t position;
	std::string line;
	while (!ifs.eof())
	{
		line = "";
		std::getline(ifs, line);
		if ((position = line.find('=')) == std::string::npos)
			continue;
		std::string key = line.substr(0, position);
		line.erase(0, position + delimiter.length());

		if (line.find("./") == 0)
		{
			std::ifstream file(line.c_str(), std::ifstream::in);
			std::stringstream buffer;
			buffer << file.rdbuf();
			line = buffer.str();
		}

		values[key] = line;
	}
	ifs.close();
}

irc::Config::Config() { init("configs/default.config"); }
irc::Config::Config(std::string config) { init(config); }

void irc::Config::set(std::string key, std::string value) { values[key] = value; }
std::string irc::Config::get(std::string key) { return values[key]; }
