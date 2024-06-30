CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilib
SRC = src/main.c src/game.c lib/libft.c
OBJ = $(SRC:.c=.o)
NAME = so_long

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re