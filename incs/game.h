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
# include "pixel_point.h"
# include "compass.h"
# include "drawing_algos.h"
# include "parsing.h"
# include "render_windows.h"
# include "vector.h"
# include "player.h"
# include "generic_utils.h"
# include "user_inputs.h"

typedef struct s_dda_hor
{
	int min_x;
	int max_x;
}	t_dda_hor;

typedef struct s_game
{
	t_parsing	parsing;
	t_map		map;
	t_compass	compass;
	t_win_glfw	win;
	t_player	player;
	t_mouse		*mouse;			//pointers because GLFW requires globals, change to stack with MLX;
	int			*keys;			//pointers because GLFW requires globals, change to stack with MLX;
	int			*key_defs;
	t_dda_hor	*hori_rays;
}	t_game;

//settings.c
void    apply_all_settings(t_game *game);

//game_setup.c
int		game_start(t_game *game, char *game_config);
void	free_game(t_game *game);
void	setup_all_angles(t_game *game, float rad);
void	game_setup_keys(t_game *game);

//game_key_funcs.c
void	game_rotate_view_angle(t_game *game, float diff);

//game_render.c
void	game_render(t_game *game);

float	radian_truncate(float radian);

int		win_render(t_game *game, t_win_glfw *win, void (*win_key_press)());

//player....
void    move_player(t_game *game, bool w, bool s, bool a, bool d);
void	handle_collisions(t_game *game);

void	render_map_outside_compass(t_game *game);
void	render_player_outside_compass(t_game *game);

//
void	render_map_inside_compass(t_game *game);
void	render_player_inside_compass(t_game *game);

// game_key_manager.c
void	game_key_manager(t_game *game);

//game_manager_mouse.c
void	game_mouse_manager(t_game *game);


void	raycasting_horizontal(t_game *game);


#endif