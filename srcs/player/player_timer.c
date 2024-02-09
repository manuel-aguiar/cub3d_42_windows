/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_timer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:14:18 by marvin            #+#    #+#             */
/*   Updated: 2024/02/09 19:14:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "player.h"

void	player_start_timers(t_player *player)
{
	int i;

	i = 0;
	while (i < CLOCK_SIZE)
	{
		ftime(&player->timer[i].start);
		i++;
	}
}

void	player_get_timer(t_player *player, e_clocks timer)
{
	if (timer > CLOCK_SIZE)
		return ;
	ftime(&player->timer[timer].end);
	player->timer[timer].elapsed = (size_t) (1000.0 * (player->timer[timer].end.time - player->timer[timer].start.time)
	+ (player->timer[timer].end.millitm - player->timer[timer].start.millitm));
	player->timer[timer].start = player->timer[timer].end;
	if (timer == CLOCK_MOVE)
		printf("fps: %u\n", (size_t)(1000 / player->timer[CLOCK_MOVE].elapsed));
}