NAME = minishell
LIBFT = libft/libft.a

CC = gcc 
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
CLEAN = rm -f

SRC := \
	src/parser/new_pipe_node.c \

#	src/expander/expand_env.c \
	src/expander/get_path.c \
	src/expander/absolute_path.c \
	src/parser/new_pipe_node.c \
	src/parser/parser.c \
	src/parser/redierctions.c \
	src/utils/list_utils.c \
	src/utils/matrix_utils.c \

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