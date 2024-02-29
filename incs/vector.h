/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:12:55 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 16:12:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_H

# define PIXEL_H

# include "math.h"
# include "generic_utils.h"
# include "pixel_point.h"

typedef struct s_vec2d
{
	float x;
	float y;
}	t_vec2d;

typedef struct s_vec3d
{
	float x;
	float y;
	float z;
}	t_vec3d;

t_vec2d		vec2d_add(t_vec2d	first, t_vec2d second);
t_vec2d		vec2d_sub(t_vec2d plus, t_vec2d minus);
t_vec2d		vec2d_multi(t_vec2d target, float multiplier);
float		vec2d_len(t_vec2d vector);
t_vec2d		vec2d_norm(t_vec2d target, float vec2d_len);
t_vec2d		vec2d_swap_coords(t_vec2d target);
float		vec2d_distance(t_vec2d start, t_vec2d end);
t_vec2d		vec2d_product(t_vec2d first, t_vec2d second);

float		vec3d_len(t_vec3d vec);
t_vec3d		vec3d_sub(t_vec3d first, t_vec3d second);

#endif