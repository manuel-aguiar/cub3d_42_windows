/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:12:55 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 16:12:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_H

# define PIXEL_H

typedef struct s_posi
{
	float x;
	float y;
}	t_posi;

typedef struct s_pixel
{
	int	x;
	int	y;
	int	colour;
}	t_pixel;

#endif