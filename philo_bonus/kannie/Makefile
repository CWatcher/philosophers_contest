NAME		=	philo_bonus

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror
HEADER		=	philo.h

SRCS		=	philo.c philo_utils.c philo_create.c \
				philo_time.c values.c philo_check.c

OBJS		=	${SRCS:%.c=%.o}

RM			=	rm -f

${NAME}:	$(OBJS)
			$(CC) $(OBJS) -lpthread -o $(NAME)

%.o:		%.c
			$(CC) ${FLAGS} -c $< -o $@
			
all:		${NAME}

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re