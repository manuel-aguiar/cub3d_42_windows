/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:45:11 by marvin            #+#    #+#             */
/*   Updated: 2024/01/11 14:45:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

# include "libft.h"
# include "compass.h"
# include "liang_barsky.h"
# include "xiaolin_wu.h"
# include "parsing.h"
# include "render_windows.h"
# include "pixel.h"
# include "player.h"

typedef struct s_game
{
	t_parsing	parsing;
	t_map		map;
	t_compass	compass;
	t_win_glfw	win;
	t_player	player;
	t_posi		player_position;
	float		player_angle_rad;
}	t_game;


int		game_start(t_game *game, char *game_config);
void	free_game(t_game *game);

//game_key_funcs.c
void	game_rotate_view_angle(t_game *game, float diff);

//game_render.c
void	game_render(t_game *game);

float	radian_truncate(float radian);

int		win_render(t_game *game, t_win_glfw *win, void (*win_key_press)());

//player....
void    move_player(t_game *game, bool w, bool s, bool a, bool d);
void	handle_collisions(t_game *game);

#endif