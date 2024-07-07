/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:27:51 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 14:27:53 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		ft_render_map(t_data *data);
void	ft_render_background(t_data *data);
void	ft_render_sprite(t_data *data, int x, int y);
void	ft_render_player(t_data *data);

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
