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

void	draw_horizontal_line(t_win_glfw *win, int min_x, int max_x, int y, int color)
{
	while (min_x <= max_x)
		win->set_pixel(win, min_x++, y, color);
}

void	draw_vertical_line(t_win_glfw *win, int start_y, int end_y, int x, int color)
{
	while (start_y <= end_y)
		win->set_pixel(win, x, start_y++, color);
}
