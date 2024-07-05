CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libft -I./mlx_linux
LDFLAGS = -L./libft -lft -L./mlx_linux -lX11 -lXext

SRC = events.c
OBJ = $(SRC:.c=.o)

NAME = so_long

gcc -o so_long so_long.c -L./mlx_linux -lmlx -lX11 -lXext -I./libft -L./libft -lft

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJS) ${LDFLAGS} -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re