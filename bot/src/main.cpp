#include "bot.hpp"

int main(int argc, char **argv)
{
	try {
		if (argc == 2)
		{
			Bot bot(argv[1]);
			bot.run();
		}
		else if (argc == 3)
		{
			Bot bot(argv[1], atoi(argv[2]));
			bot.run();
		}
		else if (argc == 4)
		{
			Bot bot(argv[1], atoi(argv[2]), argv[3]);
			bot.run();
		}
		else
		{
			std::cout << "Usage: " << argv[0] << " <server> [port] [nickname]" << std::endl;
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
		// int sock = socket(AF_INET, SOCK_STREAM, 0);
		// if (sock < 0)
		// {
		// 	perror("socket");
		// 	return 1;
		// }
		// struct sockaddr_in serv_addr;
		// serv_addr.sin_family = AF_INET;
		// serv_addr.sin_port = htons(atoi(argv[2]));
		// serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

		// while (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		// {
		// 	perror("connect");
		// 	std::cout << "Retrying in 5 seconds..." << std::endl;
		// 	sleep(5);
		// }
		// std::string msg;

		// msg = "NICK nsimon\r\n";
		// send(sock , msg.c_str(), msg.size() , 0 );
		// while (true)
		// {
		// 	char buf[1024];
		// 	int n = recv(sock, buf, sizeof(buf), 0);
		// 	if (n < 0)
		// 	{
		// 		perror("recv");
		// 		return 1;
		// 	}
		// 	if (n == 0)
		// 		break;
		// 	buf[n] = 0;
		// 	printf("%s", buf);
		// }
}
