/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:01:40 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 12:01:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_game(t_game *game)
{
	int i;
	free_win_glfw(&game->win);
	free_compass(&game->compass);
	free_map(&game->map);
	i = 0;
	while (i < NUM_TEX)
	{
		if (game->tex[i])
			xpm_tex_free(game->tex[i]);
		i++;
	}
}