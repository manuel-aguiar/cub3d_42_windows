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


void	render_square_vs_rect(t_win *win, t_compass *comp, t_pixel centre, t_pixel low_bot, t_pixel hi_top)
{
	int 		i;
	int 		x;
	int 		y;
	t_square	sqr;

	if (low_bot.x >= hi_top.x || low_bot.y >= hi_top.y)
		return ;

	sqr = comp->sqr;
	x = centre.x;
	y = centre.y;
	i = 0;
	while (i < SQR_SIZE)
	{
		translate_point(&sqr.edges[i], x, y);
		i++;
	}
	

	sqr.min_max[MM_MIN_X] += x;
	sqr.min_max[MM_MAX_X] += x;
	sqr.min_max[MM_MIN_Y] += y;
	sqr.min_max[MM_MAX_Y] += y;
	i = 0;

	if (sqr.min_max[MM_MIN_X] > hi_top.x ||
		sqr.min_max[MM_MAX_X] < low_bot.x ||
		sqr.min_max[MM_MIN_Y] > hi_top.y ||
		sqr.min_max[MM_MAX_Y] < low_bot.y)
		return ;

	i = ft_max(low_bot.y - sqr.min_max[MM_MIN_Y], 0);
	int end = ft_max(sqr.min_max[MM_MAX_Y] - hi_top.y, 0);
	while (i < sqr.real_z - end)
	{
		int start = ft_max(comp->sqr_x_lim[i].min + x, low_bot.x);
		int end_line = ft_min(comp->sqr_x_lim[i].max + x, hi_top.x);
		draw_horizontal_line(win, start , end_line, i + sqr.min_max[MM_MIN_Y], comp->sqr.color);
		i++;
	}
}
