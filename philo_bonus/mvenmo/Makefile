# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 09:17:58 by mvenmo            #+#    #+#              #
#    Updated: 2022/03/02 10:21:01 by mvenmo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus
SRCS	=	main_bonus.c philosopher_bonus.c

OBJS	=	${SRCS:.c=.o}
DEPS	=	${SRCS:.c=.d}

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
DFLAGS	=	-MMD

.PHONY:		all clean fclean re

all:		${NAME}

-include ${DEPS}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} $^ -o $@

%.o:		%.c Makefile
			${CC} ${CFLAGS} ${DFLAGS} -c $< -o $@

clean:
			rm -f ${OBJS} ${DEPS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all
