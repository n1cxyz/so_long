#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define BUFFER_SIZE 1000000

#define Wall "./textures/wooden.xpm"
#define Floor "./textures/grass.xpm"
#define Player "./textures/Skeleton.xpm"

#define MLX_ERROR 1

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*wall_ptr;
	void	*grass_ptr;
	void	*player_ptr;
	int		img_width;
	int		img_height;
	int		x;
	int		y;
	int		sprite_x;
	int		sprite_y;
	int		grass_x;
	int		grass_y;
	int		player_x;
	int		player_y;
}	t_data;

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

void render_wall(t_data *data, int x, int y) {
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall_ptr, x, y);
}

void render_grass(t_data *data, int x, int y) {
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->grass_ptr, x, y);
}
void render_player(t_data *data, int x, int y) {
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player_ptr, x, y);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 53)
	{
		//mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		printf("ESC key pressed. Exiting program.\n");
		exit (EXIT_FAILURE);
	}
	if (keysym == 13)
	{

		render_grass(data, data->player_x, data->player_y);
		data->player_y -= 16;
		render_player(data, data->player_x, data->player_y);
	}
	if (keysym == 0)
	{
		render_grass(data, data->player_x, data->player_y);
		data->player_x -= 16;
		render_player(data, data->player_x, data->player_y);
	}
	if (keysym == 1)
	{
		render_grass(data, data->player_x, data->player_y);
		data->player_y += 16;
		render_player(data, data->player_x, data->player_y);
	}
	if (keysym == 2)
	{
		render_grass(data, data->player_x, data->player_y);
		data->player_x += 16;
		render_player(data, data->player_x, data->player_y);
	}
	/* if (keysym == 1)
	{
		data->y += 16;
		render_wall(data, data->x, data->y);
	}
	if (keysym == 6)
	{
		data->x += 16;
		render_grass(data, data->x, data->y);
	}
	if (keysym == 7)
	{
		data->y += 16;
		render_grass(data, data->x, data->y);
	} */
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	main(void)
{
	t_data	data;
	char	buffer[BUFFER_SIZE];
	int		fd;
	ssize_t	bytes_read;
	const char *map_path = "./maps/large_map.ber";
	int	i;

	fd = open(map_path, O_RDONLY);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (bytes_read == -1) 
		{
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
   		}
	}
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	data.wall_ptr = mlx_xpm_file_to_image(data.mlx_ptr, Wall, &data.img_width, &data.img_height);
    if (data.wall_ptr == NULL) {
        fprintf(stderr, "Error: Failed to load sprite image\n");
        return MLX_ERROR;
    }
	data.grass_ptr = mlx_xpm_file_to_image(data.mlx_ptr, Floor, &data.img_width, &data.img_height);
    if (data.grass_ptr == NULL) {
        fprintf(stderr, "Error: Failed to load sprite image\n");
        return MLX_ERROR;
    }
	data.player_ptr = mlx_xpm_file_to_image(data.mlx_ptr, Player, &data.img_width, &data.img_height);
    if (data.player_ptr == NULL) {
        fprintf(stderr, "Error: Failed to load sprite image\n");
        return MLX_ERROR;
    }
	i = 0;
	data.sprite_x = 0;
	//data.grass_x = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			data.sprite_y += 16;
			//data.grass_y += 16;
			data.sprite_x = 0;
			//data.grass_x = 0;
		}
		else 
		{
			if (buffer[i] == '1')
			{
				render_wall(&data, data.sprite_x, data.sprite_y);
			}
			if (buffer[i] == '0')
			{
				render_grass(&data, data.sprite_x, data.sprite_y);
			
			}
			//data.grass_x += 16;
		/*  if (buffer[i] == 'C')
		{
			data.grass_x += 16;
			data.wall_x += 16;
		}
		if (buffer[i] == 'E')
		{
			data.grass_x += 16;
			data.wall_x += 16;
		}	 */
			if (buffer[i] == 'P')
			{
				data.player_x = data.sprite_x;
				data.player_y = data.sprite_y;
				render_player(&data, data.sprite_x, data.sprite_y);
			}
			data.sprite_x += 16;
		}
		i++;
	}
	/* Setup hooks */ 
	//mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); /* ADDED */

	//render_sprite(&data, 0, 0);
	//render_sprite(&data, 0, 16);
	//render_sprite(&data, 0, 32);
	data.x = 0;
	data.y = 0;
	mlx_loop(data.mlx_ptr);

	/* exit the loop if there's no window left, and execute this code */
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	free(data.mlx_ptr);
}
