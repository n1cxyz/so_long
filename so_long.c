/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dominicasal <dominicasal@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:52:13 by dasal             #+#    #+#             */
/*   Updated: 2024/07/05 06:31:34 by dominicasal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_create_map(t_data *data, char *file);
void	ft_initialize_variables(t_data *data);
//		parsing
void	ft_parse_map(t_data *data, char *map_file);
void	ft_find_player(t_data *data);
int		ft_check_file_format(char *str);
int		ft_check_walls(t_data *data);
//		error
void	ft_error_free_exit(char **map, char *message);
void	ft_error_exit(char *message);
void	ft_free_map(char **map);
void	ft_error_free_map_exit(char **map, char *message);
void	ft_error_free_all_exit(t_data *data,char **map, char *message);
void	ft_destroy_images(t_data *data);
//		rendering
int		ft_render_map(t_data *data);
void	ft_render_background(t_data *data);
void	ft_render_sprite(t_data *data, int x, int y);
void	ft_render_player(t_data *data);
void	ft_render_animation(t_data *data, int x, int y);
//		utils
char	*ft_strappend(char *s1, char *s2);
//		mlx
void	ft_file_to_image(t_data *data);
void	ft_player_to_image(t_data *data);
void	ft_animation_to_image(t_data *data);
int		ft_initialize_mlx(t_data *data);
//		hooks
void	ft_create_hooks(t_data *data);
int		ft_handle_keypress(int keysym, t_data *data);

int	main(int ac, char **av)
{
	t_data	data;
	if (ac == 2)
	{
		ft_initialize_variables(&data);
		ft_create_map(&data, av[1]);
		ft_parse_map(&data, av[1]);
		ft_initialize_mlx(&data);
		//ft_render_map(&data);
		ft_create_hooks(&data);
		mlx_loop(data.mlx_ptr);
		
	}
	else
		write(2, "Error\nmap file missing", 22);
	/* TO DO:
	https://reactive.so/post/42-a-comprehensive-guide-to-so_long
	-check memory management
	-close window with x 
	-file to image error handling
	-map parsing
	-sprite transparency
	-exit game if game won 
	-movement count on screen 
	-sprite animation
	-enemy */
	return (0);
}

void	ft_create_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, \
	ft_handle_keypress, data);
	mlx_loop_hook(data->mlx_ptr, ft_render_map, data);
}

int	ft_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape || keysym == 53)
		ft_error_free_all_exit(data,data->map, "ESC key pressed. Exiting program.\n");
	if (keysym == XK_w || keysym == 13)
	{
		if ((data->map[data->player_y - 1][data->player_x] != '1') && ((data->map[data->player_y - 1][data->player_x] != 'E' || data->collectible_count == 0)))
			data->player_y -= 1;
		data->player_direction = 1;
	}
    if (keysym == XK_a || keysym == 0)
	{
		if ((data->map[data->player_y][data->player_x - 1] != '1') && ((data->map[data->player_y][data->player_x - 1] != 'E' || data->collectible_count == 0)))
			data->player_x -= 1;
			data->player_direction = 2;
	}
    if (keysym == XK_s || keysym == 1)
	{
		if ((data->map[data->player_y + 1][data->player_x] != '1') && ((data->map[data->player_y + 1][data->player_x] != 'E' || data->collectible_count == 0)))
			data->player_y += 1;
			data->player_direction = 3;
	}
    if (keysym == XK_d || keysym == 2)
	{
		if ((data->map[data->player_y][data->player_x + 1] != '1') && ((data->map[data->player_y][data->player_x + 1] != 'E' || data->collectible_count == 0)))
			data->player_x += 1;
		data->player_direction = 4;
	}
    data->moves++;
    printf("Moves: %d\n", data->moves);

	if (data->map[data->player_y][data->player_x] == 'C')
	{
		data->map[data->player_y][data->player_x] = '0';
		data->collectible_count--;
		printf("collectibles:%d\n", data->collectible_count);
	}
	return (0);
}
int	ft_render_map(t_data *data)
{	
	ft_render_background(data);
	ft_render_player(data);
	return (0);
}

void	ft_render_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			ft_render_sprite(data, x, y);
			x++;
		}
		y++;
	}
}

void	ft_render_sprite(t_data *data, int x, int y)
{
	char	type;

	type = data->map[y][x];
	if (type == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->wall_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE);
	else if (type == 'E' && data->collectible_count != 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->closed_exit_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE);
	else if (type == 'E' && data->collectible_count == 0)
		/* mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->open_exit_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE); */
		ft_render_animation(data, x, y);
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->floor_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE);
	if (type == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->collectible_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE);
}

void	ft_render_animation(t_data *data, int x, int y)
{
	if (data->animation_count == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->open_exit_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE);
	if (data->animation_count == 20)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->open_2_exit_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE);
	if (data->animation_count == 40)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->open_3_exit_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE); 
	data->animation_count++;
	if (data->animation_count == 60)
		data->animation_count = 0;
}

void	ft_render_player(t_data *data)
{
	if (data->player_direction == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_front_ptr, data->player_x * SPRITE_SIZE, data->player_y * SPRITE_SIZE - 6);
	if (data->player_direction == 2)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_left_ptr, data->player_x * SPRITE_SIZE, data->player_y * SPRITE_SIZE - 6);
	if (data->player_direction == 3)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_back_ptr, data->player_x * SPRITE_SIZE, data->player_y * SPRITE_SIZE - 6);
	if (data->player_direction == 4)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_right_ptr, data->player_x * SPRITE_SIZE, data->player_y * SPRITE_SIZE - 6);
	
}

int	ft_initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_error_free_map_exit(data->map, "Error\nfailed to initialize mlx");
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
	data->win_width * SPRITE_SIZE, data->win_height * SPRITE_SIZE, "so_long");
	if (data->win_ptr == NULL)
	{
		free(data->mlx_ptr);
		ft_error_free_map_exit(data->map, "Error\nfailed to create new window");
	}
	ft_file_to_image(data);
	return (0);
}

void	ft_create_map(t_data *data, char *file)
{
	int		fd;
	char	*buffer;
	char	*result;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_exit("Error\nerror opening file\n");
	while (1)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		data->map_file = ft_strappend(data->map_file, buffer);
		free (buffer);
	}
	if (buffer == NULL && data->map_file == NULL)
		ft_error_exit("Error\nEmpty file\n");
	close(fd);
	data->map = ft_split(data->map_file, '\n');
	if (!data->map)
		{
			free (data->map_file);
			ft_error_free_map_exit(data->map, "failed to initialize map\n");
		}
	free (data->map_file);
}
void	ft_initialize_variables(t_data *data)
{
    data->moves = 0;
	data->collectible_count = 0;
	data->player_direction = 1;
	data->map_file = NULL;
	data->animation_count = 0;
	
}

void	ft_error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit (EXIT_FAILURE);
}

void	ft_error_free_map_exit(char **map, char *message)
{
	ft_free_map(map);
	write(2, message, ft_strlen(message));
	exit (EXIT_FAILURE);
}

void	ft_error_free_all_exit(t_data *data,char **map, char *message)
{
	ft_destroy_images(data);
	ft_free_map(map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	write(2, message, ft_strlen(message));
	exit (EXIT_FAILURE);
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free (map);
}

void	ft_file_to_image(t_data *data)
{
	ft_player_to_image(data);
	ft_animation_to_image(data);
	data->floor_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	FLOOR, &data->img_width, &data->img_height);
	if (data->floor_ptr == NULL) {
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
	data->wall_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	WALL, &data->img_width, &data->img_height);
	if (data->wall_ptr == NULL) {
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
	data->collectible_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	COLLECTIBLE, &data->img_width, &data->img_height);
	data->open_exit_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	EXIT_OPEN, &data->img_width, &data->img_height);
	data->closed_exit_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	EXIT_CLOSED, &data->img_width, &data->img_height);

}

void	ft_player_to_image(t_data *data)
{
	data->player_front_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	PLAYER_FRONT, &data->img_width, &data->img_height);
	if (data->player_front_ptr == NULL)
	{
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
	data->player_back_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	PLAYER_BACK, &data->img_width, &data->img_height);
	if (data->player_back_ptr == NULL)
	{
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
	data->player_left_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	PLAYER_LEFT, &data->img_width, &data->img_height);
	if (data->player_left_ptr == NULL)
	{
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
	data->player_right_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	PLAYER_RIGHT, &data->img_width, &data->img_height);
	if (data->player_right_ptr == NULL)
	{
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
}
void	ft_animation_to_image(t_data *data)
{
	data->open_2_exit_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	EXIT_OPEN_2, &data->img_width, &data->img_height);
	if (data->open_2_exit_ptr == NULL)
	{
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
	data->open_3_exit_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	EXIT_OPEN_3, &data->img_width, &data->img_height);
	if (data->open_3_exit_ptr == NULL)
	{
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
}
void	ft_destroy_images(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->player_front_ptr);
	mlx_destroy_image(data->mlx_ptr, data->player_back_ptr);
	mlx_destroy_image(data->mlx_ptr, data->player_left_ptr);
	mlx_destroy_image(data->mlx_ptr, data->player_right_ptr);
	mlx_destroy_image(data->mlx_ptr, data->floor_ptr);
	mlx_destroy_image(data->mlx_ptr, data->wall_ptr);
	mlx_destroy_image(data->mlx_ptr, data->collectible_ptr);
	mlx_destroy_image(data->mlx_ptr, data->open_exit_ptr);
	mlx_destroy_image(data->mlx_ptr, data->closed_exit_ptr);
}

void	ft_parse_map(t_data *data, char *map_file)
{
	int	i;

	i = 1;
	data->win_height = 1;
	data->win_width = ft_strlen(data->map[0]);
	while (data->map[i] != NULL)
	{
		if (ft_strlen(data->map[i]) != data->win_width)
			ft_error_free_map_exit(data->map, "Error\nWrong line length");
		data->win_height++;
		i++;
	}
	if (data->win_width > 40 || data->win_height > 25)
		ft_error_free_map_exit(data->map, "Error\nMap too large\n");
	ft_find_player(data);
	if (!(ft_check_walls(data)))
		ft_error_free_map_exit(data->map, "Error\nMap not enclosed in walls\n");
	if (!(ft_check_file_format(map_file)))
		ft_error_free_map_exit(data->map, "Error\nWrong file format\n");
	if (data->win_height == data->win_width)
		ft_error_free_map_exit(data->map, "Error\nMap must be rectangular\n");

}

int	ft_check_walls(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->win_width)
	{
		if (data->map[0][i] != '1')
		{
			printf("1");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < data->win_width)
	{
		if (data->map[data->win_height - 1][i] != '1')
		{
			printf("2\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (data->map[i] != NULL)
	{
		if (data->map[i][0] != '1' || data->map[i][data->win_width - 1] != '1')
		{
			printf("3");
			return (0);
		}
		i++;
	}
	return (1);
}
int	ft_check_file_format(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (str[len] != 'r')
		return (0);
	if (str[len - 1] != 'e')
		return (0);
	if (str[len - 2] != 'b')
		return (0);
	if (str[len - 3] != '.')
		return (0);
	return (1);
	
}

void	ft_find_player(t_data *data)
{
	int	x;
	int	y;
	
	y = 0;
 	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			if (data->map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
			}
			if (data->map[y][x] == 'C')
				data->collectible_count++;
			x++;
		}
		y++;	
	}
}

char	*ft_strappend(char *s1, char *s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1len);
	ft_memcpy(str + s1len, s2, s2len + 1);
	str[s1len + s2len] = '\0';
	free(s1);
	return (str);
}