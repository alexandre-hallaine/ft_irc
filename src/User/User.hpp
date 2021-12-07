#ifndef USER_HPP
#define USER_HPP

namespace irc
{
	class User
	{
	private:
		int fd;

	public:
		User(int fd);
	};
};
#endif
