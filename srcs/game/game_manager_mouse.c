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
	game->player.is_aiming = ((buttons >> BIT_AIM) & 1);
}