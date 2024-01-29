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
	player->move_sense = 0.01f;
	player->unit_size = 0.2f;
	player->pitch = 0;
	player->z_height = 0;
	player->plane = vector_multi((t_vector){player->sin_rad, -player->cos_rad}, 0.66f);
}
