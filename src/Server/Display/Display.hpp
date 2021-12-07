#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <map>
#include <string>

#define WARNING "\033[0;33m"
#define ERROR "\033[0;31m"

namespace irc
{
	class Display
	{
	private:
		std::map<unsigned char, std::string> lines;

		void clearScreen();
		void update();

	public:
		Display();

		void setLine(unsigned char pos, std::string line);
	};
}
#endif
