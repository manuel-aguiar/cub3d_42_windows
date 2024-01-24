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
	t_pixel	centre;

	centre = game->compass.map_centre;
	t_pixel	low_bot = (t_pixel){0, 0, ARGB(255,255,255,255)};
	t_pixel	hi_top = (t_pixel){game->win.width, game->win.height, ARGB(255,255,255,255)};

	

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

void	render_player_against_map(t_game *game)
{
	t_posi		new_position;
	t_pixel 	centre;
	t_pixel		pivot;
	t_player	*player;
	t_pixel 	low_bot = (t_pixel){0, 0, ARGB(255,255,255,255)};
	t_pixel 	hi_top = (t_pixel){game->win.width, game->win.height, ARGB(255,255,255,255)};
	t_pixel 	render[2];

	player = &game->player;

	new_position = player->map_posi;
	new_position.x += player->total_x_diff;
	new_position.y += player->total_y_diff;

	int		sqr_hgt;
	int		centre_index;

	sqr_hgt = game->compass.sqr_height;
	centre_index = game->map.len / 2;
	centre = game->compass.map_centre;

	centre.x += (int)((new_position.x - centre_index / game->map.height) * sqr_hgt);  //normalizing player position against square size
	centre.y += (int)((new_position.y - centre_index / game->map.width + 1) * sqr_hgt);	//normalizing player position against square size

	float cos_ray;
	float sin_ray;	

	// rendering line in front of player
	pivot = centre;
	pivot.x += player->pix_radius;
	rotate_point(&pivot, centre, player->cos_rad, player->sin_rad);
	if (liang_barsky_clipper(low_bot, hi_top, centre, pivot, render))
		xiaolinwu_line(&game->win, render[0], render[1]);

	// rendering line to the left;

	pivot = centre;
	pivot.x += player->pix_radius;
	cos_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //cos (angle - PI / 4)
	sin_ray = P_SQRT_OF_TWO_OVER_TWO * player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad;  //sin (angle - PI / 4)
	rotate_point(&pivot, centre, cos_ray, sin_ray);
	if (liang_barsky_clipper(low_bot, hi_top, centre, pivot, render))
		xiaolinwu_line(&game->win, render[0], render[1]);

	// rendering line to the right;

	pivot = centre;
	pivot.x += player->pix_radius;
	cos_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //cos (angle + PI / 4)
	sin_ray = P_SQRT_OF_TWO_OVER_TWO * player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad;  //sin (angle + PI / 4)
	rotate_point(&pivot, centre, cos_ray, sin_ray);
	if (liang_barsky_clipper(low_bot, hi_top, centre, pivot, render))
		xiaolinwu_line(&game->win, render[0], render[1]);

}