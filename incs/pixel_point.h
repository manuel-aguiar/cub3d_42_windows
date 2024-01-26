/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_point.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:31:34 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 16:31:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_POINT_H

# define PIXEL_POINT_H

# include "libft.h"

typedef struct s_pixel
{
	int	x;
	int	y;
	int	colour;
}	t_pixel;

typedef struct t_wpoint
{
	int	x;
	int	y;
}	t_wpoint;

int	rgb_r(int color);
int	rgb_g(int color);
int	rgb_b(int color);
int	rgb_a(int color);
int		rgba(int r, int g, int b, int a);

int gamma_average(int start, int end, int num, int den);
int	avg_colour(int start, int end, int num, int den);

//translate_rotate.c

void	translate_point(t_pixel	*point, int dx, int dy);
void	backward_rotate_point(t_pixel *point, t_pixel centre, float cos, float sin);
void	rotate_point(t_pixel *point, t_pixel centre, float cos, float sin);

#endif