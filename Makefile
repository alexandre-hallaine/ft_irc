NAME				=	ircserv

DIRECTORY_CHECK		=	src
DIRECTORY_SOURCE	=	src
DIRECTORY_OBJECT	=	objects

FILES_CHECK			=	utils/utils.hpp \
						Server/Config/Config.hpp \
						Server/Display/Display.hpp \
						Server/Server.hpp \
						Server/Runtime.hpp \
						User/Command/Command.hpp \
						User/User.hpp
FILES_SOURCE		=	utils/utils.cpp \
						Server/Config/Config.cpp \
						Server/Display/Display.cpp \
						Server/Server.cpp \
						Server/Runtime.cpp \
						User/Command/NICK.cpp \
						User/Command/USER.cpp \
						User/Command/MOTD.cpp \
						User/Command/QUIT.cpp \
						User/Command/MODE.cpp \
						User/Command/PING.cpp \
						User/Command/Command.cpp \
						User/Command/replies.cpp \
						User/User.cpp \
						main.cpp

COMPILE				=	clang++
COMPILATION_FLAG	=	-Wall -Wextra -Werror -std=c++98 -pedantic-errors -g

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

debugflags:
	$(eval COMPILATION_FLAG=-D DEBUG)

debug: debugflags rrun

.PHONY: all run clean fclean re rrun leaks debugflags debug
.SILENT:
