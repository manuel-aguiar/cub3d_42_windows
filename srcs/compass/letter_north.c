/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_north.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"



void	init_north_letter(t_north *north, t_pixel centre, int height, int width, int color)
{
	north->centre = centre;
	north->height = height;
	north->width = width;
	north->color = color;
	north->bot_left = (t_pixel){centre.x - (width / 2 + 1), centre.y - (height / 2 + 1), 0, color};
	north->bot_right = (t_pixel){centre.x + (width / 2 + 1), centre.y - (height / 2 + 1), 0, color};
	north->top_left = (t_pixel){centre.x - (width / 2 + 1), centre.y + (height / 2 + 1), 0, color};
	north->top_right = (t_pixel){centre.x + (width / 2 + 1), centre.y + (height / 2 + 1), 0, color};
}

void	rotate_north_letter(t_north *north, int rotate)
{
	(void)north;
	(void)rotate;
}

void	render_north_letter(t_win_glfw *win, t_north *north)
{
	xiaolinwu_line(win, north->bot_left, north->top_left);
	xiaolinwu_line(win, north->top_left, north->bot_right);
	xiaolinwu_line(win, north->bot_right, north->top_right);
}

