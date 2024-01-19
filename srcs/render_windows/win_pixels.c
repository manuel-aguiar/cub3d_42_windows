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
	char		*my_dst;

	my_dst = win->front_buf + (y * win->win_width + x) * RGB_SIZE;
	*(unsigned int *)my_dst = color;
}

int	win_get_pixel(t_win_glfw *win, int x, int y)
{
	char		*my_dst;

	my_dst = win->front_buf + (y * win->win_width + x) * RGB_SIZE;
	return (*(unsigned int *)my_dst);
}

int	avg_colour(int start, int end, int num, int den)
{
	t_ulong	r;
	t_ulong	g;
	t_ulong	b;
	t_ulong	a;

	if (den == 0)
		return (start);
	a = ((start >> 24) & 0xff);
	r = ((start >> 16) & 0xff) * num / den \
		+ ((end >> 16) & 0xff) * (den - num) / den;
	g = ((start >> 8) & 0xff) * num / den \
		+ ((end >> 8) & 0xff) * (den - num) / den;
	b = ((start) & 0xff) * num / den \
		+ ((end) & 0xff) * (den - num) / den;
	//a = (start & 0xff);
	
	return (RGBA(r, g, b, a));
}

void	swap_pixels(t_pixel *start, t_pixel *end)
{
	t_pixel	temp;

	temp = *start;
	*start = *end;
	*end = temp;
}
