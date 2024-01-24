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

	// check left; 0.5f is half the unit hieght of a square
	if (map->map[fixed_x + fixed_y * map->width] == '1')
	{
		player->map_posi.x = ft_fmax(player->map_posi.x, fixed_x + (player->unit_size + 0.5f));
		//player->map_posi.y = float_clamp(player->map_posi.y, fixed_y + player->unit_size, fixed_y + 1 - player->unit_size);		
	}

	//check right
	if (map->map[(fixed_x + 1) + fixed_y * map->width] == '1')
	{
		player->map_posi.x = ft_fmin(player->map_posi.x, fixed_x + 1 - (player->unit_size + 0.5f));
	}


	//check below
	//if (map->map[fixed_x + (fixed_y - 1) * map->width] == '1')
	//{
	//	player->map_posi.y = ft_fmax(player->map_posi.y, fixed_y + (player->unit_size - 0.5f));
	//}		

	//check above
	//if (map->map[fixed_x + (fixed_y + 1) * map->width] == '1')
	//{
	//	player->map_posi.y = ft_fmin(player->map_posi.y, fixed_y + 1 - (player->unit_size - 0.5f));
	//}	

}