/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:26:35 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 15:26:39 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int		ft_initialize_mlx(t_data *data);
void	ft_file_to_image(t_data *data);
void	ft_player_to_image(t_data *data);
void	ft_destroy_images(t_data *data);

int	ft_initialize_mlx(t_data *data)
{
	if (data->enemy_count != 1)
		ft_error_free_map_exit(data, "Error\nwrong enemy count\n");
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

void	ft_file_to_image(t_data *data)
{
	ft_animation_to_image(data);
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
	data->enemy_ptr = mlx_xpm_file_to_image(data->mlx_ptr, \
	ENEMY, &data->img_width, &data->img_height);
	if (data->enemy_ptr == NULL)
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
	if (data->open_2_exit_ptr)
		mlx_destroy_image(data->mlx_ptr, data->open_2_exit_ptr);
	if (data->open_3_exit_ptr)
		mlx_destroy_image(data->mlx_ptr, data->open_3_exit_ptr);
	if (data->enemy_ptr)
		mlx_destroy_image(data->mlx_ptr, data->enemy_ptr);
}
