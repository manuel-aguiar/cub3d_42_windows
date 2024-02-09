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

# include "game.h"

void    player_setup(t_player *player)
{
	player->is_aiming = false;
	player->is_sprinting = false;
	player->is_walking = false;
	player->plane = vector_multi((t_vector){player->sin_rad, -player->cos_rad}, player->cur_fov);
}

void	player_actions(t_game *game)
{
		t_player *player;

		player = &game->player;
		player_change_aim(player);
		player_change_stance(player);
		player_jump_gravity(player);
		player_walk_height(player);
		player_rotate_and_pitch(game);
}