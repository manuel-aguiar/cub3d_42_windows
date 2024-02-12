/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:05:50 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 13:05:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	sprite_calc_dist(t_game *game)
{
	int i;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].status == GONE)
			game->sprites[i].dist = FLT_MAX;
		else
			game->sprites[i].dist = fpow_2(game->player.map_posi.x - game->sprites[i].posi.x) \
								 + fpow_2(game->player.map_posi.y - game->sprites[i].posi.y);
		i++;
	}
}

void	print_sorted_sprites(t_game *game)
{
	int i;

	i = 0;
	while (i < game->sprite_count)
	{
		printf("sprite %d, dist %.10f, posi (%.3f, %.3f)\n", game->sprites[i].type, game->sprites[i].dist, game->sprites[i].posi.x, game->sprites[i].posi.y);
		i++;
	}
}

void	sprite_cast(t_game *game)
{
	int	i;
	int w = game->win.width;
	int h = game->win.height;
	t_xpm_tex *tex;
	t_vector	sprite_rel;
	t_vector	transform;
	t_vector	dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);

	sprite_calc_dist(game);
	sprite_qs_distance(game->sprites, game->sprite_count, sprite_qs_comp);
	//print_sorted_sprites(game);
	//exit(0);
	float invDet = 1.0 / (game->player.plane.x * dir.y - game->player.plane.y * dir.x);
	i = 0;
	while (i < game->sprite_count)
	{
		tex = game->tex[game->sprites[i].tex];
		sprite_rel = vector_sub(game->sprites[i].posi, game->player.map_posi);
		transform.x = (dir.y * sprite_rel.x - dir.x * sprite_rel.y);
		transform.y = (-game->player.plane.y * sprite_rel.x + game->player.plane.x * sprite_rel.y);
		transform = vector_multi(transform, invDet);
		int spriteScreenX = (int)((w / 2) * (1 + transform.x / transform.y));
		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(h * game->sprites[i].height / (transform.y))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod + game->sprites[i].height - game->sprites[i].cur_z) * h - h / 2) / transform.y);
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod + game->sprites[i].height - game->sprites[i].cur_z) * h - h / 2) / transform.y);
		if(drawEndY >= h) drawEndY = h - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (h / (transform.y)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= w) drawEndX = w - 1;
		//printf("first stripe let's go\n");
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((stripe - (-spriteWidth / 2 + spriteScreenX)) * tex->width / spriteWidth);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transform.y > 0 && stripe > 0 && stripe < w && transform.y < game->hori_rays[stripe].perpWallDist)
			{
				//printf("visible\n");
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
				int d = (y) - h + spriteHeight; //256 and 128 factors to avoid floats
				int texY = ((d * tex->height) / spriteHeight);
				(void)texX;
				(void)texY;
				(void)tex;
				//int color = tex->pixels[texX * tex->width + (tex->width - texY - 1)]; //get current color from the texture
				int color = rgba(0,0,255,255);
				if (color != 255)
				{
					color = add_shade(color, transform.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
					game->win.set_pixel(&game->win, stripe, y, color);
				}
				
				}
			}
			//else
			//	printf("not visible\n");
      	}

		i++;
	}
}