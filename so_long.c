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

void	ft_initialize_map(t_data *data, char *file);
void	ft_initialize_variables(t_data *data);
char	*ft_strappend(char *s1, char *s2);
int		ft_initialize_mlx(t_data *data);
void	ft_parse_map(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;
	if (ac == 2)
	{
		//ft_initialize_variables(&data);
		ft_initialize_map(&data, av[1]);
		ft_parse_map(&data);
		ft_initialize_mlx(&data);
		
	}
	else
		printf("Failed");

	return (0);
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
}

int	ft_initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width * 16, \
									data->win_height * 16, "so_long");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (MLX_ERROR);
	}
	printf("width:%d\n", data->win_width);
	printf("heigth:%d\n", data->win_height);
	/* data->wall_ptr = mlx_xpm_file_to_image(data->mlx_ptr, Wall, &data.img_width, &data.img_height);
    if (data->wall_ptr == NULL) {
        fprintf(stderr, "Error: Failed to load sprite image\n");
        return MLX_ERROR;
    }
	data->grass_ptr = mlx_xpm_file_to_image(data->mlx_ptr, Floor, &data.img_width, &data.img_height);
    if (data->grass_ptr == NULL) {
        fprintf(stderr, "Error: Failed to load sprite image\n");
        return MLX_ERROR;
    }
	data->player_ptr = mlx_xpm_file_to_image(data->mlx_ptr, Player, &data.img_width, &data.img_height);
    if (data->player_ptr == NULL) {
        fprintf(stderr, "Error: Failed to load sprite image\n");
        return MLX_ERROR;
    } */
	//mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

void	ft_initialize_map(t_data *data, char *file)
{
	int		fd;
	char	*buffer;
	char	*result;

	data->map_file = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		{
			printf("error opening file");
			exit (EXIT_FAILURE);
		}
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
			printf("error initializing map");
			exit (EXIT_FAILURE);
		}
	free (data->map_file);
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


/* void	ft_initialize_variables(t_data *data)
{
	
} */