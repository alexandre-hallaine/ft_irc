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

	public:
		Display();

		void set(unsigned char pos, std::string line);
		void remove(unsigned char pos);
	};
}
#endif
