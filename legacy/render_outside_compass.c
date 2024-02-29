/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_map_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:13:30 by marvin            #+#    #+#             */
/*   Updated: 2024/01/24 10:13:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	render_map_outside_compass(t_game *game)
{
	t_pixel	sqr_centre;
	int		sqr_hgt;
	int		i;
	int		centre_index;
	t_pixel	centre;

	centre = game->compass.map_centre;
	t_pixel	low_bot = (t_pixel){0, 0, rgba(255,255,255,255)};
	t_pixel	hi_top = (t_pixel){game->win.width, game->win.height, rgba(255,255,255,255)};

	sqr_hgt = game->compass.sqr_height;
	centre_index = game->map.len / 2;
	i = 0;
	while (i < game->map.len)
	{
		if (game->map.map[i] == '1')
		{
			sqr_centre = centre;
			sqr_centre.x += (i % game->map.width - centre_index / game->map.height) * sqr_hgt;
			sqr_centre.y += (i / game->map.width - centre_index / game->map.width) * sqr_hgt;
			render_square_vs_rect(&game->win, &game->compass, sqr_centre, low_bot, hi_top);
		}
		i++;
	}
}

void	render_player_outside_compass(t_game *game)
{
	t_vec2d		new_position;
	t_pixel 	centre;
	t_player	*player;

	player = &game->player;

	new_position = player->map_posi;
	//new_position.y += player->total_y_diff;

	int		sqr_hgt;
	int		centre_index;

	sqr_hgt = game->compass.sqr_height;
	centre_index = game->map.len / 2;
	centre = game->compass.map_centre;

	centre.x += (int)((new_position.x - centre_index / game->map.height - 0.5f) * sqr_hgt);  //normalizing player position against square size
	centre.y += (int)((new_position.y - centre_index / game->map.width - 0.5f) * sqr_hgt);	//normalizing player position against square size


	
	render_empty_circle_with_aa(&game->win, centre, (int)(player->unit_size * sqr_hgt), rgba(255,255,255,255));

}