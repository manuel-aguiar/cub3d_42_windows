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

/*

void drawFilledSquare(int vertices[][2], int color) {
	int i;
	for (i = 0; i < 3; i++) {
		drawLine(vertices[i][0], vertices[i][1], vertices[i + 1][0], vertices[i + 1][1]);
	}
	drawLine(vertices[i][0], vertices[i][1], vertices[0][0], vertices[0][1]);
}
*/

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

void	init_square(t_square *sqr, t_pixel edge1, t_pixel edge2, t_pixel edge3, t_pixel edge4)
{
	sqr->edge1 = edge1;
	sqr->edge2 = edge2;
	sqr->edge3 = edge3;
	sqr->edge4 = edge4;
}

void    translate_square(t_square *sqr, int dx, int dy)
{
	sqr->centre.x += dx;
	sqr->centre.y += dy;
	sqr->edge1.x += dx;
	sqr->edge1.y += dy;
	sqr->edge2.x += dx;
	sqr->edge2.y += dy;
	sqr->edge3.x += dx;
	sqr->edge3.y += dy;
	sqr->edge4.x += dx;
	sqr->edge4.y += dy;
	sqr->og_edge1.x += dx;
	sqr->og_edge1.y += dy;
	sqr->og_edge2.x += dx;
	sqr->og_edge2.y += dy;
	sqr->og_edge3.x += dx;
	sqr->og_edge3.y += dy;
	sqr->og_edge4.x += dx;
	sqr->og_edge4.y += dy;
	// inneficient BS just to show;
	sqr->min_y += dy;
	int i = 0;
	while (i < sqr->real_z)
	{
		sqr->min_max[i] += dx;
		sqr->min_max[i + sqr->real_z] += dx;
		i++;
	}
}

//xiaolin wu, há que alterar algoritmo para ter em conta inside e outside
//antialiasing nao ta bom, paciencia

void	render_square(t_win_glfw *win, t_square *sqr)
{
	int i;

	i = 1;
	while (i < sqr->real_z - 1)
	{
		draw_horizontal_line(win, sqr->min_max[i] + 1, sqr->min_max[i + sqr->real_z] - 1, i + sqr->min_y, sqr->color);
		i++;
	}

	xiaolinwu_line(win, sqr->edge1, sqr->edge2);
	xiaolinwu_line(win, sqr->edge2, sqr->edge3);
	xiaolinwu_line(win, sqr->edge3, sqr->edge4);
	xiaolinwu_line(win, sqr->edge4, sqr->edge1);
}


void	calculate_min_max(t_square *sqr)
{
	int i;
	
	sqr->max_y = sqr->edge1.y;
	sqr->min_y = sqr->edge1.y;
	sqr->max_y += (sqr->edge2.y - sqr->max_y) * (sqr->edge2.y > sqr->max_y);
	sqr->max_y += (sqr->edge3.y - sqr->max_y) * (sqr->edge3.y > sqr->max_y);
	sqr->max_y += (sqr->edge4.y - sqr->max_y) * (sqr->edge4.y > sqr->max_y);
	sqr->min_y -= (sqr->min_y - sqr->edge2.y) * (sqr->edge2.y < sqr->min_y);
	sqr->min_y -= (sqr->min_y - sqr->edge3.y) * (sqr->edge3.y < sqr->min_y);
	sqr->min_y -= (sqr->min_y - sqr->edge4.y) * (sqr->edge4.y < sqr->min_y);
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
	
	bersenham_min_max(sqr, sqr->edge1, sqr->edge2);
	bersenham_min_max(sqr, sqr->edge2, sqr->edge3);
	bersenham_min_max(sqr, sqr->edge3, sqr->edge4);
	bersenham_min_max(sqr, sqr->edge4, sqr->edge1);
	//i = 0;
	//while (i < sqr->real_z)
	//{
	//	printf("%d min %d max %d\n", i + sqr->min_y, sqr->min_max[i], sqr->min_max[i + sqr->real_z]);
	//	//printf("index %d, value %d\n", i, sqr->min_max[i]);
	//	i++;
	//}
	//	
	
}


void	rotate_square(t_square *sqr, t_pixel centre, float change)
{
	t_pixel	og;

	sqr->radians += change;
	sqr->cos_rad = cosf(sqr->radians);
	sqr->sen_rad = sinf(sqr->radians);
	//rotate_point(&sqr->edge1, centre, sqr->cos_rad, sqr->sen_rad);
	og = sqr->og_edge1;
    sqr->edge1.x = sqr->cos_rad * (og.x - centre.x) + sqr->sen_rad * (og.y - centre.y) + centre.x;
    sqr->edge1.y = -sqr->sen_rad * (og.x - centre.x) + sqr->cos_rad * (og.y - centre.y) + centre.y;
	og = sqr->og_edge2;
    sqr->edge2.x = sqr->cos_rad * (og.x - centre.x) + sqr->sen_rad * (og.y - centre.y) + centre.x;
    sqr->edge2.y = -sqr->sen_rad * (og.x - centre.x) + sqr->cos_rad * (og.y - centre.y) + centre.y;
	og = sqr->og_edge3;
    sqr->edge3.x = sqr->cos_rad * (og.x - centre.x) + sqr->sen_rad * (og.y - centre.y) + centre.x;
    sqr->edge3.y = -sqr->sen_rad * (og.x - centre.x) + sqr->cos_rad * (og.y - centre.y) + centre.y;
	og = sqr->og_edge4;
    sqr->edge4.x = sqr->cos_rad * (og.x - centre.x) + sqr->sen_rad * (og.y - centre.y) + centre.x;
    sqr->edge4.y = -sqr->sen_rad * (og.x - centre.x) + sqr->cos_rad * (og.y - centre.y) + centre.y;
	calculate_min_max(sqr);
}

void	new_init_square(t_square *sqr, t_pixel centre, int width, int color, int degrees)
{	
	sqr->centre = centre;
	sqr->width = width;
	sqr->color = color;
	sqr->radians = MY_PI / 180.0 * degrees;
	sqr->og_edge1 = (t_pixel){centre.x - width / 2, centre.y - width / 2, color};
	sqr->og_edge2 = (t_pixel){centre.x - width / 2, centre.y + width / 2, color};
	sqr->og_edge3 = (t_pixel){centre.x + width / 2, centre.y + width / 2, color};
	sqr->og_edge4 = (t_pixel){centre.x + width / 2, centre.y - width / 2, color};
	sqr->edge1 = sqr->og_edge1;
	sqr->edge2 = sqr->og_edge2;
	sqr->edge3 = sqr->og_edge3;
	sqr->edge4 = sqr->og_edge4;
	sqr->biggest_z = 1 + sqrt(width * width * 2);
	sqr->min_max = malloc(sizeof(*sqr->min_max) * sqr->biggest_z * 2);		//unprotected, *2 for min and max
	if (!sqr->min_max)
		return ;
	printf("crash?\n");
	rotate_square(sqr, sqr->centre, 0);
}