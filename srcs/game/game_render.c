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
	t_pixel first = {200, 200, rgba(0, 0, 255, 255)};
		
	xpm_to_window(&game->win, game->teste, first, 200, 200);

	//exit(0);
	//raycasting(game);
	//render_compass(&game->win, &game->compass);
	//render_map_inside_compass(game);
	//render_player_inside_compass(game);




}