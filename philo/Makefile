# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/11 16:09:16 by nagrivan          #+#    #+#              #
#    Updated: 2021/09/11 17:08:04 by nagrivan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo


SRCS	= philo_start.c philo_utils.c
			
OBJS	= ${SRCS:.c=.o}

INCLUDES	= philo.h

CC	= gcc

CFLAGS	= -g -Wall -Wextra -Werror -pthread

RM	= rm -rf

all: $(NAME)

%.o : %.c
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
		 ${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
