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
void	in_comp_render(t_game *game);
void	in_player_render(t_game *game);

void	raycasting(t_game *game);

void		game_render(t_game *game)
{
	//render_all_stuff
	//raycasting(game);
	render_compass(&game->win, &game->compass);
	
	//comp_map_render(game);
	render_player_against_map(game);

	in_comp_render(game);
	in_player_render(game);
	//render_player_against_map(game);
	
}