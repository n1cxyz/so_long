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
# define SPRITE_SIZE 36

# define FLOOR 0
# define WALL 1
# define COLLECTIBLE 2
# define EXIT 3
# define PLAYER 4
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
	void	*player_ptr;
	void	*collectible_ptr;
	void	*open_exit_ptr;
	void	*closed_exit_ptr;
	char	**map;
	char	*map_file;
	char	*buffer;
	int		map_x;
	int		map_y;
	int		win_width;
	int		win_height;
	int		img_width;
	int		img_height;
	int	x;
	int	y;
	const char *filename;


}	t_data;