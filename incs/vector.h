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

typedef struct s_vector
{
	float x;
	float y;
}	t_vector;

t_vector	vector_add(t_vector	first, t_vector second);
t_vector	vector_sub(t_vector plus, t_vector minus);
t_vector	vector_multi(t_vector target, float multiplier);
float		vector_len(t_vector vector);
t_vector	vector_norm(t_vector target, float vector_len);
t_vector	vector_swap_coords(t_vector target);

#endif