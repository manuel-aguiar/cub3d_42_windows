/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_without_aa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:15:48 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:15:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "game.h"

void	win_full_circle(t_win *win, t_pixel centre, int radius, int color)
{
    int x;
    int y;
    int decision;


	if (centre.x - radius < 0 || centre.y - radius < 0 || centre.x + radius > win->width || centre.y + radius > win->height)
		return ;
	x = radius;
	y = 0;
	decision = 1 - radius;
	while (y <= x)
	{
		draw_horizontal_line(win, -y + centre.x, y + centre.x, x + centre.y, color);
		draw_horizontal_line(win, -x + centre.x, x + centre.x, y + centre.y, color);
		draw_horizontal_line(win, -x + centre.x, x + centre.x, -y + centre.y, color);
		draw_horizontal_line(win, -y + centre.x, y + centre.x, -x + centre.y, color);
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



void	win_drawcircle_wo_antialiasing(t_win *win, t_pixel centre, int radius, int color, int width)
{
    int x;
    int y;
    int decision;
	int count;

	if (centre.x - radius < 0 || centre.y - radius < 0 || centre.x + radius > win->width || centre.y + radius > win->height)
		return ;

	count = 0;
	while (count < width)
	{
		x = radius - count;
		y = 0;
		decision = 1 - radius;

		while (y <= x)
		{
			win->set_pixel(win, x + centre.x, y + centre.y, color);
			win->set_pixel(win, -x + centre.x, y + centre.y, color);
			win->set_pixel(win, x + centre.x, -y + centre.y, color);
			win->set_pixel(win, -x + centre.x, -y + centre.y, color);
			win->set_pixel(win, y + centre.x, x + centre.y, color);
			win->set_pixel(win, -y + centre.x, x + centre.y, color);
			win->set_pixel(win, y + centre.x, -x + centre.y, color);
			win->set_pixel(win, -y + centre.x, -x + centre.y, color);
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

void	win_drawcircle_wo_antialiasing_clean(t_win *win, t_pixel centre, int radius, int color)
{
    int x;
    int y;
    int decision;

	x = radius;
	y = 0;
	decision = 1 - radius;

	while (y <= x)
	{
		win->set_pixel(win, x + centre.x, y + centre.y, color);
		win->set_pixel(win, -x + centre.x, y + centre.y, color);
		win->set_pixel(win, x + centre.x, -y + centre.y, color);
		win->set_pixel(win, -x + centre.x, -y + centre.y, color);
		win->set_pixel(win, y + centre.x, x + centre.y, color);
		win->set_pixel(win, -y + centre.x, x + centre.y, color);
		win->set_pixel(win, y + centre.x, -x + centre.y, color);
		win->set_pixel(win, -y + centre.x, -x + centre.y, color);
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
