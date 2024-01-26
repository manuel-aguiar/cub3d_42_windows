/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player_collisions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:06:07 by marvin            #+#    #+#             */
/*   Updated: 2024/01/24 17:06:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"





void	handle_collisions(t_game *game)
{
	t_player	*player;
	t_map		*map;
	int			fixed_x;
	int			fixed_y;
	//float		float_x;
	//float		float_y;

	
	player = &game->player;
	map = &game->map;
	fixed_x = (int)player->map_posi.x;
	fixed_y = (int)player->map_posi.y;
	//float_x = player->map_posi.x - fixed_x;
	//float_y = player->map_posi.y - fixed_y;

	//printf("i am at (%.3f, %.3f), my square is %c\n", player->map_posi.x, player->map_posi.y, map->map[fixed_x + fixed_y * map->width]);
	//check left
	if (map->map[(fixed_x - 1) + fixed_y * map->width] == '1')
		player->map_posi.x = ft_fmax(player->map_posi.x, fixed_x + (player->unit_size));
	if (map->map[(fixed_x + 1) + fixed_y * map->width] == '1')
		player->map_posi.x = ft_fmin(player->map_posi.x, fixed_x + 1 - (player->unit_size));
	if (map->map[fixed_x + (fixed_y + 1) * map->width] == '1')
		player->map_posi.y = ft_fmin(player->map_posi.y, fixed_y + 1 - (player->unit_size));
	if (map->map[fixed_x + (fixed_y - 1) * map->width] == '1')
		player->map_posi.y = ft_fmax(player->map_posi.y, fixed_y + (player->unit_size));


	t_vector nearest;
	t_vector ray_to_nearest;
	float	ray_length;
	float	diff;

	//check topo left
	//printf("fixed x %d, fixed y %d, index top left %d\n", fixed_x, fixed_y,(fixed_x - 1) + (fixed_y + 1) * map->width);
	if (map->map[(fixed_x - 1) + (fixed_y + 1) * map->width] == '1')
	{
		//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
		nearest.x = ft_fmin(player->map_posi.x, (float)fixed_x);
		nearest.y = ft_fmax(player->map_posi.y, (float)(fixed_y + 1));
		ray_to_nearest.x = nearest.x - player->map_posi.x;
		ray_to_nearest.y = nearest.y - player->map_posi.y;
		ray_length = vector_len(ray_to_nearest);

		diff = player->unit_size - ray_length;
		if (diff > 0)
		{
			ray_to_nearest.x /= ray_length;
			ray_to_nearest.y /= ray_length;
			player->map_posi.x -= ray_to_nearest.x * diff;
			player->map_posi.y -= ray_to_nearest.y * diff;
		}
		//printf("posi end (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
	}
	//top right
	if (map->map[(fixed_x + 1) + (fixed_y + 1) * map->width] == '1')
	{
		//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
		nearest.x = ft_fmax(player->map_posi.x, (float)(fixed_x + 1));
		nearest.y = ft_fmax(player->map_posi.y, (float)(fixed_y + 1));
		ray_to_nearest.x = nearest.x - player->map_posi.x;
		ray_to_nearest.y = nearest.y - player->map_posi.y;
		ray_length = vector_len(ray_to_nearest);

		diff = player->unit_size - ray_length;
		if (diff > 0)
		{
			ray_to_nearest.x /= ray_length;
			ray_to_nearest.y /= ray_length;
			player->map_posi.x -= ray_to_nearest.x * diff;
			player->map_posi.y -= ray_to_nearest.y * diff;
		}
	}

	//bot left
	if (map->map[(fixed_x - 1) + (fixed_y - 1) * map->width] == '1')
	{
		//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
		nearest.x = ft_fmin(player->map_posi.x, (float)(fixed_x));
		nearest.y = ft_fmin(player->map_posi.y, (float)(fixed_y));
		ray_to_nearest.x = nearest.x - player->map_posi.x;
		ray_to_nearest.y = nearest.y - player->map_posi.y;
		ray_length = vector_len(ray_to_nearest);

		diff = player->unit_size - ray_length;
		if (diff > 0)
		{
			ray_to_nearest.x /= ray_length;
			ray_to_nearest.y /= ray_length;
			player->map_posi.x -= ray_to_nearest.x * diff;
			player->map_posi.y -= ray_to_nearest.y * diff;
		}
	}

	//bot right
	if (map->map[(fixed_x + 1) + (fixed_y - 1) * map->width] == '1')
	{
		//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
		nearest.x = ft_fmax(player->map_posi.x, (float)(fixed_x + 1));
		nearest.y = ft_fmin(player->map_posi.y, (float)(fixed_y));
		ray_to_nearest = vector_sub(nearest, player->map_posi);
		ray_length = vector_len(ray_to_nearest);

		diff = player->unit_size - ray_length;
		if (diff > 0)
		{
			ray_to_nearest = vector_norm(ray_to_nearest, ray_length);
			player->map_posi = vector_sub(player->map_posi, vector_multi(ray_to_nearest, diff));
		}
	}

}