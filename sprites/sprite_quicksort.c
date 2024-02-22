/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_quicksort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:51:15 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 12:51:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sprites.h"

int	sprite_qs_comp(float first_dist, float second_dist)
{
	return (first_dist < second_dist);
}

static void	swap(t_sprite *first, t_sprite *second)
{
	t_sprite	temp;

	temp = *first;
	*first = *second;
	*second = temp;
}


static int	partition(t_sprite *sprites, int low, int high, int (*cmp)(float , float))
{
	float pivot;
	int		i;
	int		j;

	pivot = sprites[low].dist;
	i = low - 1;
	j = high + 1;
	while (1)
	{
		i++;
		while (cmp(pivot, sprites[i].dist))
			i++;
		j--;
		while (cmp(sprites[j].dist, pivot))
			j--;
		if (i >= j)
			return (j);
		swap(&sprites[i], &sprites[j]);
	}
}

static void	qs_recursion(t_sprite *sprites, int low, int high, int (*cmp)(float , float))
{
	int			part;

	if (low < high)
	{
		part = partition(sprites, low, high, cmp);
		qs_recursion(sprites, low, part, cmp);
		qs_recursion(sprites, part + 1, high, cmp);
	}
}

void	sprite_qs_distance(t_sprite *sprites, int sprite_count, int (*cmp)(float , float))
{
	qs_recursion(sprites, 0, sprite_count - 1, cmp);
}