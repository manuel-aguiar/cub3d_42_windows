/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:20:08 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 16:20:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_UTILS_H

# define GENERIC_UTILS_H

# include "libft.h"

# define P_MY_PI 3.14159265f

//clamp.c
int		int_clamp(int value, int min, int max);
float	float_clamp(float value, float min, float max);

//radian_truncate.c
float	radian_truncate(float radian);

//ft_split_count_replenish.c
char	**ft_split_count_replenish(t_cchar *s, t_cchar *og, \
		char *sepset, int *place_count);

//fpow_2.c
float	fpow_2(float number);

#endif