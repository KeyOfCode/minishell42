NAME = minishell

#LEAK= memory-leaks/memory_leaks.a

CC=			gcc
RM=			rm -f
CFLAGS=		-Wall -Wextra -Werror
LIBFT =		libft/libft.a
INCLUDES=	$(LIBFT)
HEADER=		include/minishell.h
LIB=		-lreadline  -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
#  -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
COMMIT:=	""
BRANCH:=	""


############################

SOURCES_LIST =	main.c

SOURCES_DIR = src/
SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCES_LIST))

# BONUS_LIST =	

# BONUS_DIR = philo_bonus/src/
# BONUS = $(addprefix $(BONUS_DIR), $(BONUS_LIST))

OBJS_DIR = obj/
OBJECTS = $(SOURCES:.c=.o)
# OBJECTS = $(addprefix $(OBJECTS_DIR), $(SOURCES_LIST:.c=.o))
# OBJECTS_B	= $(BONUS:.c=.o)

############################

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft/ all
# $(LEAK)

$(NAME): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIB) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

# $(NAME): $(INCLUDES)
# 	$(CC) src/main.c libft/libft.a include/minishell.h -o $(NAME)
# 	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

# bonus: $(NAME_B)

# $(NAME_B): $(OBJECTS_B)
# 	$(CC) $(CFLAGS) $(OBJECTS_B) -o $(NAME_B)
# 	@echo "$(NAME): $(GREEN)$(NAME_B) was created$(RESET)"

exe:
	@make
	./$(NAME)

%.o: %.c
#	mkdir -pv $(@)
	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c 
# 	mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJECTS):
# 	@mkdir $(OBJ_DIR)

clean:
	@rm -f $(NAME)
	@rm -f debug
	@echo "$(RED)$(NAME) deleted$(RESET)"
	
fclean:		clean
	@find src -name "*.o" -delete
	@echo "$(RED)Deleting all .o Files$(RESET)"
	
re:		fclean all

.PHONY:	all clean fclean re push

push:
	git add . 
	read -p "commit: " COMMIT && git commit -m "${COMMIT}"
	read -p "branch: " BRANCH; git push origin $(BRANCH)

git:
	./push.sh

test: $(OBJECTS) 
	@$(CC) -g $(CFLAGS) $(OBJECTS) $(LIBS) $(HEADERS) test.c -o test
	./test

debug: clean
	@$(CC) -g $(CFLAGS) $(SOURCES) -o debug
	lldb ./debug 2 410 200 200

############################

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

############################