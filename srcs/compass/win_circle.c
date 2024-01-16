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

void	win_drawcircle_wo_antialiasing_clean(t_win_glfw *win, t_pixel center, int radius, int color)
{
    int x;
    int y;
    int decision;

	x = radius;
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
}

//chatgpt xiaolin_wu circle

//(t_win_glfw *win, t_pixel center, int radius, int color)

void setPixel4(t_win_glfw *win, int centerX, int centerY, int deltaX, int deltaY, int color)
{
    win->set_pixel(win, centerX + deltaX, centerY + deltaY, color);
    win->set_pixel(win, centerX - deltaX, centerY + deltaY, color);
    win->set_pixel(win, centerX + deltaX, centerY - deltaY, color);
    win->set_pixel(win, centerX - deltaX, centerY - deltaY, color);
}

void	flood_fill(t_win_glfw *win, int x, int y, int color)
{
	if (win->get_pixel(win, x, y) != 0)
		return ;
	win->set_pixel(win, x, y, color);
	flood_fill(win, x + 1, y, color);
	flood_fill(win, x, y + 1, color);
	flood_fill(win, x - 1, y, color);
	flood_fill(win, x, y - 1, color);
}

void chatgpt_anticircle(t_win_glfw *win, t_pixel centre, int radius, int color)
{
	//win_full_circle(win, centre, radius, color);

	int centerX = centre.x;
	int centerY = centre.y;
    int radius2 = radius * radius;
    static const int maxTransparency = 127;

    // Upper and lower halves
    int quarterX = round(radius2 / sqrt(radius2 + radius2));
    for (int x = 0; x <= quarterX; x++) {
        float y = radius * sqrt(1 - x * x / (float)radius2);
        float error = y - floor(y);
        int transparency = round(error * maxTransparency);

		int alpha = avg_colour(0, color, transparency, maxTransparency);
		int alpha2 = avg_colour(0, color, (maxTransparency - transparency), maxTransparency);

        setPixel4(win, centerX, centerY, x, floor(y), alpha);
        setPixel4(win, centerX, centerY, x, floor(y) + 1, alpha2);
    }

    // Right and left halves
    int quarterY = round(radius2 / sqrt(radius2 + radius2));
    for (int y = 0; y <= quarterY; y++) {
        float x = radius * sqrt(1 - y * y / (float)radius2);
        float error = x - floor(x);
        int transparency = round(error * maxTransparency);

		int alpha = avg_colour(0, color, transparency, maxTransparency);
		int alpha2 = avg_colour(0, color, (maxTransparency - transparency), maxTransparency);

        setPixel4(win, centerX, centerY, floor(x), y, alpha);
        setPixel4(win, centerX, centerY, floor(x) + 1, y, alpha2);
    }
	flood_fill(win, centre.x, centre.y + radius - 1, color);
}
