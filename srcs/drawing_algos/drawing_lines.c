/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:04:16 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:04:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing_algos.h"

void	draw_horizontal_line(t_win *win, int min_x, int max_x, int y, int color)
{
	while (min_x <= max_x)
		win->set_pixel(win, min_x++, y, color);
}

void	draw_vertical_line(t_win *win, int start_y, int end_y, int x, int color)
{
	while (start_y <= end_y)
		win->set_pixel(win, x, start_y++, color);
}

void bersenham_line(t_win *win, t_pixel start, t_pixel end, int color)
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
