/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:44:25 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 18:44:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pixel_point.h"

int		rgb_r(int color)
{
	return ((color >> 24) & 0xff);
}

int		rgb_g(int color)
{
	return ((color >> 16) & 0xff);
}

int		rgb_b(int color)
{
	return ((color >> 8) & 0xff);
}

int		rgb_a(int color)
{
	return (color & 0xff);
}

int		rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | (a));
}

int		argb(int color)
{
	int new;

	new = ((color & 0xff) << 24) \
	| (((color >> 8) & 0xff) << 16) \
	| (((color >> 16) & 0xff) << 8) \
	| ((color >> 24) & 0xff);
	return (new);
}

int		abgr_inversion(int r, int g, int b, int a)
{
	return ((a << 24) | (b << 16) | (g << 8) | (r));
}

int	avg_colour(int start, int end, int num, int den)
{
	t_ulong	r;
	t_ulong	g;
	t_ulong	b;
	t_ulong	a;


	if (den == 0)
		return (start);
	r = rgb_r(start) * num / den \
		+ rgb_r(end) * (den - num) / den;
	g = rgb_g(start) * num / den \
		+ rgb_g(end) * (den - num) / den;
	b = rgb_b(start) * num / den \
		+ rgb_b(end) * (den - num) / den;
	a = rgb_a(start);
	//int final = rgba(r, g, b, a);
	//printf("r %d g %d b %d a %d\n", (int)r, (int)g, (int)b, (int)a);
	return (rgba((int)r, (int)g, (int)b, (int)a));
}
