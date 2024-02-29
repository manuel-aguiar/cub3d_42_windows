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

float	vec3d_len(t_vec3d vec)
{
	return (sqrt(fpow_2(vec.x) + fpow_2(vec.y) + fpow_2(vec.z)));
}

t_vec3d	vec3d_sub(t_vec3d first, t_vec3d second)
{
	return ((t_vec3d){second.x - first.x, second.y - first.y, second.z - first.z});
}
