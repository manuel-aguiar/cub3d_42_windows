/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:11:13 by marvin            #+#    #+#             */
/*   Updated: 2024/01/29 10:11:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"



void	wallcast_dda_visible(t_game *game)
{
	float cameraX;
	int w = game->win.width;
	int h = game->win.height;
	t_vector	dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);	//for zooming, increase direction vector
	t_vector 	plane = game->player.plane;
	int		x;


	t_vector direction;

	x = 0;
	while (x < w)
	{
		cameraX = 2 * x / (float)w - 1;
		direction = (t_vector){dir.x + plane.x * cameraX, dir.y + plane.y * cameraX};
		//printf("perpwalldist %.3f\n", perpWallDist);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / game->hori_rays[x].perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = game->hori_rays[x].min_y;
		int drawEnd = game->hori_rays[x].max_y;

		double wallX; //where exactly the wall was hit
		if (game->hori_rays[x].side == 0) wallX = game->player.map_posi.y + game->hori_rays[x].perpWallDist * direction.y;
		else           wallX = game->player.map_posi.x + game->hori_rays[x].perpWallDist * direction.x;
		//if (x == game->win.width / 2)
		//	printf("prefloor wallX is %.10f\n", wallX);
		wallX -= floor((wallX));
		//if (x == game->win.width / 2)
		//	printf("wallX is %.10f, player map (%.3f,%.3f)\n", wallX, player_in_map.x, player_in_map.y);
		//x coordinate on the texture
		t_xpm_tex *tex;
		if (game->hori_rays[x].side == 0)
			tex = game->tex[NO_TEX];
		else
			tex = game->tex[SO_TEX];

		int texX = (int)(wallX * (double)(tex->height));
		//if (x == game->win.width / 2)
		//	printf("texX is %d\n", texX);
		if(game->hori_rays[x].side == 0 && direction.x > 0) texX = (tex->height) - texX - 1;
		if(game->hori_rays[x].side == 1 && direction.y < 0) texX = (tex->height) - texX - 1;

		//texX = (int)((float)texX / (float)tex->width * (float)tex->height);
		//if (side == 1 && x == game->win.width / 2)
		//	printf("texX is %d\n", texX);
		
		double step = 1.0f * tex->width / lineHeight;
		double texPos = (drawStart - h / 2 - game->player.pitch + ((int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2)/ game->hori_rays[x].perpWallDist)) + lineHeight / 2) * step;

		int y = drawStart;
		while( y < drawEnd)
		{
			int texY = (int)texPos;
			texPos += step;
			//if (side == 1 && x == game->win.width / 2)
			//{
			//	printf("x %d y %d pixel %d\n", texX, texY, tex->pixels[texX * tex->width + (tex->width - texY - 1)]);
			//}
			int color = tex->pixels[texX * tex->width + (tex->width - texY - 1)];
			color = add_shade(color, game->hori_rays[x].perpWallDist / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
			game->win.set_pixel(&game->win, x, y, color);
			y++;
		}
		//if (side == 1 && x == game->win.width / 2)
		//{
		//	int k = 0;
		//	while (k < tex->width * tex->height)
		//	{
		//		printf("%d pixel x %d, y %d %d\n", k, k / tex->width, k % tex->width, tex->pixels[k]);
		//		k++;
		//	}
		//	exit(0);
		//}
		
		//draw_vertical_line(&game->win, drawStart, drawEnd, x, color);
		x++;
	}
	//exit (0);
}
