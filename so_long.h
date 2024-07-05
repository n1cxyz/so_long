#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <string.h>
#include "libft.h"
#include <fcntl.h>
#include <errno.h>


# define MLX_ERROR 1
# define SPRITE_SIZE 32

# define FLOOR "./textures/grass.xpm"
# define WALL "./textures/wall.xpm"
# define COLLECTIBLE "./textures/trans_char.xpm"
# define EXIT_OPEN "./textures/port1.xpm"
# define EXIT_CLOSED "./textures/closed.xpm"
# define PLAYER_FRONT "./textures/guy_front.xpm"
# define PLAYER_BACK "./textures/guy_back.xpm"
# define PLAYER_LEFT "./textures/guy_left.xpm"
# define PLAYER_RIGHT "./textures/guy_right.xpm"
# define EXIT_OPEN_2 "./textures/port2.xpm"
# define EXIT_OPEN_3 "./textures/port3.xpm"
# define UP 13
# define LEFT 2
# define DOWN 1
# define RIGHT 2

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

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*wall_ptr;
	void	*floor_ptr;
	void	*player_front_ptr;
	void	*player_back_ptr;
	void	*player_left_ptr;
	void	*player_right_ptr;
	void	*collectible_ptr;
	void	*open_exit_ptr;
	void	*open_2_exit_ptr;
	void	*open_3_exit_ptr;
	void	*closed_exit_ptr;
	char	**map;
	char	*map_file;
	char	*buffer;
	int		map_x;
	int		map_y;
	int		player_x;
	int		player_y;
	int		player_direction;
	int		win_width;
	int		win_height;
	int		img_width;
	int		img_height;
	int		moves;
	int		x;
	int		y;
	const char *filename;
	int		collectible_count;
	int		animation_count;
}	t_data;