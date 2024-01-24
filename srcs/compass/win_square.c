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
	//i = 0;
	//while (i < sqr->real_z)
	//{
	//	printf("%d min %d max %d\n", i + sqr->min_y, sqr->min_max[i], sqr->min_max[i + sqr->real_z]);
	//	i++;
	//}
	//printf("checking line (%d, %d) to (%d, %d)\n", sqr->edge1.x, sqr->edge1.y, sqr->edge2.x, sqr->edge2.y);
	

	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_BOT_LEFT], sqr->edges[SQR_TOP_LEFT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_TOP_LEFT], sqr->edges[SQR_TOP_RIGHT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_TOP_RIGHT], sqr->edges[SQR_BOT_RIGHT]);
	bersenham_sqr_x_lim(comp, sqr, sqr->edges[SQR_BOT_RIGHT], sqr->edges[SQR_BOT_LEFT]);
	//i = 0;
	//while (i < sqr->real_z)
	//{
	//	printf("%d min %d max %d\n", i + sqr->min_y, sqr->min_max[i], sqr->min_max[i + sqr->real_z]);
	//	//printf("index %d, value %d\n", i, sqr->min_max[i]);
	//	i++;
	//}
	//	
	
}


void	rotate_template_square(t_compass *comp, t_square *sqr)
{
	int	i;

	sqr->edges[SQR_BOT_LEFT] = (t_pixel){- sqr->height / 2, - sqr->height / 2, sqr->color};
	sqr->edges[SQR_TOP_LEFT] = (t_pixel){- sqr->height / 2, + sqr->height / 2, sqr->color};
	sqr->edges[SQR_TOP_RIGHT] = (t_pixel){+ sqr->height / 2, + sqr->height / 2, sqr->color};
	sqr->edges[SQR_BOT_RIGHT] = (t_pixel){+ sqr->height / 2, - sqr->height / 2, sqr->color};
	i = 0;
	while (i < SQR_SIZE)
	{
		rotate_point(&sqr->edges[i], sqr->centre, comp->cos_rad, comp->sin_rad);
		i++;
	}
	//printf("pre-min_max\n");
	calculate_sqr_x_lim(comp, sqr);
	//printf("pos-min_max\n");
}

void	init_template_square(t_compass *comp)
{
	t_square	*sqr;

	sqr = &comp->sqr;
	sqr->height = comp->sqr_height;
	sqr->centre = (t_pixel){0, 0, comp->sqr_color};
	sqr->color = comp->sqr_color;
	sqr->biggest_z = 1 + sqrt(SQR_MAX_HEIGHT * SQR_MAX_HEIGHT * 2);
	comp->sqr_x_lim = malloc(sizeof(*comp->sqr_x_lim) * sqr->biggest_z);
	if (!comp->sqr_x_lim)
		return ;	
	rotate_template_square(comp, sqr);
	
}


void	render_new_square(t_win_glfw *win, t_compass *comp, t_pixel centre)
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
	//printf("translated edges\n");
	i = 1;
	while (i < sqr.real_z - 1)
	{
		draw_horizontal_line(win, comp->sqr_x_lim[i].min + 1 + x, comp->sqr_x_lim[i].max - 1 + x, i + sqr.min_max[MM_MIN_Y] + y, comp->sqr.color);
		i++;
	}
	//printf("rendered horizontal lines\n");
	xiaolinwu_line(win, sqr.edges[SQR_BOT_LEFT], sqr.edges[SQR_TOP_LEFT]);
	xiaolinwu_line(win, sqr.edges[SQR_TOP_LEFT], sqr.edges[SQR_TOP_RIGHT]);
	xiaolinwu_line(win, sqr.edges[SQR_TOP_RIGHT], sqr.edges[SQR_BOT_RIGHT]);
	xiaolinwu_line(win, sqr.edges[SQR_BOT_RIGHT], sqr.edges[SQR_BOT_LEFT]);	
}


void	render_inner_square(t_win_glfw *win, t_compass *comp, t_pixel centre)
{
	int 		i;
	int 		x;
	int 		y;
	t_square	sqr;
	int			c_min_max[MM_SIZE];

	sqr = comp->sqr;
	ft_memcpy(&c_min_max, &comp->inner.min_max, sizeof(c_min_max));
	x = centre.x + comp->map_centre.x;											//relativos ao centro do compasso
	y = centre.y + comp->map_centre.y;											//relativos ao centro do compasso
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
	//while ( i < MM_SIZE)
	//{
	//	printf("sqr %d, circle %d\n", sqr.min_max[i], c_min_max[i]);
	//	i++;
	//}

	if (sqr.min_max[MM_MIN_X] > c_min_max[MM_MAX_X] ||
		sqr.min_max[MM_MAX_X] < c_min_max[MM_MIN_X] ||
		sqr.min_max[MM_MIN_Y] > c_min_max[MM_MAX_Y] ||
		sqr.min_max[MM_MAX_Y] < c_min_max[MM_MIN_Y])
		return ;

	

	//printf("translated edges\n");

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

	//printf("rendered horizontal lines\n");
	
	//xiaolinwu_line(win, sqr.edges[SQR_BOT_LEFT], sqr.edges[SQR_TOP_LEFT]);
	//xiaolinwu_line(win, sqr.edges[SQR_TOP_LEFT], sqr.edges[SQR_TOP_RIGHT]);
	//xiaolinwu_line(win, sqr.edges[SQR_TOP_RIGHT], sqr.edges[SQR_BOT_RIGHT]);
	//xiaolinwu_line(win, sqr.edges[SQR_BOT_RIGHT], sqr.edges[SQR_BOT_LEFT]);	
}

void	xlim_square_vs_rectangle(t_win_glfw *win, t_compass *comp, t_pixel centre, t_pixel low_bot, t_pixel hi_top)
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

	//i = 0;
	//while (i < SQR_SIZE)
	//{
	//	printf("%d ", sqr.min_max[i]);
	//	i++;
	//}
	//printf("\n");
	i = 0;

	if (sqr.min_max[MM_MIN_X] > hi_top.x ||
		sqr.min_max[MM_MAX_X] < low_bot.x ||
		sqr.min_max[MM_MIN_Y] > hi_top.y ||
		sqr.min_max[MM_MAX_Y] < low_bot.y)
		return ;

	i = ft_max(low_bot.y - sqr.min_max[MM_MIN_Y], 0);
	int end = ft_max(sqr.min_max[MM_MAX_Y] - hi_top.y, 0);

	//printf("index start %d, index end %d, sqr real.z %d\n", i, end, sqr.real_z);
	while (i < sqr.real_z - end)
	{
		int start = ft_max(comp->sqr_x_lim[i].min + x, low_bot.x);
		int end_line = ft_min(comp->sqr_x_lim[i].max + x, hi_top.x);
		//printf("index %d, end %d, start x %d, end x %d, y %d\n", i, end, start, end_line, i + sqr.min_max[MM_MIN_Y]);
		draw_horizontal_line(win, start , end_line, i + sqr.min_max[MM_MIN_Y], comp->sqr.color);
		i++;
	}
}