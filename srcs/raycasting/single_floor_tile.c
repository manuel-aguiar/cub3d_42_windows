/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_floor_tile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:35:06 by marvin            #+#    #+#             */
/*   Updated: 2024/02/08 11:35:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	floorcast(t_game *game)
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
    int max_height = ft_min(h / 2 + game->player.pitch, h);
    while (y < max_height)		//no pitch correction
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
		if (cellX < 0 || cellX > game->map.width || cellY < 0 || cellY > game->map.height)
			break ;
        // get the texture coordinate from the fractional part
        int tx = ft_abs((int)( floor->width * (floorX - cellX)) % floor->width);
        int ty = ft_abs((int)( floor->height * (floorY - cellY)) % floor->height);

        floorX += floorStepX;
        floorY += floorStepY;
		
		//printf("ty %d, width * ty  %d, tx %d, final tex index: %d total size %d color %d\n", ty, floor->width * ty, tx, floor->width * ty + tx, floor->width * floor->height, floor->pixels[floor->width * ty + tx]);
		//if (floor->width * (floor->height - ty - 1) + tx > floor->width * floor->height)
		//{
		//	printf("x %d y %d, index %d, hiegher than total length %d\n", x, y, floor->width * (floor->height - ty - 1) + tx, floor->width * floor->height);
		//	printf("tx %d, max width %d, ty %d, max height %d\n", tx, floor->width, ty, floor->height);
		//}
			
		
		game->win.set_pixel(&game->win, x, y, floor->pixels[floor->width * (floor->height - ty - 1) + tx]);

        //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
        //color = texture[ceilingTexture][texWidth * ty + tx];
        //color = (color >> 1) & 8355711; // make a bit darker
        //buffer[screenHeight - y - 1][x] = color;
		x++;
      }
	  //exit(0);
	  y++;
    }
}