#ifndef USER_HPP
#define USER_HPP

#include <netinet/in.h>

struct user
{
	int fd;
	struct sockaddr_in address;
};
#endif
