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


	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;

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


void bersenham_min_max(t_square *sqr, t_pixel start, t_pixel end)
{
	int x1;
	int x2;
	int y1;
	int y2;

	x1 = start.x;
	y1 = start.y;
	x2 = end.x;
	y2 = end.y;


	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;

	int err = dx - dy;

	while (1)
	{
		//printf("y: %d, matrix: min at %d (%d), max at %d (%d)", y1, y1 - sqr->min_y, sqr->min_max[y1 - sqr->min_y],  y1 + sqr->real_z - sqr->min_y, sqr->min_max[y1 + sqr->real_z - sqr->min_y]);
		sqr->min_max[y1 - sqr->min_y] -= (sqr->min_max[y1 - sqr->min_y] - x1) * (x1 < sqr->min_max[y1 - sqr->min_y]);
		sqr->min_max[y1 + sqr->real_z - sqr->min_y] += (x1 - sqr->min_max[y1 + sqr->real_z - sqr->min_y]) * (x1 > sqr->min_max[y1 + sqr->real_z - sqr->min_y]);
		//printf(" now: min at %d (%d), max at %d (%d)\n", y1 - sqr->min_y, sqr->min_max[y1 - sqr->min_y],  y1 + sqr->real_z - sqr->min_y, sqr->min_max[y1 + sqr->real_z - sqr->min_y]);
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


void	calculate_min_max(t_square *sqr)
{
	int i;
	
	sqr->max_y = sqr->edges[SQR_BOT_LEFT].y;
	sqr->min_y = sqr->edges[SQR_BOT_LEFT].y;
	sqr->max_y += (sqr->edges[SQR_TOP_LEFT].y - sqr->max_y) * (sqr->edges[SQR_TOP_LEFT].y > sqr->max_y);
	sqr->max_y += (sqr->edges[SQR_TOP_RIGHT].y - sqr->max_y) * (sqr->edges[SQR_TOP_RIGHT].y > sqr->max_y);
	sqr->max_y += (sqr->edges[SQR_BOT_RIGHT].y - sqr->max_y) * (sqr->edges[SQR_BOT_RIGHT].y > sqr->max_y);
	sqr->min_y -= (sqr->min_y - sqr->edges[SQR_TOP_LEFT].y) * (sqr->edges[SQR_TOP_LEFT].y < sqr->min_y);
	sqr->min_y -= (sqr->min_y - sqr->edges[SQR_TOP_RIGHT].y) * (sqr->edges[SQR_TOP_RIGHT].y < sqr->min_y);
	sqr->min_y -= (sqr->min_y - sqr->edges[SQR_BOT_RIGHT].y) * (sqr->edges[SQR_BOT_RIGHT].y < sqr->min_y);
	sqr->real_z = sqr->max_y - sqr->min_y + 1;
	//printf("min y, %d, max y  %d, real z %d\n", sqr->min_y, sqr->max_y, sqr->real_z);
	i = 0;
	while (i < sqr->real_z)
		sqr->min_max[i++] = INT_MAX;
	while (i < sqr->real_z * 2)
		sqr->min_max[i++] = INT_MIN;
	//i = 0;
	//while (i < sqr->real_z)
	//{
	//	printf("%d min %d max %d\n", i + sqr->min_y, sqr->min_max[i], sqr->min_max[i + sqr->real_z]);
	//	i++;
	//}
	//printf("checking line (%d, %d) to (%d, %d)\n", sqr->edge1.x, sqr->edge1.y, sqr->edge2.x, sqr->edge2.y);


	bersenham_min_max(sqr, sqr->edges[SQR_BOT_LEFT], sqr->edges[SQR_TOP_LEFT]);
	bersenham_min_max(sqr, sqr->edges[SQR_TOP_LEFT], sqr->edges[SQR_TOP_RIGHT]);
	bersenham_min_max(sqr, sqr->edges[SQR_TOP_RIGHT], sqr->edges[SQR_BOT_RIGHT]);
	bersenham_min_max(sqr, sqr->edges[SQR_BOT_RIGHT], sqr->edges[SQR_BOT_LEFT]);
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

	sqr->edges[SQR_BOT_LEFT] = (t_pixel){- sqr->width / 2, - sqr->width / 2, sqr->color};
	sqr->edges[SQR_TOP_LEFT] = (t_pixel){- sqr->width / 2, + sqr->width / 2, sqr->color};
	sqr->edges[SQR_TOP_RIGHT] = (t_pixel){+ sqr->width / 2, + sqr->width / 2, sqr->color};
	sqr->edges[SQR_BOT_RIGHT] = (t_pixel){+ sqr->width / 2, - sqr->width / 2, sqr->color};
	i = 0;
	while (i < SQR_SIZE)
	{
		rotate_point(&sqr->edges[i], sqr->centre, comp->cos_rad, comp->sin_rad);
		i++;
	}
	//printf("pre-min_max\n");
	calculate_min_max(sqr);
	//printf("pos-min_max\n");
}

void	init_template_square(t_compass *comp)
{
	t_square	*sqr;

	sqr = &comp->sqr;
	sqr->width = 40;  //comp->sqr_width
	sqr->centre = (t_pixel){0, 0, comp->sqr_color};
	sqr->color = comp->sqr_color;
	sqr->biggest_z = 1 + sqrt(sqr->width * sqr->width * 2);
	sqr->min_max = malloc(sizeof(*sqr->min_max) * sqr->biggest_z * 2);
	if (!sqr->min_max)
		return ;
	
	rotate_template_square(comp, sqr);
	
}


void	render_new_square(t_win_glfw *win, t_compass *comp, t_pixel centre)
{
	t_pixel	edges[SQR_SIZE];
	int i;
	int x;
	int y;

	ft_memcpy(edges, comp->sqr.edges, sizeof(*edges) * SQR_SIZE);
	//printf("memcpyied edges for rendering\n");
	x = centre.x + comp->map_centre.x;
	y = centre.y + comp->map_centre.y;
	i = 0;
	while (i < SQR_SIZE)
	{
		translate_point(&edges[i], x, y);
		i++;
	}
	//printf("translated edges\n");
	i = 1;
	while (i < comp->sqr.real_z - 1)
	{
		draw_horizontal_line(win, comp->sqr.min_max[i] + 1 + x, comp->sqr.min_max[i + comp->sqr.real_z] - 1 + x, i + comp->sqr.min_y + y, comp->sqr.color);
		i++;
	}
	//printf("rendered horizontal lines\n");
	xiaolinwu_line(win, edges[SQR_BOT_LEFT], edges[SQR_TOP_LEFT]);
	xiaolinwu_line(win, edges[SQR_TOP_LEFT], edges[SQR_TOP_RIGHT]);
	xiaolinwu_line(win, edges[SQR_TOP_RIGHT], edges[SQR_BOT_RIGHT]);
	xiaolinwu_line(win, edges[SQR_BOT_RIGHT], edges[SQR_BOT_LEFT]);	
}