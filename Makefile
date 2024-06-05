CC = cc
CFLAGS = -Wall -Wextra -Werror  -fsanitize=thread -g3
NAME = philo
obj = ${SRC:.c=.o}
SRC = philo.c ft_atoi.c init.c monitor.c philo_tasks.c tools.c

all	  : ${NAME}

${NAME}: ${obj}
	${CC} ${CFLAGS} ${obj}  -o ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@
	
clean :
	@rm -fr ${obj}


fclean : clean
	@rm -fr ${NAME}

re : fclean all
.SECONDARY : ${obj}
