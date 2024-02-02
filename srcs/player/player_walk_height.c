/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_walk_height.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:25:40 by marvin            #+#    #+#             */
/*   Updated: 2024/02/02 14:25:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "player.h"

void	player_walk_height(t_player *player)
{
	float speed;

	if ((player->is_walking && player->hgt_state != HGT_JUMP))
	{
		speed = player->cur_move_multi;
		if (player->is_sprinting && player->hgt_state == HGT_NORMAL)
			speed *= player->sprint_move_multi;
		player->cur_walk_sense += 0.015f * speed * player->timer[CLOCK_MOVE].elapsed;
		printf("walk sense %.3f\n", player->cur_walk_sense);
		player->walk_z_mod += - sinf(player->cur_walk_sense) / (150 * ( 1 / speed));

		if (player->cur_walk_sense > 2 * MY_PI)
		{
			player->is_walking = false;
			player->walk_z_mod = 0;
		}
	}
	else
	{
		if (player->walk_z_mod > 0)
			player->walk_z_mod = float_clamp(player->walk_z_mod - 0.0005f * player->timer[CLOCK_MOVE].elapsed, 0,  player->walk_z_mod);
		else if (player->walk_z_mod < 0)
			player->walk_z_mod = float_clamp(player->walk_z_mod + 0.0005f * player->timer[CLOCK_MOVE].elapsed, player->walk_z_mod, 0);
		player->cur_walk_sense = 0;
	}
		
	printf("cur z is %.3f\n", player->cur_z);
}