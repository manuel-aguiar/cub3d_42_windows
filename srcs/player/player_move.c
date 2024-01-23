/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:30:57 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 19:30:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void    move_player_back_left(t_player *player)
{
    float cos_plus_45;
    float sin_plus_45;

    cos_plus_45 = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
    sin_plus_45 = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
    player->total_x_diff -= (player->move_sense * cos_plus_45);
    player->total_y_diff += (player->move_sense * sin_plus_45);
}

void    move_player_back_right(t_player *player)
{
    float cos_minus_45;
    float sin_minus_45;

    cos_minus_45 = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
    sin_minus_45 = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
    player->total_x_diff -= (player->move_sense * cos_minus_45);
    player->total_y_diff += (player->move_sense * sin_minus_45);
}

void    move_player_for_left(t_player *player)
{
    float cos_minus_45;
    float sin_minus_45;

    cos_minus_45 = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
    sin_minus_45 = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
    player->total_x_diff += (player->move_sense * cos_minus_45);
    player->total_y_diff -= (player->move_sense * sin_minus_45);
}

void    move_player_for_right(t_player *player)
{
    float cos_plus_45;
    float sin_plus_45;

    cos_plus_45 = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;
    sin_plus_45 = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;
    player->total_x_diff += (player->move_sense * cos_plus_45);                   //wait till overflow maybe...?
    player->total_y_diff -= (player->move_sense * sin_plus_45);
}

void    move_player_left(t_player *player)
{
    player->total_x_diff += -(player->move_sense * -player->sin_rad);
    player->total_y_diff += -(player->move_sense * -player->cos_rad);
}

void    move_player_right(t_player *player)
{
    player->total_x_diff += (player->move_sense * -player->sin_rad);
    player->total_y_diff += (player->move_sense * -player->cos_rad);
}


void    move_player_backward(t_player *player)
{
    //printf("angle %d, backward delta x %f, delta y %f\n", (int)(player->angle * 180 / P_MY_PI), -(player->move_sense * player->cos_rad), (player->move_sense * player->sin_rad));
    player->total_x_diff -= (player->move_sense * player->cos_rad);
    player->total_y_diff += (player->move_sense * player->sin_rad);
}

void    move_player_forward(t_player *player)
{
    //printf("angle %d, forward delta x %f, delta y %f\n", (int)(player->angle * 180 / P_MY_PI), (player->move_sense * player->cos_rad), -(player->move_sense * player->sin_rad));
    player->total_x_diff += (player->move_sense * player->cos_rad);              
    player->total_y_diff -= (player->move_sense * player->sin_rad);
}


void    move_player(t_player *player, bool w, bool s, bool a, bool d)
{
	float cos_ray;
	float sin_ray;

    if (w && !s)
    {
        if (a && !d)
            move_player_for_left(player);
        else if (d && !a)
            move_player_for_right(player);
        else
            move_player_forward(player);
    }
    else if (s && !w)
    {
        if (a && !d)
            move_player_back_left(player);
        else if (d && !a)
            move_player_back_right(player);
        else
            move_player_backward(player);        
    }
    else if (a && !d)
        move_player_left(player);
    else if (d && !a)
        move_player_right(player);
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
}