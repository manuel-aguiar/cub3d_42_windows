/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorcast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:52:50 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 21:52:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	int_swap(int *first, int *second)
{
	int swap;

	swap = *first;
	*first = *second;
	*second = swap;
}

void	float_swap(float *first, float *second)
{
	float swap;

	swap = *first;
	*first = *second;
	*second = swap;
}

void	vector_swap(t_vector *first, t_vector *second)
{
	t_vector swap;

	swap = *first;
	*first = *second;
	*second = swap;
}

typedef struct s_door
{
	t_vector	start;
	t_vector	end;
	float		dist_start;
	float		dist_end;
	int			height_left;
	int			height_right;
}	t_door;

void	door_cast(t_game *game)
{
	int w = game->win.width;
	int h = game->win.height;
	t_door		door;
	t_xpm_tex 	*tex;
	t_vector	rel_start;
	t_vector	rel_end;
	t_vector	transform_start;
	t_vector	transform_end;
	t_vector	dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);

	door.start = (t_vector){4.0f, 6.5f};
	door.end = (t_vector){5.0f, 6.5f};
	if (game->player.map_posi.y > door.start.y)
	{
		vector_swap(&door.start, &door.end);
	}
	//print_sorted_sprites(game);
	//exit(0);
	

	float invDet = 1.0 / (game->player.plane.x * dir.y - game->player.plane.y * dir.x);

		rel_start = vector_sub(door.start, game->player.map_posi);
		transform_start.x = (dir.y * rel_start.x - dir.x * rel_start.y);
		transform_start.y = (-game->player.plane.y * rel_start.x + game->player.plane.x * rel_start.y);
		transform_start = vector_multi(transform_start, invDet);

		rel_end = vector_sub(door.end, game->player.map_posi);
		transform_end.x = (dir.y * rel_end.x - dir.x * rel_end.y);
		transform_end.y = (-game->player.plane.y * rel_end.x + game->player.plane.x * rel_end.y);
		transform_end = vector_multi(transform_end, invDet);

		if (transform_end.y < 0 && transform_start.y < 0)
			return ;

		int screen_start_x = (int)((w / 2) * (1 + transform_start.x / transform_start.y));
		if (transform_start.y < 0)
			screen_start_x = (int)((w / 2) * (1 - transform_start.x / transform_start.y));
		int height_start = abs((int)(h * 1.0f / (transform_start.y))); 

		int screen_end_x = (int)((w / 2) * (1 + transform_end.x / transform_end.y));
		if (transform_end.y < 0)
			screen_end_x = (int)((w / 2) * (1 - transform_end.x / transform_end.y));
		int height_end = abs((int)(h * 1.0f / (transform_end.y))); 
		
		
		
		//calculate lowest and highest pixel to fill in current stripe
		int min_startY = -height_start / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_start.y);
		//if(min_startY < 0) min_startY = 0;
		int max_startY = height_start / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_start.y);
		//if(max_startY >= h) max_startY = h - 1;

		int min_endY = -height_end / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_end.y);
		//if(min_endY < 0) min_endY = 0;
		int max_endY = height_end / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_end.y);
		//if(max_endY >= h) max_endY = h - 1;

		if (screen_end_x < screen_start_x)
		{
			int_swap(&screen_start_x, &screen_end_x);
			int_swap(&height_start, &height_end);
			int_swap(&min_startY, &min_endY);
			int_swap(&max_startY, &max_endY);
			vector_swap(&transform_start, &transform_end);
		}
		tex = game->tex[DOOR_TEX];
		//calculate width of the sprite
		int drawStartX = screen_start_x;
		int drawEndX = screen_end_x;
		
		//draw left
		int lineHeight = max_startY - min_startY;
		double step_y = 1.0f * tex->width / lineHeight;
		double tex_position_y = 0;
		int texX = 0;
		
		if (drawStartX > 0 && drawStartX < w)
		{
			int y = min_startY;
			while (y++ < int_clamp(min_startY, 0, h - 1))
				tex_position_y += step_y;
			while (y < int_clamp(max_startY, 0, h - 1))
			{
				float shade = ft_fabs(transform_start.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
				int texY = (int)tex_position_y;
				tex_position_y += step_y;

				int color = tex->pixels[texX * tex->width + (tex->width - texY - 1)];
				color = add_shade(color, shade);
				game->win.set_pixel(&game->win, drawStartX, y, color);
				y++;
			}
		}
		(void)drawEndX;
		/*
		y = int_clamp(min_endY, 0, h - 1);

		if (drawEndX > 0 && drawEndX < w)
		{
			while (y < int_clamp(max_endY, 0, h - 1))
			{
				float shade = ft_fabs(transform_end.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
				int color = rgba(255,0,0,255);
				color = add_shade(color, shade);
				game->win.set_pixel(&game->win, drawEndX, y, color);
				y++;
			}
		}
		*/
		
		
		int x_width = drawEndX - drawStartX;
		
		float shade_start = ft_fabs(transform_start.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
		float shade_end = ft_fabs(transform_end.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);

		float delta_min_y = (float)(min_endY - min_startY) / (float)x_width;
		float delta_max_y = (float)(max_endY - max_startY) / (float)x_width;

		//printf("delta min %.3f, delta max %.3f min max start %d %d, min max end %d %d\n", delta_min_y, delta_max_y, min_startY, max_startY, min_endY, max_endY);

		int save_startX = drawStartX;

		(void)shade_start;
		(void)shade_end;
		(void)save_startX;

		int x = drawStartX;
		float min_y = min_startY;
		float max_y = max_startY;

		double step_x = 1.0f * tex->height / x_width;
		double tex_position_x = 0;
		while (x++ < 0)
		{
			tex_position_x += step_x;
			min_y += delta_min_y;
			max_y += delta_max_y;
		}
			
		while (x < drawEndX)
		{
			int texX = (int)tex_position_x;
			tex_position_x += step_x;

			
			//float perc = (x - save_startX) / x_width;
			int start_y = (int)min_y;
			int	end_y = (int)max_y;
			int lineHeight = end_y - start_y;
			if(x > 0 && x < w && lineHeight >= game->hori_rays[x].line_height)
			//if(x > 0 && x < w && distance > 0 && distance < game->hori_rays[drawStartX].perpWallDist)
			{
				
				double step_y = 1.0f * tex->width / lineHeight;
				double tex_position_y = 0;
				

				while (start_y++ < 0)
					tex_position_y += step_y;
				while (start_y < int_clamp(end_y, 0, h - 1))
				{
					float shade = ft_fabs(transform_start.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
					int texY = (int)tex_position_y;
					tex_position_y += step_y;

					int color = tex->pixels[texX * tex->width + (tex->width - texY - 1)];
					if (color != 255)
					{
						color = add_shade(color, shade);
						game->win.set_pixel(&game->win, x, start_y, color);
					}

					start_y++;
				}
			}
			//else
			//{
			//	printf("x %d, st y %d, end t %d , min hori %d, max hori %d\n",x, start_y, end_y, game->hori_rays[x].min_y, game->hori_rays[x].max_y);
			//}
			min_y += delta_min_y;
			max_y += delta_max_y;
			x++;
		}
		//printf("min max start %d %d, min max end %d %d\n", min_startY, max_startY, min_endY, max_endY);
		
		
		
		

		

		
		(void)tex;



		/*
		printf("min st %d, max st %d, min end %d max end %d\n", min_startY, max_startY, min_endY, max_endY);
		float delta_min_y = (float)(min_endY - min_startY) / x_width;
		float delta_max_y = (float)(max_endY - max_startY) / x_width;
		printf("cheguei aqui?\n");
		for(int x = drawStartX; x < drawEndX; x++)
		{
			int texX = (int)((x - (-x_width + screen_start_x)) * tex->width / x_width);
			if(x > 0 && x < w && min_startY > game->hori_rays[x].min_y && max_startY < game->hori_rays[x].max_y)
			{

				for(int y = min_startY; y < max_startY; y++) //for every pixel of the current stripe
				{
					float d = (y - game->player.pitch + (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_start.y)) - h / 2 + height_start / 2; //256 and 128 factors to avoid floats
					int texY = ((d * tex->height) / height_start);
					//(void)texX;
					//(void)texY;
					//(void)tex;

					int color = tex->pixels[(tex->height - texY - 1) * tex->width + texX]; //get current color from the texture

					if (color != 255)
					{
						color = add_shade(color, transform_start.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
						game->win.set_pixel(&game->win, x, y, color);
					}

				}
			}
			min_startY += (int)((float)min_startY + delta_min_y);
			max_startY += (int)((float)max_startY + delta_max_y);
      	}
		*/
}