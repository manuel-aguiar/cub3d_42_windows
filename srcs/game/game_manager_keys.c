/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_key_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:43:50 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:43:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	player_set_timer(t_player * player, int timer)
{
	if (timer > CLOCK_SIZE)
		return ;
	ftime(&player->timer[timer].start);
}

void	game_key_manager(t_game *game)
{
	int keys;

	keys = *game->keys;
	move_player(game, (keys >> BIT_FRONT) & 1, (keys >> BIT_BACK) & 1, (keys >> BIT_LEFT) & 1, (keys >> BIT_RIGHT) & 1);
	if ((keys >> BIT_JUMP) & 1 && !game->player.is_jumping)
	{
		game->player.is_jumping = true;
		player_set_timer(&game->player, CLOCK_JUMP);
	}
}