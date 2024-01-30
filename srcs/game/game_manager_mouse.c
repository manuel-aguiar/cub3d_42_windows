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
	int buttons;

	buttons = game->mouse->buttons;
	if ((buttons >> BIT_AIM) & 1)
	{
		game->player.is_aiming = !game->player.is_aiming;
		game->mouse->buttons &= ~(1 << BIT_AIM);
	}
		
}