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
	
	if ((keys >> BIT_JUMP) & 1)
	{
		if (game->player.hgt_state != HGT_JUMP)
			game->player.cur_jump_sense = 0.003f;
		else
			game->player.cur_jump_sense += 0.00001f;
		game->player.hgt_state = HGT_JUMP;
		if(game->player.cur_jump_sense > 0.007f)
			game->player.cur_jump_sense = 0.007f;

	}
	if (!((keys >> BIT_JUMP) & 1) && game->player.hgt_state == HGT_JUMP)
	{
		if(game->player.cur_jump_sense > 0.002f)
			game->player.cur_jump_sense = 0.002f;
	}
	/*
	if (game->player.hgt_state == HGT_PRONE)
	{
		if ((keys >> BIT_CROUCH) & 1)
			game->player.hgt_state = HGT_CROUCH;
		else if (((keys >> BIT_PRONE) & 1) || ((keys >> BIT_JUMP) & 1))
		{
			game->player.hgt_state = HGT_NORMAL;
			printf("prone back to normal\n");
		}		
	}
	else if (game->player.hgt_state == HGT_CROUCH)
	{
		if ((keys >> BIT_PRONE) & 1)
			game->player.hgt_state = HGT_PRONE;
		else if (((keys >> BIT_CROUCH) & 1) || ((keys >> BIT_JUMP) & 1))
			game->player.hgt_state = HGT_NORMAL;
	}
	else if (game->player.hgt_state == HGT_NORMAL)
	{
		if ((keys >> BIT_PRONE) & 1)
			game->player.hgt_state = HGT_PRONE;
		else if (((keys >> BIT_CROUCH) & 1))
			game->player.hgt_state = HGT_CROUCH;
		else if (((keys >> BIT_JUMP) & 1))
			game->player.hgt_state = HGT_JUMP;
	}
	else if (game->player.hgt_state == HGT_JUMP)
	{
		game->player.hgt_state = HGT_NORMAL;
	}
	*/
	*game->keys &= ~(1 << BIT_CROUCH);
	*game->keys &= ~(1 << BIT_PRONE);
	*game->keys &= ~(1 << BIT_CROUCH);
	*game->keys &= ~(1 << BIT_PRONE);
}