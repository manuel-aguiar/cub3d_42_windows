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

void	player_start_timers(t_player *player);
void	player_get_timer(t_player *player, int timer);

void	dda_visible(t_game *game);
void	wallcast_dda_visible(t_game *game);
void	floorcast_dda_visible(t_game *game);

void		game_render(t_game *game)
{
	//t_pixel first = {300, 300, rgba(0, 0, 255, 255)};

	//player_start_timers(&game->player);
	//xpm_to_window(&game->win, game->tex[NO_TEX], first, game->tex[NO_TEX]->width, game->tex[NO_TEX]->height);
	//dda_visible(game);
	//floorcast_dda_visible(game);
	//wallcast_dda_visible(game);
	floorcast(game);
	wallcast(game);
	render_compass(&game->win, &game->compass);
	render_map_inside_compass(game);
	render_player_inside_compass(game);

}