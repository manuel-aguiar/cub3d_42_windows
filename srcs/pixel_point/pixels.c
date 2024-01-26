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

int	avg_colour(int start, int end, int num, int den)
{
	t_ulong	r;
	t_ulong	g;
	t_ulong	b;
	t_ulong	a;

	if (den == 0)
		return (start);
	r = rgb_a(start) * num / den \
		+ rgb_a(end) * (den - num) / den;
	g = rgb_a(start) * num / den \
		+ rgb_a(end) * (den - num) / den;
	b = rgb_a(start) * num / den \
		+ rgb_a(end) * (den - num) / den;
	a = rgb_a(start);
	return (rgba(r, g, b, a));
}
