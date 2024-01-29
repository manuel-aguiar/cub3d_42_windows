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
	raycasting(game);
	render_compass(&game->win, &game->compass);
	//
	//render_map_outside_compass(game);
	//render_player_outside_compass(game);
//
	render_map_inside_compass(game);
	render_player_inside_compass(game);

	//t_pixel first = {500, 1000, rgba(0, 0, 255, 255)};
	//render_inner_square(win, comp, first);
	//
	//t_pixel second = {1200, 900, rgba(255, 0, 0, 255)};
	//xiaolinwu_line(&game->win, first, second);

}