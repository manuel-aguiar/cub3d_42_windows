/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:44:15 by marvin            #+#    #+#             */
/*   Updated: 2024/02/02 14:44:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	player_rotate_and_pitch(t_game *game)
{
	float rotate;
	float rotate_aim_multi;
	float pitch;

	rotate_aim_multi = 1;
	if (game->player.is_aiming)
		rotate_aim_multi = game->player.aim_rot_multi;

	rotate = game->win.width / 2 - game->mouse->cur_x;
	game_rotate_view_angle(game, rotate * game->player.rot_sense * rotate_aim_multi * game->player.timer[CLOCK_MOVE].elapsed);


	pitch = ((game->mouse->cur_y - game->win.height / 2) * game->player.verti_sense * rotate_aim_multi * game->player.timer[CLOCK_MOVE].elapsed);
	if (pitch != 0)
	{
		game->player.verti_angle = float_clamp(game->player.verti_angle + pitch, game->player.verti_min, game->player.verti_max);
		game->player.verti_tan = tanf(game->player.verti_angle);
		game->player.pitch = (int)(game->player.cur_dir_len / game->player.base_dir_len * game->player.verti_tan * game->win.height / 2);
	}
}