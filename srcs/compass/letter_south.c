/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_south.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"


void	init_south_letter(t_south *south, t_pixel centre, int height, int width, int color)
{
	south->centre = centre;
	south->height = height;
	south->width = width;
	south->color = color;
	south->bot_left = (t_pixel){centre.x - (width / 2 + 1), centre.y - (height / 2 + 1), 0, color};
	south->bot_right = (t_pixel){centre.x + (width / 2 + 1), centre.y - (height / 2 + 1), 0, color};
	south->top_left = (t_pixel){centre.x - (width / 2 + 1), centre.y + (height / 2 + 1), 0, color};
	south->top_right = (t_pixel){centre.x + (width / 2 + 1), centre.y + (height / 2 + 1), 0, color};
	south->mid_left = (t_pixel){centre.x - (width / 2 + 1), centre.y, 0, color};
	south->mid_right = (t_pixel){centre.x + (width / 2 + 1), centre.y, 0, color};
}

void	rotate_south_letter(t_south *south, int rotate)
{
	(void)south;
	(void)rotate;
}

void	render_south_letter(t_win_glfw *win, t_south *south)
{
	xiaolinwu_line(win, south->bot_left, south->bot_right);
	xiaolinwu_line(win, south->bot_right, south->mid_right);
	xiaolinwu_line(win, south->mid_right, south->mid_left);
	xiaolinwu_line(win, south->mid_left, south->top_left);
	xiaolinwu_line(win, south->top_left, south->top_right);
}
