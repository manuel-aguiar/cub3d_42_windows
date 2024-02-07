/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:23:32 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 19:23:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "player.h"

void    player_setup(t_player *player)
{
	player->is_aiming = false;
	player->is_jumping = false;
	player->hgt_state = HGT_NORMAL;
	player->plane = vector_multi((t_vector){player->sin_rad, -player->cos_rad}, player->cur_fov);
}
