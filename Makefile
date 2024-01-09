NAME = minishell

#LEAK= memory-leaks/memory_leaks.a

CC=			gcc
RM=			rm -f
CFLAGS=		-Wall -Wextra -Werror
SANITZ=		-fsanitize=address
LIBFT =		libft/libft.a
INCLUDES=	$(LIBFT)
HEADER=		include/minishell.h
VALGRIND=	valgrind --leak-check=yes 
LIB=		-lreadline  -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
#  -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
COMMIT:=	""
BRANCH:=	""


############################

SOURCES_LIST =	main.c lexer.c expander.c utils.c matrix_utils.c \
				cmd.c
TEST_LIST =	test.c lexer.c expander.c utils.c matrix_utils.c

SOURCES_DIR = src/
SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCES_LIST))
TESTS = $(addprefix $(SOURCES_DIR), $(TEST_LIST))

# BONUS_LIST =	

# BONUS_DIR = philo_bonus/src/
# BONUS = $(addprefix $(BONUS_DIR), $(BONUS_LIST))

OBJS_DIR = obj/
OBJECTS = $(SOURCES:.c=.o)
TEST_OBJ = $(TESTS:.c=.o)
# OBJECTS = $(addprefix $(OBJECTS_DIR), $(SOURCES_LIST:.c=.o))
# OBJECTS_B	= $(BONUS:.c=.o)

############################

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft/ all
# $(LEAK)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) 
	@$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIB) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

# $(OBJECTS):
# 	@rm -rf objs
# 	@mkdir objs
# 	@mv $(OBJECTS) objs

exe:
	@make
	./$(NAME)

clean:
	@rm -f $(NAME)
	@rm -f debug
	@echo "$(RED)$(NAME) deleted$(RESET)"
	
fclean:		clean
	@find src -name "*.o" -delete
	@make -C libft/ clean
	@rm -f $(LIBFT)
	@rm -rf objs
	@mkdir objs
	@echo "$(RED)Deleting all .o Files$(RESET)"
	
re:		fclean all

.PHONY:	all clean fclean re push

push:
	git add . 
	read -p "commit: " COMMIT && git commit -m "${COMMIT}"
	read -p "branch: " BRANCH; git push origin $(BRANCH)

git:
	./push.sh

test: $(TEST_OBJ) 
	@$(CC) -g $(CFLAGS) $(SANITZ) $(TEST_OBJ)  $(INCLUDES) $(LIB) -o test
	./test

debug: clean $(OBJECTS) 
	@$(CC) -g $(CFLAGS) $(SANITZ) $(OBJECTS) $(INCLUDES) $(LIB) -o debug
#	lldb ./debug
	./debug

############################

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

############################