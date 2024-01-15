/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_east.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	init_east_letter(t_east *east, t_pixel centre, int height, int width, int color)
{
	east->centre = centre;
	east->height = height;
	east->width = width;
	east->color = color;
	east->bot_left = (t_pixel){centre.x - (width / 2 + 1), centre.y - (height / 2 + 1), 0, color};
	east->bot_right = (t_pixel){centre.x + (width / 2 + 1), centre.y - (height / 2 + 1), 0, color};
	east->top_left = (t_pixel){centre.x - (width / 2 + 1), centre.y + (height / 2 + 1), 0, color};
	east->top_right = (t_pixel){centre.x + (width / 2 + 1), centre.y + (height / 2 + 1), 0, color};
	east->mid_left = (t_pixel){centre.x - (width / 2 + 1), centre.y, 0, color};
	east->mid_right = (t_pixel){centre.x + (width / 2 + 1), centre.y, 0, color};
}

void	rotate_east_letter(t_east *east, int rotate)
{
	(void)east;
	(void)rotate;
}

void	render_east_letter(t_win_glfw *win, t_east *east)
{
	xiaolinwu_line(win, east->bot_left, east->top_left);
	xiaolinwu_line(win, east->top_left, east->top_right);
	xiaolinwu_line(win, east->bot_left, east->bot_right);
	xiaolinwu_line(win, east->mid_left, east->mid_right);
}