/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:24:28 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 19:24:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H

# define PLAYER_H

# include "vector.h"
# include "compass.h"
# include "render_windows.h"
# include "drawing_algos.h"
# include "pixel_point.h"

# define P_MY_PI 3.14159265f

/*
 diagonal of a 90º triangle with sides 1 by 1
 by pitagoras 1^2 + 1^2 = diag^2 so diag = sqrt(2)
 div by 2 heps in getting sine and cosine at +45/-45/+135/-135 angles all
based on one single sin/cos calculation
used on defining character movement
*/
# define P_SQRT_OF_TWO_OVER_TWO 0.7071067f

enum e_clocks
{
	CLOCK_MOVE,
	CLOCK_AIM,
	CLOCK_JUMP,
	CLOCK_CROUCH,
	CLOCK_SIZE,
};


typedef struct s_player
{
	t_vector		map_posi;
	t_vector		dir_vec;
	t_vector		plane;
	int				pitch;
	int				z_height;
	float			angle;
	float			cos_rad;
	float			sin_rad;
	float			unit_size;
	float			forward_move;
	float			side_move;
	float			back_move;
	float			max_aim_radius;
	float			cur_dir_len;
	float			base_dir_len;
	float			aim_dir_len;
	float			cur_fov;
	float			base_fov;
	float			aim_fov;
	bool			is_aiming;
	float			aim_sense;
	float			rot_sense;
	float			pitch_sense;
	bool			is_jumping;
	t_clock 		timer[CLOCK_SIZE];
}   t_player;


void    player_setup(t_player *player);
void	render_player(t_win_glfw *win, t_player *player);


void	player_change_aim(t_player *player);
void 	player_jump_cur_z(t_player *player);
void	player_get_timer(t_player *player, int timer);

#endif