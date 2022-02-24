# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/11 16:09:16 by nagrivan          #+#    #+#              #
#    Updated: 2021/09/16 20:00:52 by nagrivan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	=	philo_start.c \
			philo_utils.c \
			philo_init.c \
			philo_life.c \
			philo_monitor.c \
			philo_print.c
			
OBJS	= ${SRCS:.c=.o}

INCLUDES	= philo.h

CC	= gcc

CFLAGS	= -g -Wall -Wextra -Werror

RM	= rm -rf

all: $(NAME)

%.o : %.c ${INCLUDES}
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
		 ${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

norma:
		norminette ${SRCS} ${INCLUDES}

.PHONY: all clean fclean re norma
