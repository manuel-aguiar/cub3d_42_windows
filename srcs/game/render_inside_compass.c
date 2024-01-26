/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_comp_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:32:06 by marvin            #+#    #+#             */
/*   Updated: 2024/01/25 15:32:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	render_map_inside_compass(t_game *game)
{
	t_pixel	sqr_centre;
	int		sqr_hgt;
	int		i;
	int		centre_index;
	t_pixel	centre;

	centre = game->compass.centre;

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

			sqr_centre.x -= (int)((game->player.map_posi.x - centre_index / game->map.height -  0.5f) * sqr_hgt);
			sqr_centre.y -= (int)((game->player.map_posi.y - centre_index / game->map.width -  0.5f) * sqr_hgt);

			rotate_point(&sqr_centre, centre, -game->compass.sin_rad, -game->compass.cos_rad);
			render_square_vs_circle(&game->win, &game->compass, sqr_centre);
		}
		i++;
	}
}

void	render_player_inside_compass(t_game *game)
{
	int			sqr_hgt;
	t_pixel 	centre;
	t_pixel		pivot;
	t_player	*player;
	t_pixel 	low_bot = (t_pixel){0, 0, rgba(255,255,255,255)};
	t_pixel 	hi_top = (t_pixel){game->win.width, game->win.height, rgba(255,255,255,255)};
	t_pixel 	render[2];

	player = &game->player;

	

	sqr_hgt = game->compass.sqr_height;
	centre = game->compass.centre;

	centre.colour = pivot.colour = rgba(255,255,255,255);

	float cos_ray;
	float sin_ray;	

	float cos_ninety;
	float sin_ninety;

	// rendering line in front of player
	pivot = centre;
	pivot.colour = rgba(255,255,255,255);
	pivot.y += (int)(player->unit_size * sqr_hgt * 6);												//6 just because
	if (liang_barsky_clipper(low_bot, hi_top, centre, pivot, render))
		xiaolinwu_line(&game->win, render[0], render[1]);

	// rendering line to the left;

	cos_ninety = 1;
	sin_ninety = 0;

	pivot = centre;
	pivot.colour = rgba(255,255,255,255);
	pivot.y += (int)(player->unit_size * sqr_hgt * 6);												//6 just because
	cos_ray = P_SQRT_OF_TWO_OVER_TWO * cos_ninety + P_SQRT_OF_TWO_OVER_TWO * sin_ninety;  //cos (angle - PI / 4)
	sin_ray = P_SQRT_OF_TWO_OVER_TWO * sin_ninety - P_SQRT_OF_TWO_OVER_TWO * cos_ninety;  //sin (angle - PI / 4)
	rotate_point(&pivot, centre, cos_ray, sin_ray);
	if (liang_barsky_clipper(low_bot, hi_top, centre, pivot, render))
		xiaolinwu_line(&game->win, render[0], render[1]);

	// rendering line to the right;

	pivot = centre;
	pivot.colour = rgba(255,255,255,255);
	pivot.y += (int)(player->unit_size * sqr_hgt * 6);												//6 just because
	cos_ray = P_SQRT_OF_TWO_OVER_TWO * cos_ninety - P_SQRT_OF_TWO_OVER_TWO * sin_ninety;  //cos (angle + PI / 4)
	sin_ray = P_SQRT_OF_TWO_OVER_TWO * cos_ninety + P_SQRT_OF_TWO_OVER_TWO * sin_ninety;  //sin (angle + PI / 4)
	rotate_point(&pivot, centre, cos_ray, sin_ray);
	if (liang_barsky_clipper(low_bot, hi_top, centre, pivot, render))
		xiaolinwu_line(&game->win, render[0], render[1]);
	
	render_empty_circle_with_aa(&game->win, centre, (int)(player->unit_size * sqr_hgt), rgba(255,255,255,255));

}