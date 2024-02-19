/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:29:32 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:29:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"



void	render_new_square(t_win *win, t_compass *comp, t_pixel centre)
{
	int i;
	int x;
	int y;
	t_square sqr;

	sqr = comp->sqr;
	x = centre.x + comp->map_centre.x;
	y = centre.y + comp->map_centre.y;
	i = 0;
	while (i < SQR_SIZE)
	{
		translate_point(&sqr.edges[i], x, y);
		i++;
	}
	i = 1;
	while (i < sqr.real_z - 1)
	{
		draw_horizontal_line(win, comp->sqr_x_lim[i].min + 1 + x, comp->sqr_x_lim[i].max - 1 + x, i + sqr.min_max[MM_MIN_Y] + y, comp->sqr.color);
		i++;
	}
	xiaolinwu_line(win, sqr.edges[SQR_BOT_LEFT], sqr.edges[SQR_TOP_LEFT]);
	xiaolinwu_line(win, sqr.edges[SQR_TOP_LEFT], sqr.edges[SQR_TOP_RIGHT]);
	xiaolinwu_line(win, sqr.edges[SQR_TOP_RIGHT], sqr.edges[SQR_BOT_RIGHT]);
	xiaolinwu_line(win, sqr.edges[SQR_BOT_RIGHT], sqr.edges[SQR_BOT_LEFT]);	
}
