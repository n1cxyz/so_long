#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <string.h>
#include "libft.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1

#define FLOOR_PATH "./textures/grass.xpm"
#define WALL_PATH "./textures/wooden.xpm"
#define COLLECTIBLE_PATH
#define EXIT_PATH
#define PLAYER_PATH

#define FLOOR 0
#define WALL 1
#define COLLECTIBLE 2
#define EXIT 3
#define PLAYER 4

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		img_width;
	int		img_height;
	int		x;
	int		y;
}	t_vars;