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

# include "pixel.h"
# include "compass.h"
# include "render_windows.h"
# include "xiaolin_wu.h"
# include "liang_barsky.h"

# define P_MY_PI 3.14159f

/*
 diagonal of a 90º triangle with sides 1 by 1
 by pitagoras 1^2 + 1^2 = diag^2 so diag = sqrt(2)
 div by 2 heps in getting sine and cosine at +45/-45/+135/-135 angles all
based on one single sin/cos calculation
used on defining character movement
*/
# define P_SQRT_OF_TWO_OVER_TWO 0.7071067f

typedef struct s_player
{
    t_pixel st_centre;
    t_pixel st_left;
    t_pixel st_right;
    t_pixel st_front;
    t_pixel centre;
    t_pixel left;
    t_pixel right;
    t_pixel front;
    float   angle;
    float   cos_rad;
    float   sin_rad;
    float   total_x_diff;
    float   total_y_diff;
    int     pix_radius;
    int     move_sense;
}   t_player;

void    setup_player(t_player *player, t_pixel centre, int radius, float rad_angle);
void    render_player(t_win_glfw *win, t_player *player);
void    move_player(t_player *player, bool w, bool s, bool a, bool d);
void    rotate_player(t_player *player, float new_rad_angle);

#endif