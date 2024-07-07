/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:26:47 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 15:26:49 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_parse_map(t_data *data, char *map_file);
int		ft_check_walls(t_data *data);
void	ft_find_player(t_data *data);
int		ft_check_file_format(char *str);
int		ft_flood_fill(t_data *data, int y, int x);

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
			x++;
		}
		y++;
	}
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

int	ft_flood_fill(t_data *data, int y, int x)
{
	if (data->map_copy[y][x] == '1' || data->map_copy[y][x] == 'v')
		return (1);
	if (data->map_copy[y][x] == 'E')
		data->exit_count++;
	if (data->map_copy[y][x] == 'C')
		data->to_collect++;
	if (data->map_copy[y][x] == 'M')
	{
		data->enemy_count++;
		data->enemy_x = x;
		data->enemy_y = y;
	}
	data->map_copy[y][x] = 'v';
	ft_flood_fill(data, y + 1, x);
	ft_flood_fill(data, y - 1, x);
	ft_flood_fill(data, y, x + 1);
	ft_flood_fill(data, y, x - 1);
	return (1);
}
