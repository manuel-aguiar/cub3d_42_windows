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

void	xlim_square_vs_rectangle(t_win_glfw *win, t_compass *comp, t_pixel centre, t_pixel low_bot, t_pixel hi_top);

void	comp_map_render(t_game *game)
{
	t_pixel	sqr_centre;
	int		sqr_hgt;
	int		i;
	int		centre_index;

	t_pixel	centre = (t_pixel){1000, 500, ARGB(255,255,255,255)};
	t_pixel	low_bot = (t_pixel){0, 0, ARGB(255,255,255,255)};
	t_pixel	hi_top = (t_pixel){WIN_WIDTH, WIN_HEIGHT, ARGB(255,255,255,255)};

	

	sqr_hgt = game->compass.sqr_height;
	centre_index = game->map.len / 2;
	//printf("centre index %d center row %d, centre col %d\n", centre_index, centre_index / game->map.width, centre_index % game->map.height);
	i = 0;
	while (i < game->map.len)
	{
		if (game->map.map[i] == '1')
		{
			sqr_centre = centre;
			sqr_centre.x += (i % game->map.width - centre_index / game->map.height) * sqr_hgt;
			sqr_centre.y += (i / game->map.width - centre_index / game->map.width) * sqr_hgt;
			//printf("sqr (%d, %d), x %d, y %d\n", i % game->map.width, i / game->map.width, sqr_centre.x, sqr_centre.y);
			// rotate sqr_center around map center using compass angle (later change to player angle)
			xlim_square_vs_rectangle(&game->win, &game->compass, sqr_centre, low_bot, hi_top);
		}
		i++;
	}
}