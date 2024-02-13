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

/*
https://github.com/OneLoneCoder/Javidx9/blob/master/PixelGameEngine/SmallerProjects/OneLoneCoder_PGE_CircleVsRect.cpp
*/

void	handle_collisions(t_game *game, t_vector potencial)
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
	
	float pot_len;
	pot_len = vector_len(potencial);
	if (pot_len > player->unit_size)
	{
		potencial = vector_multi(vector_norm(potencial, pot_len), player->unit_size - 0.001f);
	}

	player->map_posi = vector_add(player->map_posi, potencial);


	
	//float_x = player->map_posi.x - fixed_x;
	//float_y = player->map_posi.y - fixed_y;

	//printf("i am at (%.3f, %.3f), my square is %c\n", player->map_posi.x, player->map_posi.y, map->map[fixed_x + fixed_y * map->width]);
	//check left


		

		if (map->map[(fixed_x - 1) + fixed_y * map->width] == MAP_WALL)
			player->map_posi.x = ft_fmax(player->map_posi.x, fixed_x + (player->unit_size));
		if (map->map[(fixed_x + 1) + fixed_y * map->width] == MAP_WALL)
			player->map_posi.x = ft_fmin(player->map_posi.x, fixed_x + 1 - (player->unit_size));
		if (map->map[fixed_x + (fixed_y + 1) * map->width] == MAP_WALL)
			player->map_posi.y = ft_fmin(player->map_posi.y, fixed_y + 1 - (player->unit_size));
		if (map->map[fixed_x + (fixed_y - 1) * map->width] == MAP_WALL)
			player->map_posi.y = ft_fmax(player->map_posi.y, fixed_y + (player->unit_size));


		t_vector nearest;
		t_vector ray_to_nearest;
		float	ray_length;
		float	overlap;
		

		//check topo left
		//printf("fixed x %d, fixed y %d, index top left %d\n", fixed_x, fixed_y,(fixed_x - 1) + (fixed_y + 1) * map->width);
		if (map->map[(fixed_x - 1) + (fixed_y + 1) * map->width] == MAP_WALL)
		{
			//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
			nearest.x = ft_fmin(player->map_posi.x, (float)fixed_x);
			nearest.y = ft_fmax(player->map_posi.y, (float)(fixed_y + 1));
			ray_to_nearest = vector_sub(nearest,  player->map_posi);
			ray_length = vector_len(ray_to_nearest);

			overlap = player->unit_size - ray_length;
			if (overlap > 0)
			{
				ray_to_nearest = vector_norm(ray_to_nearest, ray_length);
				player->map_posi = vector_sub(player->map_posi, vector_multi(ray_to_nearest, overlap));
			}
			//printf("posi end (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
		}
		//top right
		if (map->map[(fixed_x + 1) + (fixed_y + 1) * map->width] == MAP_WALL)
		{
			//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
			nearest.x = ft_fmax(player->map_posi.x, (float)(fixed_x + 1));
			nearest.y = ft_fmax(player->map_posi.y, (float)(fixed_y + 1));
			ray_to_nearest = vector_sub(nearest,  player->map_posi);
			ray_length = vector_len(ray_to_nearest);

			overlap = player->unit_size - ray_length;
			if (overlap > 0)
			{
				ray_to_nearest = vector_norm(ray_to_nearest, ray_length);
				player->map_posi = vector_sub(player->map_posi, vector_multi(ray_to_nearest, overlap));
			}
		}

		//bot left
		if (map->map[(fixed_x - 1) + (fixed_y - 1) * map->width] == MAP_WALL)
		{
			//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
			nearest.x = ft_fmin(player->map_posi.x, (float)(fixed_x));
			nearest.y = ft_fmin(player->map_posi.y, (float)(fixed_y));
			ray_to_nearest = vector_sub(nearest,  player->map_posi);
			ray_length = vector_len(ray_to_nearest);

			overlap = player->unit_size - ray_length;
			if (overlap > 0)
			{
				ray_to_nearest = vector_norm(ray_to_nearest, ray_length);
				player->map_posi = vector_sub(player->map_posi, vector_multi(ray_to_nearest, overlap));
			}
		}

		//bot right
		if (map->map[(fixed_x + 1) + (fixed_y - 1) * map->width] == MAP_WALL)
		{
			//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
			nearest.x = ft_fmax(player->map_posi.x, (float)(fixed_x + 1));
			nearest.y = ft_fmin(player->map_posi.y, (float)(fixed_y));
			ray_to_nearest = vector_sub(nearest, player->map_posi);
			ray_length = vector_len(ray_to_nearest);

			overlap = player->unit_size - ray_length;
			if (overlap > 0)
			{
				ray_to_nearest = vector_norm(ray_to_nearest, ray_length);
				player->map_posi = vector_sub(player->map_posi, vector_multi(ray_to_nearest, overlap));
			}
		}




	//printf("player->map_posi (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);


	
}

/*

	//printf("player in %d, %d\n", fixed_x, fixed_y);
	//t_vector nearest;
	//t_vector ray_to_nearest;
	//float	ray_length;
	//float	overlap;
	//int			x;
	//int			y;
	//x = -1;
	//while (x <= 1)
	//{
	//	y = -1;
	//	while (y <= 1)
	//	{
	//		//printf("checking point %d, %d\n", (fixed_x + x), (fixed_y + y));
	//		if (map->map[(fixed_x + x) + (fixed_y + y) * map->width] == '1')
	//		{
	//			//printf("posi start (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y);
	//			nearest.x = ft_fmax(fixed_x + x, ft_fmin(potencial_posi.x, fixed_x + x + 1));
//
	//			nearest.y = ft_fmax(fixed_y + y, ft_fmin(potencial_posi.y, fixed_y + y + 1));
	//			//if (y == 1 && nearest.y > fixed_y + y)
	//			//	nearest.y = fixed_y + y;
	//			ray_to_nearest = vector_sub(nearest, potencial_posi);
	//			ray_length = vector_len(ray_to_nearest);
//
	//			overlap = player->unit_size - ray_length;
	//			if (overlap > 0)
	//			{
	//				
	//				printf("player at %d, %d, collision registered at %d, %d\n", fixed_x, fixed_y, (fixed_x + x), (fixed_y + y));
	//				printf("player is (%.3f, %.3f), radius (%.3f), wants to be (%.3f, %.3f)\n", player->map_posi.x, player->map_posi.y, player->unit_size, potencial_posi.x, potencial_posi.y);
	//				printf("nearest (%.3f, %.3f), ray_to_nearest (%.3f, %.3f) ray_len (%.3f)\n", nearest.x, nearest.y, ray_to_nearest.x, ray_to_nearest.y, ray_length);
	//				
	//				potencial_posi = vector_sub(potencial_posi, vector_multi(vector_norm(ray_to_nearest, ray_length), overlap));
	//				printf("new player posi will be (%.3f, %.3f)\n", potencial_posi.x, potencial_posi.y);
	//			}
	//		}
	//		y++;
	//	}
	//	x++;
	//}
	
	
	*/