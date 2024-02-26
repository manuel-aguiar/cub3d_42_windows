/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager_mouse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:52:57 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 13:52:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	game_mouse_manager(t_game *game)
{
	game->player.is_aiming = ((game->mouse->buttons >> BIT_AIM) & 1);
	if (((game->mouse->buttons >> BIT_SHOOT) & 1))
	{
		if (game->player.ammo[CTR_CUR] > 0)
		{
			shot_raycasting(game, game->player.dir_vec);
			game->player.ammo[CTR_CUR]--;
		}
		game->mouse->buttons &= ~(1 << BIT_SHOOT);
	}
}