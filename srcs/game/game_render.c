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

void		game_render(t_game *game)
{
	//t_pixel first = {300, 300, rgba(0, 0, 255, 255)};

	//player_start_timers(&game->player);

	//xpm_to_window(&game->win, game->tex[NO_TEX], first, game->tex[NO_TEX]->width * 10 , game->tex[NO_TEX]->height * 10);


	//player_get_timer(&game->player, CLOCK_MOVE);
	//printf("dementor elapsed: %u\n", game->player.timer[CLOCK_MOVE].elapsed);

	//exit(0);
	//exit(0);
	raycasting(game);
	render_compass(&game->win, &game->compass);
	render_map_inside_compass(game);
	render_player_inside_compass(game);




}