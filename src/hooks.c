/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:28:24 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 14:28:26 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_create_hooks(t_data *data);
int		ft_handle_keypress(int keysym, t_data *data);
void	ft_check_collision(t_data *data, int y, int x, int direction);

void	ft_create_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, DestroyNotify, \
	ButtonPressMask, ft_close_game, data);
	mlx_hook(data->win_ptr, Expose, ExposureMask, ft_render_map, data);
	ft_render_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, \
	ft_handle_keypress, data);
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
	if (data->map[data->player_y][data->player_x] == 'E' && \
	data->collectible_count == 0)
		ft_error_free_all_exit(data, "You won!\n");
	ft_render_map(data);
	return (0);
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
