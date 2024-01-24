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

/*
void    render_player(t_win_glfw *win, t_player *player)
{
	t_pixel render[2];
	t_pixel low_bot;
	t_pixel hi_top;

	low_bot = (t_pixel){0, 0, ARGB(255,255,255,255)};
	hi_top = (t_pixel){win->width, win->height, ARGB(255,255,255,255)};
	if (liang_barsky_clipper(low_bot, hi_top, player->centre, player->left, render))
		xiaolinwu_line(win, render[0], render[1]);
	if (liang_barsky_clipper(low_bot, hi_top, player->centre, player->right, render))
		xiaolinwu_line(win, render[0], render[1]);
	if (liang_barsky_clipper(low_bot, hi_top, player->centre, player->front, render))
		xiaolinwu_line(win, render[0], render[1]);
}
*/

void    setup_player(t_player *player, float unit_size, float rad_angle)
{

	player->move_sense = 0.01f;
	player->unit_size = unit_size;
	player->angle = rad_angle;
	player->cos_rad = cosf(player->angle);
	player->sin_rad = sinf(player->angle);
}
