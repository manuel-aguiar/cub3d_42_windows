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

	t_vector	res;
	t_vector	ray_start;
	t_vector	ray_first;
	t_vector	ray_step;
	t_vector	axis_move;
	t_vector	player_in_map;
	float		cur_dist;
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
			color = add_shade(color, game->hori_rays[x].perpWallDist / game->max_vis_dist);
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

void	floorcast_dda_visible(t_game *game)
{
	int	y;
	int	h;
	int w;
	t_vector ray_left;
	t_vector ray_right;
	t_vector	dir = vector_multi(vector_multi(game->player.dir_vec, game->player.cur_dir_len), -1);
	y = 0;
	h = game->win.height;
	w = game->win.width;

	ray_left = vector_add(dir, game->player.plane);
	ray_right = vector_sub(dir, game->player.plane);
    float posZ = (game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h ;
    //dda_visible(game);
    //printf("break\n")
	//printf("maxmin floor %d\n", game->maxmin_hori);
    while (y < game->maxmin_hori)		//no pitch correction
    {
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)

      //float rayDirX0 = dirX - planeX;
      //float rayDirY0 = dirY - planeY;
      //float rayDirX1 = dirX + planeX;
      //float rayDirY1 = dirY + planeY;

      // Current y position compared to the center of the screen (the horizon)
      int p = y - h / 2 - game->player.pitch;

      // Vertical position of the camera.


      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
      float rowDistance = posZ / p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
      float floorStepX = rowDistance * (ray_right.x - ray_left.x) / w;
      float floorStepY = rowDistance * (ray_right.y - ray_left.y) / w;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX = game->player.map_posi.x + rowDistance * ray_left.x;
      float floorY = game->player.map_posi.y + rowDistance * ray_left.y;

		int x;
		x = 0;

	t_xpm_tex *floor;
		floor = game->tex[F_TEX];
    
      while(x < w)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);
		//if ((cellX < 0 || cellX > game->map.width ) && (cellY < 0 || cellY > game->map.height))
		//	break ;
        // get the texture coordinate from the fractional part
        int tx = ft_abs((int)( floor->width * (floorX - cellX)) % floor->width);
        int ty = ft_abs((int)( floor->height * (floorY - cellY)) % floor->height);

        floorX += floorStepX;
        floorY += floorStepY;
        //while(x < w && !game->visible[(int)floorX * game->map.width + (int)floorY])
        //{
        //    floorX += floorStepX;
        //    floorY += floorStepY;
        //    x++;
        //}

		
		//printf("ty %d, width * ty  %d, tx %d, final tex index: %d total size %d color %d\n", ty, floor->width * ty, tx, floor->width * ty + tx, floor->width * floor->height, floor->pixels[floor->width * ty + tx]);
		//if (floor->width * (floor->height - ty - 1) + tx > floor->width * floor->height)
		//{
		//	printf("x %d y %d, index %d, hiegher than total length %d\n", x, y, floor->width * (floor->height - ty - 1) + tx, floor->width * floor->height);
		//	printf("tx %d, max width %d, ty %d, max height %d\n", tx, floor->width, ty, floor->height);
		//}
			
		//if (!((cellX < 0 || cellX > game->map.width ) || (cellY < 0 || cellY > game->map.height))
		//&& game->visible[(int)floorX + game->map.width * (int)floorY])

		int color = floor->pixels[floor->width * (floor->height - ty - 1) + tx];
		color = add_shade(color, rowDistance / game->max_vis_dist);

		game->win.set_pixel(&game->win, x, y, color);
		x++;
        while(x < w && y >= game->hori_rays[x].min_y)
        {
            floorX += floorStepX;
            floorY += floorStepY;
            x++;
        }
        //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
        //color = texture[ceilingTexture][texWidth * ty + tx];
        //color = (color >> 1) & 8355711; // make a bit darker
        //buffer[screenHeight - y - 1][x] = color;
		
      }
	  //exit(0);
	  y++;
    }

	dir = vector_multi(vector_multi(game->player.dir_vec, game->player.cur_dir_len), 1);
	ray_left = vector_add(dir, game->player.plane);
	ray_right = vector_sub(dir, game->player.plane);
    float floorZ = (1 - (game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod)) * h ;
   // y+=200;
   y = game->minmax_hori + 1;
   //printf("minmax ceil %d\n", game->minmax_hori);
    while (y < h)		//no pitch correction
    {
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
	  //ray_left = vector_add(dir, game->player.plane);
	  //ray_right = vector_sub(dir, game->player.plane);
      //float rayDirX0 = dirX - planeX;
      //float rayDirY0 = dirY - planeY;
      //float rayDirX1 = dirX + planeX;
      //float rayDirY1 = dirY + planeY;

      // Current y position compared to the center of the screen (the horizon)
      int p = y - h / 2 - game->player.pitch;

      // Vertical position of the camera.
         //no pitch correction

      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
      float rowDistance = floorZ / p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
      float floorStepX = rowDistance * (ray_right.x - ray_left.x) / w;
      float floorStepY = rowDistance * (ray_right.y - ray_left.y) / w;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX = game->player.map_posi.x + rowDistance * ray_right.x;
      float floorY = game->player.map_posi.y + rowDistance * ray_right.y;

		int x;
		x = 0;

	t_xpm_tex *floor;
		floor = game->tex[C_TEX];
        
      while(x < w)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);
		//if ((cellX < 0 || cellX > game->map.width ) && (cellY < 0 || cellY > game->map.height))
		//	break ;
        // get the texture coordinate from the fractional part
        int tx = ft_abs((int)( floor->width * (floorX - cellX)) % floor->width);
        int ty = ft_abs((int)( floor->height * (floorY - cellY)) % floor->height);
		
        floorX -= floorStepX;
        floorY -= floorStepY;
		
		//printf("ty %d, width * ty  %d, tx %d, final tex index: %d total size %d color %d\n", ty, floor->width * ty, tx, floor->width * ty + tx, floor->width * floor->height, floor->pixels[floor->width * ty + tx]);
		
		int color = floor->pixels[floor->width * ty + tx];
		color = add_shade(color, rowDistance / game->max_vis_dist);

            game->win.set_pixel(&game->win, x, y, floor->pixels[floor->width * ty + tx]);
		
		x++;
        while(x < w && y <= game->hori_rays[x].max_y)
        {
            floorX -= floorStepX;
            floorY -= floorStepY;
            x++;
        }
        //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
        //color = texture[ceilingTexture][texWidth * ty + tx];
        //color = (color >> 1) & 8355711; // make a bit darker
        //buffer[screenHeight - y - 1][x] = color;
		
      }
	  //exit(0);
	  y++;
    }
	//printf("frame done\n");

	//printf("current pitch %d, screen height %d\n", game->player.pitch, game->win.height);
}