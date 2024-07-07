/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:38:30 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 15:38:59 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int		ft_render_animation(t_data *data);
void	ft_animation_to_image(t_data *data);
int		ft_enemy(t_data *data);

int	ft_render_animation(t_data *data)
{
	if (data->animation_count % 20 == 0)
		ft_render_map(data);
	if (data->animation_count == 20)
		ft_enemy(data);
	if (data->animation_count == 10000)
		data->animation_count = 0;
	data->animation_count++;
	if ((data->enemy_x == data->player_x) && (data->enemy_y == data->player_y))
		ft_error_free_all_exit(data, "You lost!");
	return (0);
}

void	ft_animation_to_image(t_data *data)
{
	data->open_2_exit_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	EXIT_OPEN_2, &data->img_width, &data->img_height);
	data->open_3_exit_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	EXIT_OPEN_3, &data->img_width, &data->img_height);
}

int	ft_enemy(t_data *data)
{
	int	delta_y;
	int	delta_x;
	int	to_move;

	delta_x = data->player_x - data->enemy_x;
	delta_y = data->player_y - data->enemy_y;
	if (ft_abs(delta_y) > ft_abs(delta_x))
	{
		to_move = delta_y / ft_abs(delta_y);
		if (data->map[data->enemy_y + to_move][data->enemy_x] != '1')
			data->enemy_y += to_move;
	}
	else
	{
		to_move = delta_x / ft_abs(delta_x);
		if (data->map[data->enemy_y][data->enemy_x + to_move] != '1')
			data->enemy_x += to_move;
	}
	return (0);
}
