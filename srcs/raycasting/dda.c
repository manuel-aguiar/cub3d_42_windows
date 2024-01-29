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

float	ft_fabs(float number)
{
	if (number < 0)
		return (-number);
	return (number);
}

t_vector		dda_get_collision_posi(t_game *game, t_vector norm_dir)
{
	t_vector	res;
	t_vector	ray_start;
	t_vector	ray_first;
	t_vector	ray_step;
	t_vector	axis_move;
	t_vector	player_in_map;
	float		cur_dist;
	float		max_dist;

	max_dist = (float)game->map.len;
	player_in_map = (t_vector){(float)((int)game->player.map_posi.x), (float)((int)game->player.map_posi.y)};
	ray_start = game->player.map_posi;
	ray_step = (t_vector){norm_dir.x == 0 ? FLT_MAX : ft_fabs(1.0f / norm_dir.x), norm_dir.y == 0 ? FLT_MAX : ft_fabs(1.0f / norm_dir.y)};

	// first step before constant multiplier, getting move in x axis and y axis
	if (norm_dir.x < 0)
	{
		axis_move.x = -1;
		ray_first.x = (ray_start.x - player_in_map.x) * ray_step.x;
	}
	else
	{
		axis_move.x = 1;
		ray_first.x = ((player_in_map.x + 1) - ray_start.x) * ray_step.x;
	}
	if (norm_dir.y < 0)
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
	
	while (cur_dist < max_dist)
	{
		if (ray_first.x < ray_first.y)
		{
			player_in_map.x += axis_move.x;
			cur_dist += ray_first.x;
			ray_first.x += ray_step.x;
		}
		else
		{
			player_in_map.y += axis_move.y;
			cur_dist += ray_first.y;
			ray_first.y += ray_step.y;
		}
		//printf("checking map point (%d, %d) whose value is %c\n", (int)player_in_map.x, (int)player_in_map.y, game->map.map[(int)player_in_map.x + (int)player_in_map.y * game->map.width]);
		if (game->map.map[(int)player_in_map.x + (int)player_in_map.y * game->map.width] == '1')
		{
			//printf("dda break \n");
			break ;
		}
			
	}
	
	return (res);
}


//not using normalized vectors
void	raycasting(t_game *game)
{
	float cameraX;
	int w = game->win.width;
	int h = game->win.height;
	t_vector	dir = game->player.dir_vec;
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
		int drawStart = -lineHeight / 2 + h / 2 + game->player.pitch + game->player.z_height / perpWallDist;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2 + game->player.pitch + game->player.z_height / perpWallDist;
		if(drawEnd >= h) drawEnd = h - 1;

		//choose wall color
		int color = rgba(0,50,0,255);

		//give x and y sides different brightness
		//if(side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		draw_vertical_line(&game->win, drawStart, drawEnd, x, color);
		x++;
	}
	//exit (0);
}