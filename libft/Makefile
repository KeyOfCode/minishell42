# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darismen <darismen@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 11:41:39 by darismen          #+#    #+#              #
#    Updated: 2024/03/17 20:25:37 by darismen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		libft.a

FILES=	ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isprint.c \
		ft_isupper.c ft_islower.c ft_strlen.c  ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_memmove.c ft_calloc.c ft_strlcpy.c ft_strlcat.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_chrrmv.c\
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_strndup.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstclear.c		\
				ft_lstdelone.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
		ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_printf_util.c \
		get_next_line.c ft_putnbr_base_fd.c \


SRCS= $(addprefix src/, ${FILES})
#OBJS=	${SRCS:.c=.o}
OBJS=	$(addprefix objs/, ${FILES:.c=.o})
INC= includes/

CC=			gcc
RM=			rm -rf
AR=			ar -rcs
CFLAGS=		-Wall -Wextra -Werror -Iincludes/ 


all:	${NAME}

${NAME}: ${OBJS}
	@${AR} ${NAME} ${OBJS}

${OBJS}: ${SRCS}
	@$(CC) $(CFLAGS) -c $(SRCS)
	@rm -rf objs
	@mkdir objs
	@mv ${FILES:.c=.o} objs

#%.o: %.c
#	@$(CC) $(CFLAGS) -I/includes -c $< -o $@

clean:
	@${RM} objs
fclean:		clean
	@${RM} ${NAME}
re:		fclean ${NAME}

.PHONY:	all clean fclean re