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
	float cos_ray;
	float sin_ray;

	player->angle = new_rad_angle;
	player->cos_rad = cosf(player->angle);
	player->sin_rad = sinf(player->angle);
	player->centre = player->st_centre;
	player->left = player->st_left;
	player->right = player->st_right;
	player->front = player->st_front;
	player->centre.x += (int)(player->total_x_diff);
	player->left.x += (int)(player->total_x_diff);
	player->right.x += (int)(player->total_x_diff);
	player->front.x += (int)(player->total_x_diff);
	player->centre.y += (int)(player->total_y_diff);
	player->left.y += (int)(player->total_y_diff);
	player->right.y += (int)(player->total_y_diff);
	player->front.y += (int)(player->total_y_diff);
	cos_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //cos (angle + PI / 4)
	sin_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //sin (angle + PI / 4)
	rotate_point(&player->right, player->centre, cos_ray, sin_ray);
	cos_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //cos (angle - PI / 4)
	sin_ray = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;  //sin (angle - PI / 4)
	rotate_point(&player->left, player->centre, cos_ray, sin_ray);
	rotate_point(&player->front, player->centre, player->cos_rad, player->sin_rad);
	//printf("new angle is %d\n", (int)(player->angle * 180 / P_MY_PI));
}