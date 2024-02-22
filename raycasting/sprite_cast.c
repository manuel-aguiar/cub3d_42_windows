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
		printf("sprite %d, dist %.10f, posi (%.3f, %.3f)", game->sprites[i].type, game->sprites[i].dist, game->sprites[i].posi.x, game->sprites[i].posi.y);
		printf("cur_z %.3f, height %.3f, width %.3f, \n", game->sprites[i].cur_z, game->sprites[i].height, game->sprites[i].width);
		i++;
	}
}

void	sprite_cast(t_game *game)
{
	int	i;
	int w = game->win.width;
	int h = game->win.height;
	t_xpm_tex 	*tex;
	t_vector	sprite_rel;
	t_vector	transform;
	t_vector	dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].type == DOOR)
			doorcast(game, &game->sprites[i]);
		else
		{
			float invDet = 1.0 / (game->player.plane.x * dir.y - game->player.plane.y * dir.x);
		
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
			int spriteWidth = abs( (int) (w * game->sprites[i].unit_size * 2 / (transform.y)));
			int drawStartX = -spriteWidth / 2 + spriteScreenX;
			if(drawStartX < 0) drawStartX = 0;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
			if(drawEndX >= w) drawEndX = w - 1;
			//printf("first stripe let's go\n");
			for(int x = drawStartX; x < drawEndX; x++)
			{
				int texX = (int)((x - (-spriteWidth / 2 + spriteScreenX)) * tex->height / spriteWidth);
				if (game->sprites[i].inverted)
					texX = (tex->width - texX - 1);
				//the conditions in the if are:
				//1) it's in front of camera plane so you don't see things behind you
				//2) it's on the screen (left)
				//3) it's on the screen (right)
				//4) ZBuffer, with perpendicular distance
				if(transform.y > 0 && x > 0 && x < w && transform.y < game->hori_rays[x].perpWallDist)
				{
					//printf("visible\n");
					for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
					{
					float d = (y - game->player.pitch + (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod + game->sprites[i].height - game->sprites[i].cur_z) * h - h / 2) / transform.y)) - h / 2 + spriteHeight / 2; //256 and 128 factors to avoid floats
					int texY = ((d * tex->width) / spriteHeight);

					int color = tex->pixels[texX * tex->width + (tex->width - texY - 1)]; //get current color from the texture
					//if (game->sprites[i].type == MEDIKIT)
					//{
					//	printf("x %d y %d, color %d, width %d height %d, index %d len %d\n", 
					//	texX, texY , color,tex->width, tex->height, texY * tex->width + (tex->width - texX - 1), tex->width* tex->height );
					//}
					
					//int color = rgba(0,0,255,255);
					if (color != 255)
					{
						color = add_shade(color, transform.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
						game->win.set_pixel(&game->win, x, y, color);
					}

					}
				}
				//else
				//	printf("not visible\n");
			}
					//if (game->sprites[i].type == MEDIKIT)
					//	exit(0);
			
		}
		i++;
	}
}