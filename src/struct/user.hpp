#ifndef USER_HPP
#define USER_HPP

#include <netinet/in.h>
#include <string>

struct user
{
	int fd;
	struct sockaddr_in address;
	std::string nick;
};
#endif
