/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_key_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:24:38 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 12:24:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

float	radian_truncate(float radian)
{
	if (radian >= 2 * P_MY_PI)
		return (0 + (float)(radian - 2 * P_MY_PI));
	if (radian < -2 * P_MY_PI)
		return (0 + (float)(radian + 2 * P_MY_PI));
	return (radian);
}

void	game_rotate_view_angle(t_game *game, float diff)
{
	game->player_angle_rad = radian_truncate(game->player_angle_rad + diff);
	//set_compass_angle(&game->compass, radian_truncate(game->player_angle_rad + P_MY_PI / 2));			//stop rotating to test
	game->player.angle = radian_truncate(game->player.angle + diff);							//limpar
	rotate_player(&game->player, game->player.angle);
}
