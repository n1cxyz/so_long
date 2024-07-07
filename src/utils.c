/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:27:59 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 14:28:00 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strappend(char *s1, char *s2);
void	ft_print_moves(int n);
int		ft_check_empty_line(char *str);
void	ft_check_invalid_char(t_data *data);

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

void	ft_check_invalid_char(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			if (data->map[y][x] != '1' && data->map[y][x] != '0' && \
			data->map[y][x] != 'C' && data->map[y][x] != 'E' && \
			data->map[y][x] != 'P')
				ft_error_free_map_exit(data, "Error\nInvalid char\n");
			x++;
		}
		y++;
	}
}
