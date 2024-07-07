/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dominicasal <dominicasal@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:52:13 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 00:43:23 by dominicasal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_create_map(t_data *data, int fd);
void	ft_initialize_variables(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac == 2)
	{
		ft_initialize_variables(&data);
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			ft_error_exit("Error\nerror opening file\n");
		ft_create_map(&data, fd);
		ft_parse_map(&data, av[1]);
		ft_initialize_mlx(&data);
		ft_create_hooks(&data);
		mlx_loop(data.mlx_ptr);
	}
	else
		write(2, "Error\nmap file missing\n", 23);
	return (0);
}

void	ft_initialize_variables(t_data *data)
{
	data->moves = 0;
	data->collectible_count = 0;
	data->player_direction = 1;
	data->map_file = NULL;
	data->animation_count = 0;
	data->enemy_count = 0;
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
	data->open_2_exit_ptr = NULL;
	data->open_3_exit_ptr = NULL;
	data->enemy_ptr = NULL;
}

void	ft_create_map(t_data *data, int fd)
{
	char	*buffer;

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
