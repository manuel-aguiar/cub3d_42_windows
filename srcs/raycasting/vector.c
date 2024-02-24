/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:07:43 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 13:07:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vector.h"

t_vec2d	vector_add(t_vec2d	first, t_vec2d second)
{
	return ((t_vec2d){first.x + second.x, first.y + second.y});
}

t_vec2d	vector_sub(t_vec2d plus, t_vec2d minus)
{
	return ((t_vec2d){plus.x - minus.x, plus.y - minus.y});
}

t_vec2d	vector_multi(t_vec2d target, float multiplier)
{
	return ((t_vec2d){target.x * multiplier, target.y * multiplier});
}

float		vector_len(t_vec2d vector)
{
	return (sqrt(fpow_2(vector.x) + fpow_2(vector.y)));
}

t_vec2d	vector_norm(t_vec2d target, float vector_len)
{
	if (vector_len == 0)
		return ((t_vec2d){0, 0});
	return ((t_vec2d){target.x / vector_len, target.y / vector_len});
}

t_vec2d	vector_swap_coords(t_vec2d target)
{
	float	swap;

	swap = target.x;
	target.x = target.y;
	target.y = swap;
	return (target);
}

float	vector_distance(t_vec2d start, t_vec2d end)
{
	return (sqrt(fpow_2(end.x - start.x) + sqrt(fpow_2(end.y - start.y))));
}

t_vec2d	vector_product(t_vec2d first, t_vec2d second)
{
	return((t_vec2d){first.x * second.x, first.y * second.y});
}