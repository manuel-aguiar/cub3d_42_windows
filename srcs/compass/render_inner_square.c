/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_inner_square.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:30:04 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:30:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	render_square_vs_circle(t_win *win, t_compass *comp, t_pixel centre)
{
	int 		i;
	int 		x;
	int 		y;
	t_square	sqr;
	int			c_min_max[MM_SIZE];

	sqr = comp->sqr;
	ft_memcpy(&c_min_max, &comp->inner.min_max, sizeof(c_min_max));
	x = centre.x;														//relativos ao centro do compasso
	y = centre.y;														//relativos ao centro do compasso
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

	c_min_max[MM_MIN_X] += comp->centre.x;
	c_min_max[MM_MAX_X] += comp->centre.x;
	c_min_max[MM_MIN_Y] += comp->centre.y;
	c_min_max[MM_MAX_Y] += comp->centre.y;

	i = 0;
	if (sqr.min_max[MM_MIN_X] > c_min_max[MM_MAX_X] ||
		sqr.min_max[MM_MAX_X] < c_min_max[MM_MIN_X] ||
		sqr.min_max[MM_MIN_Y] > c_min_max[MM_MAX_Y] ||
		sqr.min_max[MM_MAX_Y] < c_min_max[MM_MIN_Y])
		return ;
	i = ft_max(c_min_max[MM_MIN_Y] - sqr.min_max[MM_MIN_Y], 0);
	int end = ft_max(sqr.min_max[MM_MAX_Y] - c_min_max[MM_MAX_Y], 0);
	int adj_x = sqr.min_max[MM_MIN_Y] - comp->inner.centre.y + comp->inner.radius;
	while (i < sqr.real_z - end)
	{
		int start = ft_max(comp->sqr_x_lim[i].min + x, comp->circle_x_lim[i + adj_x].min + comp->inner.centre.x);
		int end_line = ft_min(comp->sqr_x_lim[i].max + x, comp->circle_x_lim[i + adj_x].max + comp->inner.centre.x);
		
		draw_horizontal_line(win, start , end_line, i + sqr.min_max[MM_MIN_Y], comp->sqr.color);
		i++;
	}
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