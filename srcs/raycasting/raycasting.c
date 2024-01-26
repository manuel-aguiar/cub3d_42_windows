/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 09:43:36 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 09:43:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//# include "game.h"
//
///*
//	First, get the vectors to the first X side encounter and first Y encounter
//	from then, get the vector to the second X and second Y. This second vector
//	will be called delta because:
//	By mathematics of squares, each X side will be "second X away from each other"
//	and each Y side will be "second Y away from each other".
//	so, to find interceptions, we move them along side. when a wall is hit, then it is stopped
//	What makes the algorithm efficient is the fact that one can determine where potential
//	walls will be by just (first X + delta X * trials), and the same for Y.
//	This possible given the symetry of rectangles and squares.
//
//	t_vector ray, signals the direction the ray is pointing to. In this case,
//	towards the camera plane formed by or plane.
//
//*/
//
//void	draw_vertical_line(t_win_glfw *win, int start_y, int end_y, int x, int color)
//{
//	while (start_y <= end_y)
//		win->set_pixel(win, x, start_y++, color);
//}
//
//void	raycasting(t_game *game)
//{
//	/*
//	t_player	*player;
//	t_vector	dir;
//	t_vector	plane;
//	t_vector	ray;
//	int			win_width;
//	int			win_height;
//	float		camera_x;
//	int			x;
//	t_vector	first_x;
//	t_vector	first_y;
//	t_vector	delta_x;
//	t_vector	delta_y;
//
//
//	player = &game->player;
//	dir = player->direction;
//	plane = player->plane;
//	win_width = game->win.width;
//	win_height = game->win.height;
//
//	while (x < game->win.width)
//	{
//		camera_x = 2 * (x / (float)win_width) - 1;
//		ray = vector_add(dir, vector_multi(plane, camera_x));
//	}
//	*/
//	int w = game->win.width;
//	int h = game->win.height;
//	float dirX = game->player.direction.x;
//	float dirY = game->player.direction.y;
//	float planeX = game->player.plane.x;
//	float planeY = game->player.plane.y;
//	float posX = game->player.map_posi.x;
//	float posY = game->player.map_posi.y;
//
//	for(int x = 0; x < w; x++)
//    {
//
//      //calculate ray position and direction
//      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
//      double rayDirX = dirX + planeX * cameraX;
//      double rayDirY = dirY + planeY * cameraX;
//      //which box of the map we're in
//      int mapX = (int)(posX);
//      int mapY = (int)(posX);
//
//      //length of ray from current position to next x or y-side
//      double sideDistX;
//      double sideDistY;
//
//      //length of ray from one x or y-side to next x or y-side
//      //these are derived as:
//      //deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
//      //deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
//      //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
//      //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
//      //unlike (dirX, dirY) is not 1, however this does not matter, only the
//      //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
//      //stepping further below works. So the values can be computed as below.
//      // Division through zero is prevented, even though technically that's not
//      // needed in C++ with IEEE 754 floating point values.
//      double deltaDistX = (rayDirX == 0) ? INT_MAX : abs(1 / rayDirX);
//      double deltaDistY = (rayDirY == 0) ? INT_MAX : abs(1 / rayDirY);
//
//      double perpWallDist;
//
//      //what direction to step in x or y-direction (either +1 or -1)
//      int stepX;
//      int stepY;
//
//      int hit = 0; //was there a wall hit?
//      int side; //was a NS or a EW wall hit?
//      //calculate step and initial sideDist
//      if(rayDirX < 0)
//      {
//        stepX = -1;
//        sideDistX = (posX - mapX) * deltaDistX;
//      }
//      else
//      {
//        stepX = 1;
//        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//      }
//      if(rayDirY < 0)
//      {
//        stepY = -1;
//        sideDistY = (posY - mapY) * deltaDistY;
//      }
//      else
//      {
//        stepY = 1;
//        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//      }
//      //perform DDA
//      while(hit == 0)
//      {
//        //jump to next map square, either in x-direction, or in y-direction
//        if(sideDistX < sideDistY)
//        {
//          sideDistX += deltaDistX;
//          mapX += stepX;
//          side = 0;
//        }
//        else
//        {
//          sideDistY += deltaDistY;
//          mapY += stepY;
//          side = 1;
//        }
//        //Check if ray has hit a wall
//        if(game->map.map[mapX + mapY * game->map.width] == '1') hit = 1;
//      }
//      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
//      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
//      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
//      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
//      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
//      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
//      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//      else          perpWallDist = (sideDistY - deltaDistY);
//
//      //Calculate height of line to draw on screen
//      int lineHeight = (int)(h / perpWallDist);
//
//      //calculate lowest and highest pixel to fill in current stripe
//      int drawStart = -lineHeight / 2 + h / 2;
//      if(drawStart < 0) drawStart = 0;
//      int drawEnd = lineHeight / 2 + h / 2;
//      if(drawEnd >= h) drawEnd = h - 1;
//
//      //choose wall color
//      int color = ARGB(0,255,0,0);
//
//      //give x and y sides different brightness
//      //if(side == 1) {color = color / 2;}
//
//      //draw the pixels of the stripe as a vertical line
//      draw_vertical_line(&game->win, drawStart, drawEnd, x, color);
//    }
//}

