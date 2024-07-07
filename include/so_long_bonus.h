/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:58:19 by dasal             #+#    #+#             */
/*   Updated: 2024/07/07 15:58:21 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <string.h>
#include "libft.h"
#include <fcntl.h>
#include <errno.h>

#define MLX_ERROR 1
#define SPRITE_SIZE 32
#define FLOOR "./textures/floortile.xpm"
#define WALL "./textures/wall.xpm"
#define COLLECTIBLE "./textures/globe.xpm"
#define EXIT_OPEN "./textures/port1.xpm"
#define EXIT_CLOSED "./textures/closed.xpm"
#define PLAYER_BACK "./textures/guy_back.xpm"
#define PLAYER_FRONT "./textures/guy_front.xpm"
#define PLAYER_LEFT "./textures/guy_left.xpm"
#define PLAYER_RIGHT "./textures/guy_right.xpm"
#define EXIT_OPEN_2 "./textures/port2.xpm"
#define EXIT_OPEN_3 "./textures/port3.xpm"
#define ENEMY "./textures/trans_char.xpm"
#define UP 13
#define LEFT 2
#define DOWN 1
#define RIGHT 2

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*wall_ptr;
	void	*floor_ptr;
	void	*player_front_ptr;
	void	*player_back_ptr;
	void	*player_left_ptr;
	void	*player_right_ptr;
	void	*collectible_ptr;
	void	*open_exit_ptr;
	void	*open_2_exit_ptr;
	void	*open_3_exit_ptr;
	void	*closed_exit_ptr;
	void	*enemy_ptr;
	char	**map;
	char	**map_copy;
	char	*map_file;
	char	*buffer;
	int		player_x;
	int		player_y;
	int		enemy_x;
	int		enemy_y;
	int		player_direction;
	int		win_width;
	int		win_height;
	int		img_width;
	int		img_height;
	int		moves;
	int		to_collect;
	int		collectible_count;
	int		animation_count;
	int		exit_count;
	int		player_count;
	int		enemy_count;
}	t_data;

//      errors
void	ft_error_exit(char *message);
void	ft_free_map(char **map);
void	ft_error_free_map_exit(t_data *data, char *message);
void	ft_error_free_all_exit(t_data *data, char *message);
int		ft_close_game(t_data *data);
//      hooks
void	ft_create_hooks(t_data *data);
int		ft_handle_keypress(int keysym, t_data *data);
void	ft_check_collision(t_data *data, int y, int x, int direction);
//      loading
int		ft_initialize_mlx(t_data *data);
void	ft_file_to_image(t_data *data);
void	ft_player_to_image(t_data *data);
void	ft_destroy_images(t_data *data);
//      parsing
void	ft_parse_map(t_data *data, char *map_file);
int		ft_check_walls(t_data *data);
void	ft_find_player(t_data *data);
int		ft_check_file_format(char *str);
int		ft_flood_fill(t_data *data, int y, int x);
//      rendering
int		ft_render_map(t_data *data);
void	ft_render_background(t_data *data);
void	ft_render_sprite(t_data *data, int x, int y);
void	ft_render_player(t_data *data);
//      utils
char	*ft_strappend(char *s1, char *s2);
int		ft_check_empty_line(char *str);
void	ft_check_invalid_char(t_data *data);
int		ft_abs(int n);
//      bonus
int		ft_render_animation(t_data *data);
void	ft_animation_to_image(t_data *data);
int		ft_enemy(t_data *data);
void	ft_render_open_door(t_data *data, int x, int y);