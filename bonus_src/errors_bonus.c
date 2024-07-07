/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:26:22 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 15:26:24 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_error_exit(char *message);
void	ft_free_map(char **map);
void	ft_error_free_map_exit(t_data *data, char *message);
void	ft_error_free_all_exit(t_data *data, char *message);
int		ft_close_game(t_data *data);

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
	mlx_destroy_display(data->mlx_ptr);
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
	mlx_destroy_display(data->mlx_ptr);
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
