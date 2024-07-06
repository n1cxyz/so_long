/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dominicasal <dominicasal@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:52:13 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 00:42:49 by dominicasal      ###   ########.fr       */
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
int		ft_flood_fill(t_data *data, int y, int x);
//		error
void	ft_error_exit(char *message);
void	ft_free_map(char **map);
void	ft_error_free_map_exit(t_data *data, char *message);
void	ft_error_free_all_exit(t_data *data, char *message);
void	ft_destroy_images(t_data *data);
int		ft_close_game(t_data *data);
//		rendering
int		ft_render_map(t_data *data);
void	ft_render_background(t_data *data);
void	ft_render_sprite(t_data *data, int x, int y);
void	ft_render_player(t_data *data);
//		utils
char	*ft_strappend(char *s1, char *s2);
void	ft_print_moves(int n);
void	ft_check_collision(t_data *data, int y, int x, int direction);
int		ft_check_empty_line(char *str);
//		mlx
void	ft_file_to_image(t_data *data);
void	ft_player_to_image(t_data *data);
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
		ft_create_hooks(&data);
		mlx_loop(data.mlx_ptr);
		
	}
	else
		write(2, "Error\nmap file missing", 22);
	/* TO DO:
	https://reactive.so/post/42-a-comprehensive-guide-to-so_long
	-bonus map parsing
	-destroy display
	-fix norm
	-fix file structure
	-fix Makefile
	*/
	return (0);
}

void	ft_create_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, DestroyNotify, \
	ButtonPressMask, ft_close_game, data);
	mlx_hook(data->win_ptr, Expose, ExposureMask, ft_render_map, data);
	ft_render_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, \
	ft_handle_keypress, data);
}

void	ft_check_collision(t_data *data, int y, int x, int direction)
{
	data->player_direction = direction;
	if (data->map[y][x] != '1')
	{
		if (direction == 1)
			data->player_y -= 1;
		if (direction == 2)
			data->player_x -= 1;
		if (direction == 3)
			data->player_y += 1;
		if (direction == 4)
			data->player_x += 1;
		data->moves++;
		ft_print_moves(data->moves);
	}
}

int	ft_handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape || keysym == 53)
		ft_error_free_all_exit(data, "ESC key pressed. Exiting program.\n");
	if (keysym == XK_w || keysym == 13)
		ft_check_collision(data, data->player_y - 1, data->player_x, 1);
    if (keysym == XK_a || keysym == 0)
		ft_check_collision(data, data->player_y, data->player_x - 1, 2);
    if (keysym == XK_s || keysym == 1)
		ft_check_collision(data, data->player_y + 1, data->player_x, 3);
    if (keysym == XK_d || keysym == 2)
		ft_check_collision(data, data->player_y, data->player_x + 1, 4);
	if (data->map[data->player_y][data->player_x] == 'C')
	{
		data->map[data->player_y][data->player_x] = '0';
		data->collectible_count--;
	}
	if (data->map[data->player_y][data->player_x] == 'E' && data->collectible_count == 0)
		ft_error_free_all_exit(data, "You won!");
	ft_render_map(data);	
	return (0);
}

void	ft_print_moves(int n)
{
	char	*to_print;

	to_print = ft_itoa(n);
	if (to_print != NULL)
	{
		write(1, "Moves:", 6);
		write(1, to_print, ft_strlen(to_print));
		write(1, "\n", 1);
		free(to_print);
	} 
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
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->open_exit_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE);
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->floor_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE);
	if (type == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->collectible_ptr, x * SPRITE_SIZE, y * SPRITE_SIZE - 6);
}

void	ft_render_player(t_data *data)
{
	if (data->player_direction == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_back_ptr, data->player_x * SPRITE_SIZE, \
	data->player_y * SPRITE_SIZE - 6);
	if (data->player_direction == 2)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_left_ptr, data->player_x * SPRITE_SIZE, \
	data->player_y * SPRITE_SIZE - 6);
	if (data->player_direction == 3)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_front_ptr, data->player_x * SPRITE_SIZE, \
	data->player_y * SPRITE_SIZE - 6);
	if (data->player_direction == 4)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_right_ptr, data->player_x * SPRITE_SIZE, \
	data->player_y * SPRITE_SIZE - 6);
}

int	ft_initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_error_free_map_exit(data, "Error\nfailed to initialize mlx");
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
	data->win_width * SPRITE_SIZE, data->win_height * SPRITE_SIZE, "so_long");
	if (data->win_ptr == NULL)
	{
		free(data->mlx_ptr);
		ft_error_free_map_exit(data, "Error\nfailed to create new window");
	}
	ft_file_to_image(data);
	return (0);
}

void	ft_create_map(t_data *data, char *file)
{
	int		fd;
	char	*buffer;

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
	ft_check_empty_line(data->map_file);
	data->map = ft_split(data->map_file, '\n');
	data->map_copy = ft_split(data->map_file, '\n');
	if (!data->map || !data->map_copy)
		{
			free (data->map_file);
			ft_error_free_map_exit(data, "Error\nfailed to initialize map\n");
		}
	free (data->map_file);
}

void	ft_initialize_variables(t_data *data)
{
    data->moves = 0;
	data->collectible_count = 0;
	data->player_direction = 1;
	data->map_file = NULL;
	data->player_count = 0;
	data->exit_count = 0;	
	data->to_collect = 0;
	data->win_height = 1;
	data->wall_ptr = NULL;
	data->player_front_ptr = NULL;
	data->player_back_ptr = NULL;
	data->player_left_ptr = NULL;
	data->player_right_ptr = NULL;
	data->floor_ptr = NULL;
	data->collectible_ptr = NULL;
	data->open_exit_ptr = NULL;
	data->closed_exit_ptr = NULL;
}

void	ft_error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit (EXIT_FAILURE);
}

void	ft_error_free_map_exit(t_data *data, char *message)
{
	ft_destroy_images(data);
	ft_free_map(data->map);
	ft_free_map(data->map_copy);
	write(2, message, ft_strlen(message));
	exit (EXIT_FAILURE);
}

void	ft_error_free_all_exit(t_data *data, char *message)
{
	ft_destroy_images(data);
	ft_free_map(data->map);
	ft_free_map(data->map_copy);	
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	write(2, message, ft_strlen(message));
	exit (EXIT_FAILURE);
}

int	ft_close_game(t_data *data)
{
	ft_destroy_images(data);
	ft_free_map(data->map);
	ft_free_map(data->map_copy);	
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	write(2, "Error\n", 6);
	write(2, "closed game\n", 12);
	exit (EXIT_FAILURE);
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] && map)
	{
		free(map[i]);
		i++;
	}
	free (map);
}

void	ft_file_to_image(t_data *data)
{
	data->floor_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	FLOOR, &data->img_width, &data->img_height);
	if (data->floor_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
	data->wall_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	WALL, &data->img_width, &data->img_height);
	if (data->wall_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
	data->collectible_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	COLLECTIBLE, &data->img_width, &data->img_height);
	if (data->collectible_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
	data->open_exit_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	EXIT_OPEN, &data->img_width, &data->img_height);
	if (data->open_exit_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
	data->closed_exit_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	EXIT_CLOSED, &data->img_width, &data->img_height);
	if (data->closed_exit_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
	ft_player_to_image(data);
}

void	ft_player_to_image(t_data *data)
{
	data->player_front_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	PLAYER_FRONT, &data->img_width, &data->img_height);
	if (data->player_front_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
	data->player_back_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	PLAYER_BACK, &data->img_width, &data->img_height);
	if (data->player_back_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
	data->player_left_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	PLAYER_LEFT, &data->img_width, &data->img_height);
	if (data->player_left_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
	data->player_right_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	PLAYER_RIGHT, &data->img_width, &data->img_height);
	if (data->player_right_ptr == NULL)
		ft_error_free_all_exit(data, "failed to load immage");
}

void	ft_destroy_images(t_data *data)
{
	if (data->player_front_ptr)
		mlx_destroy_image(data->mlx_ptr, data->player_front_ptr);
	if (data->player_back_ptr)
		mlx_destroy_image(data->mlx_ptr, data->player_back_ptr);
	if (data->player_left_ptr)
		mlx_destroy_image(data->mlx_ptr, data->player_left_ptr);
	if (data->player_right_ptr)
		mlx_destroy_image(data->mlx_ptr, data->player_right_ptr);
	if (data->floor_ptr)
		mlx_destroy_image(data->mlx_ptr, data->floor_ptr);
	if (data->wall_ptr)
		mlx_destroy_image(data->mlx_ptr, data->wall_ptr);
	if (data->collectible_ptr)
		mlx_destroy_image(data->mlx_ptr, data->collectible_ptr);
	if (data->open_exit_ptr)
		mlx_destroy_image(data->mlx_ptr, data->open_exit_ptr);
	if (data->closed_exit_ptr)
		mlx_destroy_image(data->mlx_ptr, data->closed_exit_ptr);
}

void	ft_parse_map(t_data *data, char *map_file)
{
	int	i;

	i = 1;
	data->win_width = ft_strlen(data->map[0]);
	while (data->map[i] != NULL)
	{
		if (ft_strlen(data->map[i]) != data->win_width)
			ft_error_free_map_exit(data, "Error\nWrong line length\n");
		data->win_height++;
		i++;
	}
	if (data->win_width > 40 || data->win_height > 25)
		ft_error_free_map_exit(data, "Error\nMap too large\n");
	if (!(ft_check_walls(data)))
		ft_error_free_map_exit(data, "Error\nMap not enclosed in walls\n");
	ft_find_player(data);
	if ((data->player_count != 1) || (data->exit_count != 1))
		ft_error_free_map_exit(data, "Error\nwrong player or exit count\n");
	if (!(ft_check_file_format(map_file)))
		ft_error_free_map_exit(data, "Error\nWrong file format\n");
	data->exit_count = 0;
	ft_flood_fill(data, data->player_y, data->player_x);
	if ((!(data->exit_count == 1)) || \
	data->collectible_count != data->to_collect)
		ft_error_free_map_exit(data, "Error\nwrong exit or collectible\n");
}

int	ft_flood_fill(t_data *data, int y, int x)
{
	if (data->map_copy[y][x] == '1' || data->map_copy[y][x] == 'v')
		return (1);
	if (data->map_copy[y][x] == 'E')
		data->exit_count++;
	if (data->map_copy[y][x] == 'C')
		data->to_collect++;
	data->map_copy[y][x]= 'v';
	ft_flood_fill(data, y + 1, x);
	ft_flood_fill(data, y - 1, x);
	ft_flood_fill(data, y, x + 1);
	ft_flood_fill(data, y, x - 1);
	return (1);
}

int	ft_check_walls(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->win_width)
	{
		if (data->map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < data->win_width)
	{
		if (data->map[data->win_height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (data->map[i] != NULL)
	{
		if (data->map[i][0] != '1' || data->map[i][data->win_width - 1] != '1')
			return (0);
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
				data->player_count++;
				data->player_x = x;
				data->player_y = y;
			}
			if (data->map[y][x] == 'C')
				data->collectible_count++;
			if (data->map[y][x] == 'E')
				data->exit_count++;
			if (data->map[y][x] != '1' && data->map[y][x] != '0' && \
			data->map[y][x] != 'C' && data->map[y][x] != 'E' && \
			data->map[y][x] != 'P')
				ft_error_free_map_exit(data, "Error\nInvalid char\n");
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
	free (s1);
	return (str);
}

int	ft_check_empty_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\n' || str[ft_strlen(str) - 1] == '\n')
	{
		free (str);
		ft_error_exit("Error\nempty line\n");
	}
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			free (str);
			ft_error_exit("Error\nempty line\n");
		}
		i++;
	}
	return (0);
}