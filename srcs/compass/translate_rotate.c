/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:39:15 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 13:39:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

void	translate_point(t_pixel	*point, int dx, int dy)
{
	point->x += dx;
	point->y += dy;
}

void	rotate_point(t_pixel *point, t_pixel centre, float cos, float sin)
{
	t_pixel og;

	og = *point;
    point->x = cos * (og.x - centre.x) + sin * (og.y - centre.y) + centre.x;
    point->y = - sin * (og.x - centre.x) + cos * (og.y - centre.y) + centre.y;
}
