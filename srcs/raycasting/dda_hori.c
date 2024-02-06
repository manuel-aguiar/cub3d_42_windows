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

#include "float.h"


void	draw_raycast_horizontal(t_game *game)
{
	int h;
	int w;
	int color = rgba(0,50,0,255);

	h = 0;
	while ( h < game->win.height - 1)
	{
		w = 0;
		while (w < game->win.width - 1)
		{
			if (h == int_clamp(h, game->hori_rays[w].min_x, game->hori_rays[w].max_x))
				game->win.set_pixel(&game->win, w, h, color);
			w++;
		}
		h++;
	}
}

//not using normalized vectors
void	raycasting_horizontal(t_game *game)
{
	float cameraX;
	int w = game->win.width;
	int h = game->win.height;
	t_vector	dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);	//for zooming, increase direction vector
	t_vector 	plane = game->player.plane;
	int		x;

	t_vector	res;
	t_vector	ray_start;
	t_vector	ray_first;
	t_vector	ray_step;
	t_vector	axis_move;
	t_vector	player_in_map;
	float		cur_dist;
	player_in_map = (t_vector){(float)((int)game->player.map_posi.x), (float)((int)game->player.map_posi.y)};
	ray_start = game->player.map_posi;

	t_vector direction;
	int side;

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
		cur_dist = 0;
		int hit = 0;
		int loop = 0;
		while (!hit)
		{
			//printf("ray first at (%.3f, %.3f)\n", ray_first.x, ray_first.y);
			if (ray_first.x < ray_first.y)
			{
				player_in_map.x += axis_move.x;
				cur_dist += ray_first.x;
				ray_first.x += ray_step.x;
				side = 0;
			}
			else
			{
				player_in_map.y += axis_move.y;
				cur_dist += ray_first.y;
				ray_first.y += ray_step.y;
				side = 1;
			}
			//printf("loop %d, checking map point (%d, %d) whose value is %c\n", loop, (int)player_in_map.x, (int)player_in_map.y, game->map.map[(int)player_in_map.x + (int)player_in_map.y * game->map.width]);
			
			if (game->map.map[(int)player_in_map.x + (int)player_in_map.y * game->map.width] == '1')
			{
				res = vector_multi(direction, cur_dist);
				(void)res;
				//printf("wall hit at (%.3f, %.3f), column %d\n", ray_first.x - game->player.map_posi.x, ray_first.y - game->player.map_posi.y, x);
				//printf("dda break \n");
				hit = 1;
			}
			loop++;
		}
		float perpWallDist;
		if(side == 0) perpWallDist = (ray_first.x - ray_step.x);
			else          perpWallDist = (ray_first.y - ray_step.y);
		//printf("perpwalldist %.3f\n", perpWallDist);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		game->hori_rays[x].min_x = -lineHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / perpWallDist);
		if(game->hori_rays[x].min_x < 0) game->hori_rays[x].min_x = 0;
		game->hori_rays[x].max_x = lineHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2)/ perpWallDist);
		if(game->hori_rays[x].max_x >= h) game->hori_rays[x].max_x = h - 1;

		//choose wall color
		

		//draw_vertical_line(&game->win, drawStart, drawEnd, x, color);
		x++;
	}
	draw_raycast_horizontal(game);
	//exit (0);
}