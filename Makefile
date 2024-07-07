NAME 		= so_long
NAME_BONUS	= so_long_bonus
CC			= gcc
BIN			= bin
BIN_BONUS	= bin_bonus
SRC			= src/so_long.c \
				src/errors.c \
				src/hooks.c \
				src/loading.c\
				src/parse_map.c\
				src/rendering.c\
				src/utils.c
SRC_BONUS	= bonus_src/so_long_bonus.c \
				bonus_src/errors_bonus.c \
				bonus_src/hooks_bonus.c \
				bonus_src/loading_bonus.c\
				bonus_src/parse_map_bonus.c\
				bonus_src/rendering_bonus.c\
				bonus_src/utils_bonus.c\
				bonus_src/bonus_bonus.c
OBJS		= $(SRC:src/%c=$(BIN)/%o)
OBJS_BONUS	= $(SRC_BONUS:bonus_src/%c=$(BIN_BONUS)/%o)
INCS		= include
LIBFT		= libft
LIBFT_INCS	= $(LIBFT)
LIBMLX_INCS = /usr/local/include
LIBMLX		= /usr/local/lib
CFLAGS		= -Wall -Werror -Wextra -g -D LINUX
LFLAGS		= -L$(LIBFT) -lft -L$(LIBMLX) -lmlx -lbsd -lXext -lX11 -lm
IFLAGS		= -I$(INCS) -I$(LIBFT_INCS) -I$(LIBMLX_INCS)
RM			= rm -rf
VALGRIND	= @valgrind --leak-check=full --show-leak-kinds=all
#--track-origins=yes --quiet --tool=memcheck --keep-debuginfo=yes

all: $(NAME)

$(NAME): ${BIN} ${OBJS} | ${LIBFT}
	${CC} ${OBJS} ${LFLAGS} -o ${NAME}

bonus: $(NAME_BONUS)

$(NAME_BONUS): ${BIN_BONUS} ${OBJS_BONUS} | ${LIBFT}
	${CC} ${OBJS_BONUS} ${LFLAGS} -o ${NAME_BONUS}

$(BIN_BONUS)/%o: bonus_src/%c
	${CC} -c $< ${CFLAGS} ${IFLAGS} -o $@

$(BIN_BONUS):
	mkdir -p $(BIN_BONUS)

$(BIN)/%o: src/%c
	${CC} -c $< ${CFLAGS} ${IFLAGS} -o $@

$(BIN):
	mkdir -p $(BIN)

$(LIBFT):
	@make all -C $(LIBFT) --no-print-directory

clean:
	$(RM) $(BIN) $(BIN_BONUS)

fclean: clean
	$(RM) $(NAME) ${NAME_BONUS}
	@make fclean -C $(LIBFT) --no-print-directory

re: fclean all

rebonus: fclean ${NAME_BONUS}

test: ${NAME}
	${VALGRIND} ./${NAME} maps/map.ber

testbonus: ${NAME_BONUS}
	${VALGRIND} ./${NAME_BONUS} maps/enemy.ber

show:
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "IFLAGS		: $(IFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJS		: $(OBJS)\n"

.PHONY: $(LIBFT) re all clean fclean