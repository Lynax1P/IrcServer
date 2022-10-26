NAME	=	bot

SRCS	=	src/Bot.cpp\
			src/main.cpp\
			../service/utility/utils.cpp\


HEADERS	=	src/Bot.hpp\
			../service/utility/utils.hpp\

VPATH	=	sources/

OBJ_DIR	=	./obj/
OBJS	=	$(SRCS:.cpp=.o)	\

CPPFLAGS = -Wall -Werror -Wextra

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADERS)
			c++ $(CPPFLAGS) $(OBJS) -o $(NAME)

clean	:
			@rm -rf $(OBJS)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all