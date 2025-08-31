NAME	= philosophers
CC		= clang
CFLAGS	= -pthread -Wall -Wextra -Werror

SRCS	= main.c \
		free.c \
		init.c \
		routine.c \

OBJS	= $(SRCS:.c=.o)
all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make clean

re: fclean all

.PHONY: all clean fclean re