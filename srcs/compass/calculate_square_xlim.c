/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_square.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:12:39 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 16:12:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void bersenham_line(t_win_glfw *win, t_pixel start, t_pixel end, int color)
{
	int x1;
	int x2;
	int y1;
	int y2;

	x1 = start.x;
	y1 = start.y;
	x2 = end.x;
	y2 = end.y;


	int dx = ft_abs(x2 - x1);
	int dy = ft_abs(y2 - y1);
	int sx = ft_ternary(x1 < x2, 1, -1);
	int sy = ft_ternary(y1 < y2, 1, -1);

	int err = dx - dy;

	while (1)
	{
		win->set_pixel(win, x1, y1, color);

		if (x1 == x2 && y1 == y2)
			break;

		int e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}


void bersenham_sqr_x_lim(t_compass *comp, t_square *sqr, t_pixel start, t_pixel end)
{
	int x1;
	int x2;
	int y1;
	int y2;

	x1 = start.x;
	y1 = start.y;
	x2 = end.x;
	y2 = end.y;


	int dx = ft_abs(x2 - x1);
	int dy = ft_abs(y2 - y1);
	int sx = ft_ternary(x1 < x2, 1, -1);
	int sy = ft_ternary(y1 < y2, 1, -1);

	int err = dx - dy;

	int	table_y;

	while (1)
	{
		table_y = y1 - sqr->min_max[MM_MIN_Y];
		comp->sqr_x_lim[table_y].min = ft_min(comp->sqr_x_lim[table_y].min, x1);
		comp->sqr_x_lim[table_y].max = ft_max(comp->sqr_x_lim[table_y].max, x1);
		if (x1 == x2 && y1 == y2)
			break;

		int e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}


//xiaolin wu, há que alterar algoritmo para ter em conta inside e outside
//antialiasing nao ta bom, paciencia


void	calculate_sqr_x_lim(t_compass *comp, t_square *sqr)
{
	int i;

	sqr->min_max[MM_MIN_X] = sqr->edges[0].x;
	sqr->min_max[MM_MAX_X] = sqr->edges[0].x;	
	sqr->min_max[MM_MIN_Y] = sqr->edges[0].y;
	sqr->min_max[MM_MAX_Y] = sqr->edges[0].y;
	i = 1;
	while (i < SQR_SIZE)
	{
		sqr->min_max[MM_MIN_X] = ft_min(sqr->min_max[MM_MIN_X], sqr->edges[i].x);
		sqr->min_max[MM_MAX_X] = ft_max(sqr->min_max[MM_MAX_X], sqr->edges[i].x);
		sqr->min_max[MM_MIN_Y] = ft_min(sqr->min_max[MM_MIN_Y], sqr->edges[i].y);
		sqr->min_max[MM_MAX_Y] = ft_max(sqr->min_max[MM_MAX_Y], sqr->edges[i].y);
		i++;
	}
	sqr->real_z = sqr->min_max[MM_MAX_Y] - sqr->min_max[MM_MIN_Y] + 1;
	//printf("min y, %d, max y  %d, real z %d\n", sqr->min_y, sqr->max_y, sqr->real_z);
	i = 0;
	while (i < sqr->real_z)
	{
		comp->sqr_x_lim[i].min = INT_MAX;
		comp->sqr_x_lim[i].max = INT_MIN;
		i++;
	}

	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_BOT_LEFT], sqr->edges[SQR_TOP_LEFT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_TOP_LEFT], sqr->edges[SQR_TOP_RIGHT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_TOP_RIGHT], sqr->edges[SQR_BOT_RIGHT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_BOT_RIGHT], sqr->edges[SQR_BOT_LEFT]);
	
}


void	compass_square_xlim_rotate(t_compass *comp, t_square *sqr)
{
	int	i;

	sqr->edges[SQR_BOT_LEFT] = (t_pixel){- sqr->height / 2, - sqr->height / 2, sqr->color};
	sqr->edges[SQR_TOP_LEFT] = (t_pixel){- sqr->height / 2, + sqr->height / 2, sqr->color};
	sqr->edges[SQR_TOP_RIGHT] = (t_pixel){+ sqr->height / 2, + sqr->height / 2, sqr->color};
	sqr->edges[SQR_BOT_RIGHT] = (t_pixel){+ sqr->height / 2, - sqr->height / 2, sqr->color};
	i = 0;
	while (i < SQR_SIZE)
	{
		rotate_point(&sqr->edges[i], sqr->centre, -comp->cos_rad, comp->sin_rad);
		i++;
	}
	calculate_sqr_x_lim(comp, sqr);
}

void	init_template_square(t_compass *comp)
{
	t_square	*sqr;

	sqr = &comp->sqr;
	comp->sqr_x_lim = malloc(sizeof(*comp->sqr_x_lim) * sqr->biggest_z);
	if (!comp->sqr_x_lim)
		return ;	
	compass_square_xlim_rotate(comp, sqr);
	
}

