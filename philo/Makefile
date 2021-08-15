# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 17:22:08 by caugusta          #+#    #+#              #
#    Updated: 2021/08/15 18:10:16 by caugusta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c utils.c actions.c
OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. 

.PHONY : all clean fclean re

all: ${NAME}

${OBJS} : philo.h

${NAME} : ${OBJS}
	${CC} ${CFLAGS} -o $@ $^

clean: 
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re:	fclean all