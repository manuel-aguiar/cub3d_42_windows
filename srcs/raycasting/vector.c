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

t_vector	vector_add(t_vector	first, t_vector second)
{
	return ((t_vector){first.x + second.x, first.y + second.y});
}

t_vector	vector_sub(t_vector plus, t_vector minus)
{
	return ((t_vector){plus.x - minus.x, plus.y - minus.y});
}

t_vector	vector_multi(t_vector target, float multiplier)
{
	return ((t_vector){target.x * multiplier, target.y * multiplier});
}

float		vector_len(t_vector vector)
{
	return (sqrt(fpow_2(vector.x) + fpow_2(vector.y)));
}

t_vector	vector_norm(t_vector target, float vector_len)
{
	return ((t_vector){target.x / vector_len, target.y / vector_len});
}
