CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libft -I./mlx_linux
LDFLAGS = -L./libft -lft -L./mlx_linux -lX11 -lXext

SRC = events.c
OBJ = $(SRC:.c=.o)

NAME = so_long

gcc -o so_long so_long.c -L./mlx_linux -lmlx -lX11 -lXext -I./libft -L./libft -lft
gcc -g -o so_long_bonus -I ./lib/libft -L ./lib/libft -lft -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit so_long_bonus.c

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