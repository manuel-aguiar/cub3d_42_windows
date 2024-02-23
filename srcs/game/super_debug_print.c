/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_debug_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:46:40 by marvin            #+#    #+#             */
/*   Updated: 2024/02/09 20:46:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"


void	print_hori_rays(t_game *game)
{
	int i;
	int width;

	i = 0;
	width = game->win.width;
	printf("hello\n");
	while (i < width)
	{
		printf("x %d, min_y %d, max_y %d, dist %.3f, side %d, lineheight %d\n",
		i,
		game->hori_rays[i].min_y,
		game->hori_rays[i].max_y,
		game->hori_rays[i].wall_dist,
		game->hori_rays[i].side,
		game->hori_rays[i].line_h
		);
		i++;
	}
}

void	super_debug_print(t_game *game)
{
	print_hori_rays(game);
}