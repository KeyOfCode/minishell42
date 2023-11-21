NAME = minishell
LIBFT = libft/libft.a

CC = gcc 
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
CLEAN = rm -f

SRC := \
	src/get_path.c \
	src/absolute_path.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ./libft
	
clean:
	$(CLEAN) $(OBJS)
	make clean -C ./libft

fclean: clean
	$(CLEAN) $(NAME)
	make fclean -C ./libft

re: fclean all
.PHONY: all clean fclean re bonus