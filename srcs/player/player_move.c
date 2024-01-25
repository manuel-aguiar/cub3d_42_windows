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
	float cos_plus_45;
	float sin_plus_45;

	cos_plus_45 = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
	sin_plus_45 = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
	player->map_posi.x -= (player->move_sense * cos_plus_45);
	player->map_posi.y += (player->move_sense * sin_plus_45);
}

void    move_player_back_right(t_player *player)
{
	float cos_minus_45;
	float sin_minus_45;

	cos_minus_45 = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
	sin_minus_45 = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
	player->map_posi.x -= (player->move_sense * cos_minus_45);
	player->map_posi.y += (player->move_sense * sin_minus_45);
}

void    move_player_for_left(t_player *player)
{
	float cos_minus_45;
	float sin_minus_45;

	cos_minus_45 = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
	sin_minus_45 = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
	player->map_posi.x += (player->move_sense * cos_minus_45);
	player->map_posi.y -= (player->move_sense * sin_minus_45);
}

void    move_player_for_right(t_player *player)
{
	float cos_plus_45;
	float sin_plus_45;

	cos_plus_45 = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
	sin_plus_45 = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
	player->map_posi.x += (player->move_sense * cos_plus_45);                   //wait till overflow maybe...?
	player->map_posi.y -= (player->move_sense * sin_plus_45);
}

void    move_player_left(t_player *player)
{
	player->map_posi.x += -(player->move_sense * -player->sin_rad);
	player->map_posi.y += -(player->move_sense * -player->cos_rad);
}

void    move_player_right(t_player *player)
{
	player->map_posi.x += (player->move_sense * -player->sin_rad);
	player->map_posi.y += (player->move_sense * -player->cos_rad);
}


void    move_player_backward(t_player *player)
{
	player->map_posi.x -= (player->move_sense * player->cos_rad);
	player->map_posi.y += (player->move_sense * player->sin_rad);
}

void    move_player_forward(t_player *player)
{
	player->map_posi.x += (player->move_sense * player->cos_rad);              
	player->map_posi.y -= (player->move_sense * player->sin_rad);
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
	printf("player: %.3f    %.3f\n", player->map_posi.x, player->map_posi.y);
}