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

void	game_key_manager(t_game *game)
{
	int keys;

	keys = *game->keys;
	move_player(game, (keys >> BIT_FRONT) & 1, (keys >> BIT_BACK) & 1, (keys >> BIT_LEFT) & 1, (keys >> BIT_RIGHT) & 1);
}