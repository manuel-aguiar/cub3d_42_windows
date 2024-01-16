/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:32:07 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 11:32:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

/*Midpoint Circle algorithm, by calculating 1/8 of a circle, one can render the
full object by projecting coordinates

i will have to use a hashtable to store the circles coordinates to make collision
detection easier. inner circle will not be moveable so the coordinates will always
be valid. if the circle has atmost 200 height, i'll be storing 1600 bytes,
so it is a very small table and not drain much memory

hashtable for the square as well, for each single frame the square will be the same for everyone except
the offset from where it starts off, with a couple of lookups i can check the boundaries for
each scanline and print only what is needed

*/

// must be visible

void	draw_horizontal_line(t_win_glfw *win, int min_x, int max_x, int y, int color)
{
	while (min_x <= max_x)
		win->set_pixel(win, min_x++, y, color);
}		


void	win_full_circle(t_win_glfw *win, t_pixel center, int radius, int color)
{
    int x;
    int y;
    int decision;


	if (center.x - radius < 0 || center.y - radius < 0 || center.x + radius > win->win_width || center.y + radius > win->win_height)
		return ;
	x = radius;
	y = 0;
	decision = 1 - radius;
	while (y <= x)
	{
		draw_horizontal_line(win, -y + center.x, y + center.x, x + center.y, color);
		draw_horizontal_line(win, -x + center.x, x + center.x, y + center.y, color);
		draw_horizontal_line(win, -x + center.x, x + center.x, -y + center.y, color);
		draw_horizontal_line(win, -y + center.x, y + center.x, -x + center.y, color);
		y++;
		if (decision <= 0)
			decision += 2 * y + 1;
		else
		{
			x--;
			decision += 2 * (y - x) + 1;
		}
	}
}


void	win_drawcircle_wo_antialiasing(t_win_glfw *win, t_pixel center, int radius, int color, int width)
{
    int x;
    int y;
    int decision;
	int count;

	if (center.x - radius < 0 || center.y - radius < 0 || center.x + radius > win->win_width || center.y + radius > win->win_height)
		return ;

	count = 0;
	while (count < width)
	{
		x = radius - count;
		y = 0;
		decision = 1 - radius;

		while (y <= x)
		{
			win->set_pixel(win, x + center.x, y + center.y, color);
			win->set_pixel(win, -x + center.x, y + center.y, color);
			win->set_pixel(win, x + center.x, -y + center.y, color);
			win->set_pixel(win, -x + center.x, -y + center.y, color);
			win->set_pixel(win, y + center.x, x + center.y, color);
			win->set_pixel(win, -y + center.x, x + center.y, color);
			win->set_pixel(win, y + center.x, -x + center.y, color);
			win->set_pixel(win, -y + center.x, -x + center.y, color);
			y++;
			if (decision <= 0)
				decision += 2 * y + 1;
			else
			{
				x--;
				decision += 2 * (y - x) + 1;
			}
		}
		count++;
	}
}