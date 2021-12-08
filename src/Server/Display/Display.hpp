#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <map>
#include <string>

namespace irc
{
	class Display
	{
	private:
		std::map<unsigned char, std::string> lines;

		void clearScreen();
		void update();
		void write(unsigned char pos, std::string prefix, std::string line);

	public:
		Display();

		void write(unsigned char pos, std::string line);
		void warning(unsigned char pos, std::string line);
		void error(unsigned char pos, std::string line);
	};
}
#endif
