/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_west.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:47 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	init_west_letter(t_west *west, t_pixel centre, int height, int width, int color)
{
	west->centre = centre;
	west->height = height;
	west->width = width;
	west->color = color;
	west->top_left = (t_pixel){centre.x - (width / 2 + 1), centre.y + (height / 2 + 1), 0, color};
	west->mid_bot_left = (t_pixel){centre.x - (width / 4), centre.y - (height / 2 + 1), 0, color};
	west->mid_top = (t_pixel){centre.x, centre.y + (height / 2 + 1), 0, color};
	west->mid_bot_right = (t_pixel){centre.x + (width / 4), centre.y - (height / 2 + 1), 0, color};
	west->top_right = (t_pixel){centre.x + (width / 2 + 1), centre.y + (height / 2 + 1), 0, color};
}

void	rotate_west_letter(t_west *west, int rotate)
{
	(void)west;
	(void)rotate;
}

void	render_west_letter(t_win_glfw *win, t_west *west)
{
	xiaolinwu_line(win, west->top_left, west->mid_bot_left);
	xiaolinwu_line(win, west->mid_bot_left, west->mid_top);
	xiaolinwu_line(win, west->mid_top, west->mid_bot_right);
	xiaolinwu_line(win, west->mid_bot_right, west->top_right);
}

