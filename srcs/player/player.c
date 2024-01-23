/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:23:32 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 19:23:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "player.h"


void    render_player(t_win_glfw *win, t_player *player)
{
	t_pixel render[2];
	t_pixel low_bot;
	t_pixel hi_top;

	low_bot = (t_pixel){0, 0, ARGB(255,255,255,255)};
	hi_top = (t_pixel){WIN_WIDTH, WIN_HEIGHT, ARGB(255,255,255,255)};
	if (liang_barsky_clipper(low_bot, hi_top, player->centre, player->left, render))
		xiaolinwu_line(win, render[0], render[1]);
	if (liang_barsky_clipper(low_bot, hi_top, player->centre, player->right, render))
		xiaolinwu_line(win, render[0], render[1]);
	if (liang_barsky_clipper(low_bot, hi_top, player->centre, player->front, render))
		xiaolinwu_line(win, render[0], render[1]);
}


void    setup_player(t_player *player, t_pixel centre, int radius, float rad_angle)
{
	float cos_ray;
	float sin_ray;

	player->move_sense = 5;
	player->pix_radius = radius;
	player->st_centre = centre;
	player->st_left = centre;
	player->st_right = centre;
	player->st_front = centre;
	player->st_left.x += radius;
	player->st_right.x += radius;
	player->st_front.x += radius;
	player->angle = rad_angle;
	player->cos_rad = cosf(player->angle);
	player->sin_rad = sinf(player->angle);
	player->centre = player->st_centre;
	player->left = player->st_left;
	player->right = player->st_right;
	player->front = player->st_front;
	player->total_x_diff = 0;
	player->total_y_diff = 0;
	cos_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //cos (angle + PI / 4)
	sin_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //sin (angle + PI / 4)
	rotate_point(&player->right, player->centre, cos_ray, sin_ray);
	cos_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //cos (angle - PI / 4)
	sin_ray = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;  //sin (angle - PI / 4)
	rotate_point(&player->left, player->centre, cos_ray, sin_ray);
	rotate_point(&player->front, player->centre, player->cos_rad, player->sin_rad);
}
