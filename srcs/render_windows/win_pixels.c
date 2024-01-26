/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_set_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:41:56 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:41:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_windows.h"

void	win_set_pixel(t_win_glfw *win, int x, int y, int color)
{
	int i;

	i = (x + y * win->width) * RGB_SIZE;
	//printf("%d %d %d %d\n", rgb_r(color), rgb_g(color), rgb_b(color), rgb_a(color));
	win->front_buf[i++] = rgb_r(color);
	win->front_buf[i++] = rgb_g(color);
	win->front_buf[i++] = rgb_b(color);
	win->front_buf[i] = rgb_a(color);
}

int	win_get_pixel(t_win_glfw *win, int x, int y)
{
	char r;
	char g;
	char b;
	char a;
	int 	i;

	i = (x + y * win->width) * RGB_SIZE;
	r = win->front_buf[i++];
	g = win->front_buf[i++];
	b = win->front_buf[i++];
	a = win->front_buf[i++];
	return (rgba(r, g, b, a));
}



void	swap_pixels(t_pixel *start, t_pixel *end)
{
	t_pixel	temp;

	temp = *start;
	*start = *end;
	*end = temp;
}

