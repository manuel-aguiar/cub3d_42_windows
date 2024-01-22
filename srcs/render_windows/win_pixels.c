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


# define WIN_ADJ(color) (((RGB_R(color)) << 24) | ((RGB_G(color)) << 16) | ((RGB_B(color)) << 8) | (RGB_A(color)))


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
	a = RGB_A(start);
	r = RGB_R(start) * num / den \
		+ RGB_R(end) * (den - num) / den;
	g = RGB_G(start) * num / den \
		+ RGB_G(end) * (den - num) / den;
	b = RGB_B(start) * num / den \
		+ RGB_B(end) * (den - num) / den;
	return (ARGB(a, r, g, b));
}

void	swap_pixels(t_pixel *start, t_pixel *end)
{
	t_pixel	temp;

	temp = *start;
	*start = *end;
	*end = temp;
}
