/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_visible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:58:16 by marvin            #+#    #+#             */
/*   Updated: 2024/02/08 11:58:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	dda_visible(t_game *game)
{
	float cameraX;
	int w = game->win.width;
	int h = game->win.height;
	t_vector	dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);	//for zooming, increase direction vector
	t_vector 	plane = game->player.plane;
	int		x;

	t_vector	ray_start;
	t_vector	ray_first;
	t_vector	ray_step;
	t_vector	axis_move;
	t_vector	player_in_map;
	player_in_map = (t_vector){(float)((int)game->player.map_posi.x), (float)((int)game->player.map_posi.y)};
	ray_start = game->player.map_posi;
	//ft_memset(game->visible, 0, game->map.width * game->map.height * sizeof(*game->visible));
	//printf("memset done\n");
	//game->visible[(int)player_in_map.x + game->map.width * (int)player_in_map.y] = true;
	t_vector direction;
	int side;
	game->minmax_hori = game->win.height;
	game->maxmin_hori = 0;
	x = 0;
	while (x < w)
	{
		cameraX = 2 * x / (float)w - 1;

		direction = (t_vector){dir.x + plane.x * cameraX, dir.y + plane.y * cameraX};
		//printf("player at (%.3f, %.3f), player dir (%.3f, %.3f), direction (%.3f, %.3f)\n", 
		//game->player.map_posi.x, game->player.map_posi.y, 
		//game->player.dir_vec.x,
		//game->player.dir_vec.y,
		//
		//direction.x, direction.y);
		ray_step = (t_vector){direction.x == 0 ? FLT_MAX : ft_fabs(1.0f / direction.x), direction.y == 0 ? FLT_MAX : ft_fabs(1.0f / direction.y)};
		player_in_map = (t_vector){(float)((int)game->player.map_posi.x), (float)((int)game->player.map_posi.y)};
		//
		//attempt tto add sway horizontally!!!!
		//player_in_map = vector_add(player_in_map, vector_multi(game->player.plane, game->player.walk_z_mod / 200));
		
		
		
		
		//printf("ray step at (%.3f, %.3f)\n", ray_step.x, ray_step.y);
		// first step before constant multiplier, getting move in x axis and y axis
		if (direction.x < 0)
		{
			axis_move.x = -1;
			ray_first.x = (ray_start.x - player_in_map.x) * ray_step.x;
		}
		else
		{
			axis_move.x = 1;
			ray_first.x = ((player_in_map.x + 1) - ray_start.x) * ray_step.x;
		}
		if (direction.y < 0)
		{
			axis_move.y = -1;
			ray_first.y = (ray_start.y - player_in_map.y) * ray_step.y;
		}
		else
		{
			axis_move.y = 1;
			ray_first.y = ((player_in_map.y + 1) - ray_start.y) * ray_step.y;
		}
		int loop = 0;
		while (1)
		{
			//printf("ray first at (%.3f, %.3f)\n", ray_first.x, ray_first.y);
			if (ray_first.x < ray_first.y)
			{
				player_in_map.x += axis_move.x;
				ray_first.x += ray_step.x;
				side = 0;
			}
			else
			{
				player_in_map.y += axis_move.y;
				ray_first.y += ray_step.y;
				side = 1;
			}
			//printf("loop %d, checking map point (%d, %d) whose value is %c\n", loop, (int)player_in_map.x, (int)player_in_map.y, game->map.map[(int)player_in_map.x + (int)player_in_map.y * game->map.width]);

			if (game->map.map[(int)player_in_map.x + (int)player_in_map.y * game->map.width] == MAP_WALL)
			{
				//printf("wall hit at (%.3f, %.3f), column %d\n", ray_first.x - game->player.map_posi.x, ray_first.y - game->player.map_posi.y, x);
				//printf("dda break \n");
				break ;
			}
			//else
			//{
			//	//printf("setting %d, %d to visible\n",(int)player_in_map.x, (int)player_in_map.y);
			//	game->visible[(int)player_in_map.x + game->map.width * (int)player_in_map.y] = true;
			//	//printf("done\n");
			//}
				
			loop++;
		}
		game->hori_rays[x].side = side;
		
		float perpWallDist;
		if(side == 0) perpWallDist = (ray_first.x - ray_step.x);
			else          perpWallDist = (ray_first.y - ray_step.y);
		game->hori_rays[x].perpWallDist = perpWallDist;
		//printf("perpwalldist %.3f\n", perpWallDist);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);
		game->hori_rays[x].line_height = lineHeight;
		//calculate lowest and highest pixel to fill in current stripe
		game->hori_rays[x].min_y = -lineHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / perpWallDist);
		//game->hori_rays[x].min_y = int_clamp(game->hori_rays[x].min_y, 0, h);
		game->hori_rays[x].max_y = lineHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2)/ perpWallDist);
		//game->hori_rays[x].max_y = int_clamp(game->hori_rays[x].max_y, 0, h);
		
		if (game->hori_rays[x].min_y > game->maxmin_hori)
			game->maxmin_hori = game->hori_rays[x].min_y;
		if (game->hori_rays[x].max_y < game->minmax_hori)
			game->minmax_hori = game->hori_rays[x].max_y;
		//choose wall color





		//draw_vertical_line(&game->win, drawStart, drawEnd, x, color);
		x++;
	}
	/*
	int i;
	int j;

	i = game->map.len - game->map.len;
	while (i >= 0)
	{
		j = 0;
		printf("\n");
		while (j < game->map.len)
		{
			printf("%d", game->visible[i + j]);
			j++;
		}
		i -= game->map.width;
	}
	printf("\n");
	exit(0);
	*/
	//draw_raycast_horizontal(game);
	//exit (0);
}


void	dda_visible_and_wallcast(t_game *game)
{
	float cameraX;
	int w = game->win.width;
	int h = game->win.height;
	t_vector	dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);	//for zooming, increase direction vector
	t_vector 	plane = game->player.plane;
	int		x;

	t_vector	ray_start;
	t_vector	ray_first;
	t_vector	ray_step;
	t_vector	axis_move;
	t_vector	player_in_map;
	player_in_map = (t_vector){(float)((int)game->player.map_posi.x), (float)((int)game->player.map_posi.y)};
	ray_start = game->player.map_posi;
	//ft_memset(game->visible, 0, game->map.width * game->map.height * sizeof(*game->visible));
	//printf("memset done\n");
	//game->visible[(int)player_in_map.x + game->map.width * (int)player_in_map.y] = true;
	t_vector direction;
	int side;
	game->minmax_hori = game->win.height;
	game->maxmin_hori = 0;
	x = 0;
	while (x < w)
	{
		cameraX = 2 * x / (float)w - 1;

		direction = (t_vector){dir.x + plane.x * cameraX, dir.y + plane.y * cameraX};
		//printf("player at (%.3f, %.3f), player dir (%.3f, %.3f), direction (%.3f, %.3f)\n", 
		//game->player.map_posi.x, game->player.map_posi.y, 
		//game->player.dir_vec.x,
		//game->player.dir_vec.y,
		//
		//direction.x, direction.y);
		ray_step = (t_vector){direction.x == 0 ? FLT_MAX : ft_fabs(1.0f / direction.x), direction.y == 0 ? FLT_MAX : ft_fabs(1.0f / direction.y)};
		player_in_map = (t_vector){(float)((int)game->player.map_posi.x), (float)((int)game->player.map_posi.y)};
		//
		//attempt tto add sway horizontally!!!!
		//player_in_map = vector_add(player_in_map, vector_multi(game->player.plane, game->player.walk_z_mod / 200));
		
		
		
		
		//printf("ray step at (%.3f, %.3f)\n", ray_step.x, ray_step.y);
		// first step before constant multiplier, getting move in x axis and y axis
		if (direction.x < 0)
		{
			axis_move.x = -1;
			ray_first.x = (ray_start.x - player_in_map.x) * ray_step.x;
		}
		else
		{
			axis_move.x = 1;
			ray_first.x = ((player_in_map.x + 1) - ray_start.x) * ray_step.x;
		}
		if (direction.y < 0)
		{
			axis_move.y = -1;
			ray_first.y = (ray_start.y - player_in_map.y) * ray_step.y;
		}
		else
		{
			axis_move.y = 1;
			ray_first.y = ((player_in_map.y + 1) - ray_start.y) * ray_step.y;
		}
		int loop = 0;
		while (1)
		{
			//printf("ray first at (%.3f, %.3f)\n", ray_first.x, ray_first.y);
			if (ray_first.x < ray_first.y)
			{
				player_in_map.x += axis_move.x;
				ray_first.x += ray_step.x;
				side = 0;
			}
			else
			{
				player_in_map.y += axis_move.y;
				ray_first.y += ray_step.y;
				side = 1;
			}
			//printf("loop %d, checking map point (%d, %d) whose value is %c\n", loop, (int)player_in_map.x, (int)player_in_map.y, game->map.map[(int)player_in_map.x + (int)player_in_map.y * game->map.width]);

			if (game->map.map[(int)player_in_map.x + (int)player_in_map.y * game->map.width] == MAP_WALL)
			{
				//printf("wall hit at (%.3f, %.3f), column %d\n", ray_first.x - game->player.map_posi.x, ray_first.y - game->player.map_posi.y, x);
				//printf("dda break \n");
				break ;
			}
			//else
			//{
			//	//printf("setting %d, %d to visible\n",(int)player_in_map.x, (int)player_in_map.y);
			//	game->visible[(int)player_in_map.x + game->map.width * (int)player_in_map.y] = true;
			//	//printf("done\n");
			//}
				
			loop++;
		}
		game->hori_rays[x].side = side;
		
		float perpWallDist;
		if(side == 0) perpWallDist = (ray_first.x - ray_step.x);
			else          perpWallDist = (ray_first.y - ray_step.y);
		game->hori_rays[x].perpWallDist = perpWallDist;
		//printf("perpwalldist %.3f\n", perpWallDist);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);
		game->hori_rays[x].line_height = lineHeight;
		//calculate lowest and highest pixel to fill in current stripe
		game->hori_rays[x].min_y = -lineHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / perpWallDist);
		game->hori_rays[x].min_y = int_clamp(game->hori_rays[x].min_y, 0, h);
		game->hori_rays[x].max_y = lineHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2)/ perpWallDist);
		game->hori_rays[x].max_y = int_clamp(game->hori_rays[x].max_y, 0, h);
		
		if (game->hori_rays[x].min_y > game->maxmin_hori)
			game->maxmin_hori = game->hori_rays[x].min_y;
		if (game->hori_rays[x].max_y < game->minmax_hori)
			game->minmax_hori = game->hori_rays[x].max_y;
		//choose wall color


		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = game->hori_rays[x].min_y;
		int drawEnd = game->hori_rays[x].max_y;

		double wallX; //where exactly the wall was hit
		if (game->hori_rays[x].side == 0) wallX = game->player.map_posi.y + game->hori_rays[x].perpWallDist * direction.y;
		else           wallX = game->player.map_posi.x + game->hori_rays[x].perpWallDist * direction.x;
		//if (x == game->win.width / 2)
		//	printf("prefloor wallX is %.10f\n", wallX);
		
		//if (x == game->win.width / 2)
		//	printf("wallX is %.10f, player map (%.3f,%.3f)\n", wallX, player_in_map.x, player_in_map.y);
		//x coordinate on the texture
		t_xpm_tex *tex;
		if (game->hori_rays[x].side == 0)
		{
			tex = game->tex[EA_TEX];
			if (game->player.map_posi.x + game->hori_rays[x].perpWallDist * direction.x < game->player.map_posi.x)
				tex = game->tex[WE_TEX];
		}	
		else
		{
			tex = game->tex[NO_TEX];
			if (game->player.map_posi.y + game->hori_rays[x].perpWallDist * direction.y < game->player.map_posi.y)
				tex = game->tex[SO_TEX];
		}
			
		wallX -= floor((wallX));
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



		//draw_vertical_line(&game->win, drawStart, drawEnd, x, color);
		x++;
	}
	/*
	int i;
	int j;

	i = game->map.len - game->map.len;
	while (i >= 0)
	{
		j = 0;
		printf("\n");
		while (j < game->map.len)
		{
			printf("%d", game->visible[i + j]);
			j++;
		}
		i -= game->map.width;
	}
	printf("\n");
	exit(0);
	*/
	//draw_raycast_horizontal(game);
	//exit (0);
}

