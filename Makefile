NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

SRCS = main.c \
	checker.c \
	checker_utils.c \
	init.c \
	time_utils.c \
	philo.c \
	philo_utils.c \
	simulation.c \
	monitor.c 
	

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re