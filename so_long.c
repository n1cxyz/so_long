/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:52:13 by dasal             #+#    #+#             */
/*   Updated: 2024/07/01 12:52:15 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_create_map(t_data *data, char *file);
void	ft_initialize_variables(t_data *data);
//		parsing
void	ft_parse_map(t_data *data);
void	ft_find_player(t_data *data);
//		error
void	ft_error_free_exit(char **map, char *message);
void	ft_error_exit(char *message);
void	ft_free_map(char **map);
//		rendering
int		ft_render_map(t_data *data);
void	ft_render_background(t_data *data);
int		ft_render_player(t_data *data);
void	ft_render_sprite(t_data *data, int x, int y);
void	ft_render_player_sprite(t_data *data);
//		utils
char	*ft_strappend(char *s1, char *s2);
//		mlx
void	ft_file_to_image(t_data *data);
int		ft_initialize_mlx(t_data *data);
//		hooks
void	ft_create_hooks(t_data *data);
int		ft_handle_keypress(int keysym, t_data *data);

int	main(int ac, char **av)
{
	t_data	data;
	if (ac == 2)
	{
		//ft_initialize_variables(&data);
		ft_create_map(&data, av[1]);
		ft_parse_map(&data);
		ft_initialize_mlx(&data);
		//ft_render_map(&data);
		ft_create_hooks(&data);
		mlx_loop(data.mlx_ptr);
		
	}
	else
		printf("Failed");

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
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		printf("ESC key pressed. Exiting program.\n");
		exit (EXIT_FAILURE);
	}
	if (keysym == XK_w)
	{
		if (!(data->map[data->player_y - 1][data->player_x] == '1'))
			data->player_y -= 1;
		printf("w key pressed.\n");
		printf("player coordinates:%d %d\n", data->player_y, data->player_x);
	}
	return (0);
}
int	ft_render_map(t_data *data)
{	
	ft_render_background(data);
	ft_render_player_sprite(data);
	return (0);
}

/* int	ft_render_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->map_y = 0;
	while (y < data->win_height)
	{
		x = 0;
		data->map_x = 0;
		while (x < data->win_width)
		{
			if (data->map[y][x] == 'P')
			{
				ft_render_player_sprite(data);
				return (0);
			}
			x++;
			data->map_x += SPRITE_SIZE;
		}
		y++;
		data->map_y += SPRITE_SIZE;		
	}
	return (1);
} */

void	ft_render_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->map_y = 0;
	while (y < data->win_height)
	{
		x = 0;
		data->map_x = 0;
		while (x < data->win_width)
		{
			ft_render_sprite(data, x, y);
			x++;
			data->map_x ++;
		}
		y++;
		data->map_y ++;		
	}
}

void	ft_render_sprite(t_data *data, int x, int y)
{
	char	type;

	type = data->map[y][x];
	if (type == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->wall_ptr, data->map_x * 36, data->map_y * 36);
	/* if (type == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_ptr, data->player_x, data->player_y); */
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->floor_ptr, data->map_x * 36, data->map_y * 36);
}

void	ft_render_player_sprite(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
	data->player_ptr, data->player_x * 36, data->player_y * 36);
}

int	ft_initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
	data->win_width * SPRITE_SIZE, data->win_height * SPRITE_SIZE, "so_long");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (MLX_ERROR);
	}
	ft_file_to_image(data);
	//mlx_loop(data->mlx_ptr);
	return (0);
}

void	ft_create_map(t_data *data, char *file)
{
	int		fd;
	char	*buffer;
	char	*result;

	data->map_file = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_exit("error opening file\n");
	while (1)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		data->map_file = ft_strappend(data->map_file, buffer);
		free (buffer);
	}
	close(fd);
	data->map = ft_split(data->map_file, '\n');
	if (!data->map)
		{
			free (data->map_file);
			ft_error_free_exit(data->map, "failed to initialize map\n");
		}
	free (data->map_file);
}
/* void	ft_initialize_variables(t_data *data)
{
	
} */

void	ft_error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit (EXIT_FAILURE);
}

void	ft_error_free_exit(char **map, char *message)
{
	ft_free_map(map);
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
}

void	ft_file_to_image(t_data *data)
{
	data->floor_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	"./textures/floor.xpm", &data->img_width, &data->img_height);
	if (data->floor_ptr == NULL) {
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
	data->wall_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	"./textures/wall.xpm", &data->img_width, &data->img_height);
	if (data->wall_ptr == NULL) {
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
	data->player_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	"./textures/player.xpm", &data->img_width, &data->img_height);
	if (data->player_ptr == NULL) {
       fprintf(stderr, "Error: Failed to load sprite image\n");
       exit (MLX_ERROR);
	}
}

void	ft_parse_map(t_data *data)
{
	int	i;

	i = 1;
	data->win_height = 1;
	data->win_width = ft_strlen(data->map[0]);
	while (data->map[i] != NULL)
	{
		if (ft_strlen(data->map[i]) != data->win_width)
		{
			printf("wrong line length");
			exit (EXIT_FAILURE);
		}
		data->win_height++;
		i++;
	}
	ft_find_player(data);
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