NAME = minishell

#LEAK= memory-leaks/memory_leaks.a

CC=			gcc
RM=			rm -f
CFLAGS=		-Wall -Wextra -Werror

HEADER=		include/minishell.h

############################

SOURCES_LIST =	main.c parser.c

SOURCES_DIR = src/
SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCES_LIST))

# BONUS_LIST =	

# BONUS_DIR = philo_bonus/src/
# BONUS = $(addprefix $(BONUS_DIR), $(BONUS_LIST))

OBJECTS_DIR = ./obj/
OBJECTS		= $(SOURCES:.c=.o)
# OBJECTS_B	= $(BONUS:.c=.o)

############################

all: $(NAME)

# $(LEAK)

$(NAME): $(SOURCES) $(OBJECTS) $(HEADER) $(LEAK)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

# bonus: $(NAME_B)

# $(NAME_B): $(OBJECTS_B)
# 	$(CC) $(CFLAGS) $(OBJECTS_B) -o $(NAME_B)
# 	@echo "$(NAME): $(GREEN)$(NAME_B) was created$(RESET)"

exe:
	@make

%.o: %.c
	$(CC) $(FLAGS)  -o $@ -c $<

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c 
# 	mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(NAME)
	@rm -f debug
	@echo "$(RED)$(NAME) deleted$(RESET)"
	
fclean:		clean
	@find philo/src -name "*.o" -delete
	@echo "$(RED)Deleting all .o Files$(RESET)"
	
re:		fclean all

.PHONY:	all clean fclean re

push:
	git add .
	git commit -m "push"
	git push origin master

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