/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_crouch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:13:44 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 20:13:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "player.h"

void    player_change_height(t_player *player)
{
    float target;
    int   up_down;

    target = player->base_z;
    if (player->hgt_state == HGT_PRONE)
        target = player->prone_z;
    if (player->hgt_state == HGT_CROUCH)
        target = player->crouch_z;
    if (player->hgt_state == HGT_JUMP)
        target = player->base_z;    //future change;
    if (player->cur_z >= target)
        up_down = -1;
    else
        up_down = 1;
    player->cur_z += up_down * player->hgt_sense * player->timer[CLOCK_MOVE].elapsed;
    if ((up_down == -1 && player->cur_z <= target) || (up_down == 1 && player->cur_z >= target))
        player->cur_z = target;
}