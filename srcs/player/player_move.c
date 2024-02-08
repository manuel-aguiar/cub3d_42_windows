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

t_vector    move_player_back_left(t_player *player)
{
	t_vector diagonal;
	float		speed;

	speed = player->back_move * player->cur_move_multi * player->timer[CLOCK_MOVE].elapsed;
	diagonal.x = 1 * (P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad);
	diagonal.y = -1 * (P_SQRT_OF_TWO_OVER_TWO * player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad);
	return(vector_multi(vector_swap_coords(diagonal), speed));
}

t_vector    move_player_back_right(t_player *player)
{
	t_vector diagonal;
	float		speed;

	speed = player->back_move * player->cur_move_multi * player->timer[CLOCK_MOVE].elapsed;


	diagonal.x = -1 * (P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad);
	diagonal.y = 1 * (P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad);

	return(vector_multi(vector_swap_coords(diagonal), speed));
}

t_vector    move_player_for_left(t_player *player)
{
	t_vector diagonal;
	float		speed;

	speed = player->side_move * player->cur_move_multi * player->timer[CLOCK_MOVE].elapsed;
	diagonal.x = 1 * (P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad);
	diagonal.y = -1 * (P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad);
	return(vector_multi(vector_swap_coords(diagonal), speed));
}

t_vector    move_player_for_right(t_player *player)
{
	t_vector	diagonal;
	float		speed;

	speed = player->side_move * player->cur_move_multi * player->timer[CLOCK_MOVE].elapsed;
	diagonal.x = -1 * (P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad);
	diagonal.y = 1 * (P_SQRT_OF_TWO_OVER_TWO * player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad);

	return(vector_multi(vector_swap_coords(diagonal), speed));
}

t_vector    move_player_left(t_player *player)
{
	float	speed;

	speed = player->side_move * player->cur_move_multi * player->timer[CLOCK_MOVE].elapsed;
	return (vector_multi((t_vector){-player->dir_vec.y, +player->dir_vec.x}, speed));
}

t_vector    move_player_right(t_player *player)
{
	float	speed;

	speed = player->side_move * player->cur_move_multi * player->timer[CLOCK_MOVE].elapsed;
	return (vector_multi((t_vector){+player->dir_vec.y, -player->dir_vec.x}, speed));
}


t_vector    move_player_backward(t_player *player)
{
	return (vector_multi(vector_multi(player->dir_vec, player->back_move * player->cur_move_multi * player->timer[CLOCK_MOVE].elapsed), -1));
}

t_vector    move_player_forward(t_player *player)
{
	float speed;

	speed = player->forward_move * player->cur_move_multi;
	if (player->is_sprinting && (player->hgt_state == HGT_NORMAL || player->hgt_state == HGT_JUMP))
		speed *= player->sprint_move_multi;
	return (vector_multi(player->dir_vec, speed * player->timer[CLOCK_MOVE].elapsed));
}


void    move_player(t_game *game, bool w, bool s, bool a, bool d)
{
	t_player 	*player;
	t_vector	potencial;

	player = &game->player;
	player->cur_move_multi = player->move_multi[player->hgt_state];
	if (player->is_aiming)
		player->cur_move_multi *= player->aim_move_multi;
	if (!w && !s && !a && !d)
	{
		player->is_walking = false;
		return ;
	}
	if (player->is_walking == false && player->hgt_state != HGT_JUMP)
	{
		player->cur_walk_sense = 0;
	}
	player->is_walking = true;
	if (w && !s)
	{
		if (a && !d)
			potencial = move_player_for_left(player);
		else if (d && !a)
			potencial = move_player_for_right(player);
		else
			potencial = move_player_forward(player);
	}
	else if (s && !w)
	{
		if (a && !d)
			potencial = move_player_back_left(player);
		else if (d && !a)
			potencial = move_player_back_right(player);
		else
			potencial = move_player_backward(player);        
	}
	else if (a && !d)
		potencial = move_player_left(player);
	else if (d && !a)
		potencial = move_player_right(player);
	//player->map_posi = vector_add(player->map_posi, potencial);
	handle_collisions(game, potencial);
}