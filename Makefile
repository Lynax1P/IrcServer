NAME = ircserv
CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

APP_DIR = application/
APP_FILES = main.cpp \
			Server.cpp

CLIENT_DIR = clients/
CLIENT_FILES = 	Channel.cpp \
				User.cpp

SERVICE_DIR = service/
SERVICE_FILES = 	Postman.cpp\
				UserService.cpp \

UTIL_DIR = $(SERVICE_DIR)utility/
UTIL_FILE = 	utils.cpp

COMMAND_DIR = $(SERVICE_DIR)command/
COMMAND_FILES = 	pass.cpp \
				   	privmsg.cpp \
					userc.cpp \
					nick.cpp \
					away.cpp \
					pong.cpp\
					join.cpp \
					names.cpp \
					part.cpp \
				   	invite.cpp \
					kick.cpp \
					quit.cpp \
				   	topic.cpp \
					notice.cpp \
					list.cpp \
					ison.cpp \
					oper.cpp \
					wallops.cpp \
					mode.cpp

OBJ_DIR  = ./obj/
OBJS_NAME = $(APP_FILES:.cpp=.o) $(CLIENT_FILES:.cpp=.o) $(SERVICE_FILES:.cpp=.o) $(UTIL_FILE:.cpp=.o) $(COMMAND_FILES:.cpp=.o)

SOURCES = 	$(addprefix $(APP_DIR), $(APP_FILES)) \
			$(addprefix $(CLIENT_DIR), $(CLIENT_FILES)) \
			$(addprefix $(SERVICE_DIR), $(SERVICE_FILES)) \
			$(addprefix $(UTIL_DIR), $(UTIL_FILE)) \
			$(addprefix $(COMMAND_DIR), $(COMMAND_FILES))

OBJS_FILES =	$(addprefix $(OBJ_DIR), $(OBJS_NAME))

.PHONY: all clean fclean re

all : $(NAME)

$(NAME): 	$(OBJS_FILES)
			@$(CPP) $(CPPFLAGS) $(OBJS_FILES) -o $(NAME)
			@echo "Makefile COMPLETED."

$(OBJS_FILES): $(SOURCES)
				@mkdir -p $(OBJ_DIR)
				@$(CPP) $(CPPFLAGS) -c $(SOURCES)
				mv $(OBJS_NAME) $(OBJ_DIR)
clean :
		@rm -rf $(OBJ_DIR)

fclean:	clean
		@rm -f $(NAME)

re: 	fclean all