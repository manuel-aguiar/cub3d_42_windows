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

#include "render_windows.h"

/*Midpoint Circle algorithm, by calculating 1/8 of a circle, one can render the
full object by projecting coordinates

*/

// must be visible
void	win_drawcircle_wo_antialiasing(t_win_glfw *win, t_win_point center, int radius, int color, int width)
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