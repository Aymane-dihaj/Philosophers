NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror
SRC =	main.c \
		utils.c \
		load.c \
		threads.c \
		actions.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all