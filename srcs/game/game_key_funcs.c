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
	if (radian >= 2)
		return (0 + (float)(radian - 2));
	if (radian < -2)
		return (0 + (float)(radian + 2));
	return (radian);
}

int	game_rotate_view_angle(t_game *game, float diff)
{
	game->player_angle_rad = radian_truncate(game->player_angle_rad + diff);
	set_compass_angle(&game->compass, game->player_angle_rad);
}