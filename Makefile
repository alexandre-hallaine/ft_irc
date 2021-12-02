NAME				=	ircserv

DIRECTORY_CHECK		=	src
DIRECTORY_SOURCE	=	src
DIRECTORY_OBJECT	=	objects

FILES_CHECK			=	Packet/PacketManager.hpp \
						User/User.hpp \
						Channel/Channel.hpp \
						Channel/ChannelManager.hpp \
						Display/Display.hpp \
						Server/Server.hpp
FILES_SOURCE		=	Packet/Commands/CAP.cpp \
						Packet/Commands/NICK.cpp \
						Packet/Commands/QUIT.cpp \
						Packet/PacketManager.cpp \
						User/User.cpp \
						Channel/Channel.cpp \
						Channel/ChannelManager.cpp \
						Display/Display.cpp \
						Server/Server.cpp \
						main.cpp

COMPILE				=	clang++
COMPILATION_FLAG	=	-Wall -Wextra -Werror -std=c++98 -pedantic-errors

ARGUMENTS			=	6667 azerty

all: $(NAME)

$(DIRECTORY_OBJECT)/%.o: $(DIRECTORY_SOURCE)/%.cpp $(FILES_CHECK:%=$(DIRECTORY_CHECK)/%)
	@printf "\e[33m"
	@printf "Compile\t$< -> $@\n"
	mkdir -p $(dir $@)
	$(COMPILE) $(COMPILATION_FLAG) -c $< -o $@

$(NAME): $(FILES_SOURCE:%.cpp=$(DIRECTORY_OBJECT)/%.o)
	@printf "\e[32m"
	@printf "Build\t$@\n"
	$(COMPILE) -o $@ $(FILES_SOURCE:%.cpp=$(DIRECTORY_OBJECT)/%.o)

run: all
	@printf "\e[0m"
	./$(NAME) $(ARGUMENTS)

clean:
	@printf "\e[31m"
	@printf "Remove\t$(DIRECTORY_OBJECT)\n"
	rm -rf $(DIRECTORY_OBJECT)

fclean: clean
	@printf "Remove\t$(NAME)\n"
	rm -f $(NAME)

re: fclean all

rrun: re run

leaks: all
	@printf "\e[0m"
	valgrind make run

.PHONY: all run clean fclean re rrun leaks
.SILENT:
