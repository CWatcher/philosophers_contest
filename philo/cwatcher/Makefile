# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: CWatcher <cwatcher@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 18:45:13 by CWatcher          #+#    #+#              #
#    Updated: 2021/08/14 18:51:26 by CWatcher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	= utils
SRC		= main.c			\
		  main_routines.c	\
		  philo_run.c		\
		  philo_utils.c		\
		  ft_strchr.c		\
		  ft_skipchrs.c		\
		  ft_isdigit.c		\
		  ft_atoi.c 		\
		  ft_strlen.c		\
		  ft_putstr_fd.c	\
		  minmaxsign.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Wpedantic -Werror #-g -fsanitize=address
NAME	= philo

all		: $(NAME)

%.o		: %.c Makefile
	$(CC) $(CFLAGS) -Iutils -MMD -c $<

-include $(SRC:.c=.d)

$(NAME)	: $(OBJ) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread

clean	:
	$(RM) $(OBJ) $(SRC:.c=.d)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

.PHONY	: all clean fclean re force
