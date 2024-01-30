/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:57:01 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 15:57:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"


# define JUMP_END 1000
# define JUMP_FLIGHT 800
# define JUMP_DIP 200

# define JUMP_Z_TOP 80
# define JUMP_Z_BOT -20

# define TOTAL_JUMP_TIME

size_t	calc_elapsed(t_player *player, int timer)
{
	struct timeb  	cur;
	if (timer > CLOCK_SIZE)
		return (-1);
	ftime(&cur);
	return ((size_t) (1000.0 * (cur.time - player->timer[timer].start.time)
	+ (cur.millitm - player->timer[timer].start.millitm)));
}

/*
https://jsfiddle.net/LyM87/
*/

/*
void player_jump_cur_z(t_player *player)
{
	size_t elapsed;
	int jump_middle;

	elapsed = calc_elapsed(player, CLOCK_JUMP);
	if (elapsed > TOTAL_JUMP_TIME)
	{
		player->z_height = 0;
		player->is_jumping = false;
	}
	else
	{
		player->z_height = JUMP_Z_TOP ;
	}
	printf("elapsed %u\n", elapsed);
	if (!player->is_jumping)
		return ;
	
	if (elapsed < JUMP_DIP)
	{
		printf("start at %u\n", elapsed);
		jump_middle = (JUMP_DIP - 0) / 2;
		int sqr = (elapsed - jump_middle) * (elapsed - jump_middle) / ft_abs(elapsed - jump_middle);
		player->z_height = -(sqr - JUMP_Z_BOT);
	}
	else if (elapsed < JUMP_FLIGHT)
	{
		printf("middle at %u\n", elapsed);
		elapsed -= JUMP_DIP;
		jump_middle = JUMP_FLIGHT / 2;
		int sqr = (elapsed - jump_middle) * (elapsed - jump_middle) / ft_abs(elapsed - jump_middle);
		player->z_height = -(-sqr + JUMP_Z_TOP);
	}
	else if (elapsed < JUMP_END)
	{
		printf("end at %u\n", elapsed);
		elapsed -= (JUMP_DIP + JUMP_FLIGHT);
		jump_middle = (JUMP_END - 0) / 2;
		int sqr = (elapsed - jump_middle) * (elapsed - jump_middle) / ft_abs(elapsed - jump_middle);
		player->z_height = -(sqr - JUMP_Z_BOT);
	}
	else
	{
		printf("landed at %u\n", elapsed);
		player->z_height = 0;
		player->is_jumping = false;
	}
	printf("player z is %d\n", player->z_height);

}

	*/