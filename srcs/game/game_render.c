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

void	comp_map_render(t_game *game);
void	render_player_against_map(t_game *game);


void		game_render(t_game *game)
{
	//render_all_stuff
	comp_map_render(game);
	render_compass(&game->win, &game->compass);
	render_player_against_map(game);
	chatgpt_anticircle(&game->win, (t_pixel){1000, 500, ARGB(255,255,255,255)}, 10, ARGB(255,255,255,255));
	
}