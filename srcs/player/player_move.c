/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:30:57 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 19:30:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	handle_collisions(t_game *game);

void    move_player_back_left(t_player *player)
{
	t_vector diagonal;

	diagonal.x = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
	diagonal.y = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
	player->map_posi.x -= (diagonal.y * player->move_sense); 
	player->map_posi.y += (diagonal.x * player->move_sense);
}

void    move_player_back_right(t_player *player)
{
	t_vector diagonal;

	diagonal.x = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
	diagonal.y = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
	player->map_posi.x += (diagonal.y * player->move_sense);                   //wait till overflow maybe...?
	player->map_posi.y -= (diagonal.x * player->move_sense);
}

void    move_player_for_left(t_player *player)
{
	t_vector diagonal;

	diagonal.x = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
	diagonal.y = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
	player->map_posi.x -= (diagonal.y * player->move_sense); 
	player->map_posi.y += (diagonal.x * player->move_sense);
}

void    move_player_for_right(t_player *player)
{
	t_vector diagonal;

	diagonal.x = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
	diagonal.y = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
	player->map_posi.x += (diagonal.y * player->move_sense);                   //wait till overflow maybe...?
	player->map_posi.y -= (diagonal.x * player->move_sense);
}

void    move_player_left(t_player *player)
{
	player->map_posi.x -= (player->dir_vec.y * player->move_sense);
	player->map_posi.y += (player->dir_vec.x * player->move_sense);
}

void    move_player_right(t_player *player)
{
	player->map_posi.x += (player->dir_vec.y * player->move_sense);
	player->map_posi.y -= (player->dir_vec.x * player->move_sense);
}


void    move_player_backward(t_player *player)
{
	player->map_posi = vector_sub(player->map_posi, vector_multi(player->dir_vec, player->move_sense));
}

void    move_player_forward(t_player *player)
{
	player->map_posi = vector_add(player->map_posi, vector_multi(player->dir_vec, player->move_sense));
}


void    move_player(t_game *game, bool w, bool s, bool a, bool d)
{
	t_player *player;

	player = &game->player;
	if (w && !s)
	{
		if (a && !d)
			move_player_for_left(player);
		else if (d && !a)
			move_player_for_right(player);
		else
			move_player_forward(player);
	}
	else if (s && !w)
	{
		if (a && !d)
			move_player_back_left(player);
		else if (d && !a)
			move_player_back_right(player);
		else
			move_player_backward(player);        
	}
	else if (a && !d)
		move_player_left(player);
	else if (d && !a)
		move_player_right(player);
	handle_collisions(game);
	//printf("player: %.3f    %.3f\n", player->map_posi.x, player->map_posi.y);
}