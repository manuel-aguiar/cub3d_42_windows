/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:58:30 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 20:58:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void    rotate_player(t_player *player, float new_rad_angle)
{
	player->angle = new_rad_angle;
	player->cos_rad = cosf(player->angle);
	player->sin_rad = sinf(player->angle);
}