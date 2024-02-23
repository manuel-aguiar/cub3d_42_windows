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

# include <float.h>

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
# include "xpm_parser.h"
# include "sprites.h"


typedef struct s_hud
{
	t_pixel bar_bot_left;
	t_pixel bar_top_left;

}	t_hud;

typedef struct s_dda_hor
{
	int 	min_y;
	int 	max_y;
	int		side;
	float 	wall_dist;
	int		line_h;
}	t_dda_hor;

typedef struct s_dda_ver
{
	float row_distance;
}	t_dda_ver;

typedef struct t_wall_line
{
	int			line_start;
	int			line_end;
	float		x_hit;
	int			tex_pix_x;
	int			tex_pix_y;
	float		step;
	float		tex_exact_y_save;
	float		tex_exact_y;
	int			y_start;
	int			y_end;
	int			color;
	float		shade_wgt;
	t_xpm_tex 	*tex;
}	t_wall_line;

typedef struct s_ray
{
	int			w;
	int			h;
	float 		cam_x;
	t_vector	dir_vec;
	t_vector	plane;
	t_vector	player_sqr;
	t_vector	start;
	t_vector	first;
	t_vector	step;
	t_vector	axis_move;
	t_vector	ray_dir;
	int			side;
	int			pitch_mod;
	float		z_mod;
	int			hgt_mod;
}	t_ray;

typedef struct s_game
{
	t_parsing	parsing;
	t_map		map;
	t_compass	compass;
	t_win		win;
	t_player	player;
	t_mouse		*mouse;			//pointers because GLFW requires globals, change to stack with MLX;
	int			*keys;			//pointers because GLFW requires globals, change to stack with MLX;
	int			*key_defs;
	t_dda_hor	*hori_rays;
	t_dda_ver	*verti_rays;
	int			maxmin_hori;
	int			minmax_hori;
	float		max_vis_dist;
	float		wall_reflection;
	t_xpm_tex	*tex[NUM_TEX];
	t_sprite	*sprites;
	int			sprite_count;
	float		floating;
	float		float_sense;
	float		float_sin;
	t_door		template_door;
	t_medi		template_medi;
	t_ammo		template_ammo;
	t_exit		template_exit;
	t_enemy		template_enemy;
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

void	game_actions(t_game *game);


int		win_render(t_game *game, t_win *win, void (*win_key_press)());

//player....
void	handle_collisions(t_game *game, t_vector potencial);

void	render_map_outside_compass(t_game *game);
void	render_player_outside_compass(t_game *game);

//
void	render_map_inside_compass(t_game *game);
void	render_player_inside_compass(t_game *game);

// game_key_manager.c
void	game_key_manager(t_game *game);

//game_manager_mouse.c
void	game_mouse_manager(t_game *game);

void	floorcast(t_game *game);

void	raycasting_horizontal(t_game *game);

void	xpm_to_window(t_win *win, t_xpm_tex *tex, t_pixel corner, int pixel_wid, int pixel_hgt);
void	xpm_tex_translate(t_xpm_tex *tex);

void	player_actions(t_game *game);
void	player_rotate_and_pitch(t_game *game);

void    move_player(t_game *game, int keys);

//shader.c
int		add_shade(int color, float perc);
void	hori_raycasting(t_game *game);

void	sprite_cast(t_game *game);
void	doorcast(t_game *game, t_sprite *sprite);

void	floorcast(t_game *game);
void	wallcast(t_game *game, t_ray *ray, t_dda_hor *hori, int x);

//super_debug_print.c
void	super_debug_print(t_game *game);

//sprites
int		setup_sprites(t_game *game);
void	sprite_calc_dist(t_game *game);


void	render_stats_bars(t_game *game);


#endif