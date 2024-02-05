/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:37:43 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 12:37:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	raycasting(t_game *game);

void		game_render(t_game *game)
{
	t_pixel first = {300, 300, rgba(0, 0, 255, 255)};


	xpm_to_window(&game->win, game->teste, first, game->teste->width * 10, game->teste->height * 10);

	//exit(0);
	//raycasting(game);
	//render_compass(&game->win, &game->compass);
	//render_map_inside_compass(game);
	//render_player_inside_compass(game);




}