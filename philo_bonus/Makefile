# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caugusta <caugusta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/15 17:22:08 by caugusta          #+#    #+#              #
#    Updated: 2021/08/17 15:06:40 by caugusta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = main.c utils.c actions.c my_usleep.c
OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. 

.PHONY : bonus clean fclean re

bonus: ${NAME}

${OBJS} : philo.h

${NAME} : ${OBJS}
	${CC} ${CFLAGS} -o $@ $^

clean: 
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re:	fclean all