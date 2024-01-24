/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:48:44 by marvin            #+#    #+#             */
/*   Updated: 2024/01/22 10:48:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void	print_tex_data(t_parsing *parsing)
{
	int	i;
	int color;

	i = 0;
	while (i < NUM_TEX)
	{
		if (parsing->tex_data[i].type == PATH_TEX)
			printf("%s\n", parsing->tex_data[i].path);
		else
		{
			color = parsing->tex_data[i].color;
			printf("(%d, %d, %d)\n", RGB_R(color), RGB_G(color), RGB_B(color));
		}
		i++;
	}	
}

void	gnl_len_print_line(void	*str)
{
	t_gnl_len *new;

	new = (t_gnl_len *)str;
	if (new->line)
		ft_putstr(new->line);
}

void	print_map(t_map *map)
{
	int i;
	int j;

	i = map->len - map->width;
	while (i >= 0)
	{
		j = 0;
		printf("\n");
		while (j < map->width)
		{
			printf("%c", map->map[i + j]);
			j++;
		}
		i -= map->width;
	}
	printf("\n");
}
