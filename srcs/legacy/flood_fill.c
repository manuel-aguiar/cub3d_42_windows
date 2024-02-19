/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:22:25 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:22:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_windows.h"

void	flood_fill(t_win *win, int x, int y, int color)
{
	if (win->get_pixel(win, x, y) != 0)
		return ;
	win->set_pixel(win, x, y, color);
	flood_fill(win, x + 1, y, color);
	flood_fill(win, x, y + 1, color);
	flood_fill(win, x - 1, y, color);
	flood_fill(win, x, y - 1, color);
}
