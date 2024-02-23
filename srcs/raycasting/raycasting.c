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

typedef struct s_ray
{
	int			w;
	int			h;
	float 		cam_x;
	t_vector	dir_vec;
	t_vector	plane;
	t_vector	player_sqr;
	t_vector	start;
	t_vector	first;
	t_vector	step;
	t_vector	axis_move;
	t_vector	ray_dir;
	int			side;	
}	t_ray;

static inline float	float_ternary(bool cond, float yes, float no)
{
	if (cond)
		return (yes);
	return (no);
}

static inline void setup_this_ray(t_ray *ray, int win_x)
{
	ray->cam_x = 2 * win_x / (float)ray->w - 1;
	ray->ray_dir = (t_vector){ray->dir_vec.x + ray->plane.x \
		* ray->cam_x, ray->dir_vec.y + ray->plane.y * ray->cam_x};
	ray->step.x = float_ternary(ray->ray_dir.x == 0, FLT_MAX , ft_fabs(1.0f / ray->ray_dir.x));
	ray->step.y = float_ternary(ray->ray_dir.y == 0, FLT_MAX , ft_fabs(1.0f / ray->ray_dir.y));
	ray->player_sqr = (t_vector){(float)((int)ray->start.x), (float)((int)ray->start.y)};
	ray->first.x = float_ternary(ray->ray_dir.x < 0, (ray->start.x - ray->player_sqr.x), \
				((ray->player_sqr.x + 1) - ray->start.x));
	ray->first.y = float_ternary(ray->ray_dir.y < 0, (ray->start.y - ray->player_sqr.y), \
				((ray->player_sqr.y + 1) - ray->start.y));
	ray->first = vector_product(ray->first, ray->step);
	ray->axis_move.x = ft_ternary(ray->ray_dir.x < 0, -1, 1);
	ray->axis_move.y = ft_ternary(ray->ray_dir.y < 0, -1, 1);
}

static inline void setup_common_ray(t_game *game, t_ray *ray)
{
	ray->w = game->win.width;
	ray->h = game->win.height;
	ray->dir_vec = vector_multi(game->player.dir_vec, \
		game->player.cur_dir_len);
	ray->plane = game->player.plane;
	ray->start = game->player.map_posi;
}

void	dda_visible(t_game *game)
{
	t_ray	ray;

	setup_common_ray(game, &ray);
	int w = game->win.width;
	int h = game->win.height;
	int		x;

	//ft_memset(game->visible, 0, game->map.width * game->map.height * sizeof(*game->visible));
	//printf("memset done\n");
	//game->visible[(int)player_in_map.x + game->map.width * (int)player_in_map.y] = true;
	int side;
	game->minmax_hori = game->win.height;
	game->maxmin_hori = 0;
	x = 0;
	while (x < w)
	{
		setup_this_ray(&ray, x);

		//printf("player at (%.3f, %.3f), player dir (%.3f, %.3f), direction (%.3f, %.3f)\n", 
		//game->player.map_posi.x, game->player.map_posi.y, 
		//game->player.dir_vec.x,
		//game->player.dir_vec.y,
		//
		//direction.x, direction.y);
		
		
		
		
		//printf("ray step at (%.3f, %.3f)\n", ray.step.x, ray.step.y);
		// first step before constant multiplier, getting move in x axis and y axis

		int loop = 0;
		while (1)
		{
			//printf("ray first at (%.3f, %.3f)\n", ray.first.x, ray.first.y);
			if (ray.first.x < ray.first.y)
			{
				ray.player_sqr.x += ray.axis_move.x;
				ray.first.x += ray.step.x;
				side = 0;
			}
			else
			{
				ray.player_sqr.y += ray.axis_move.y;
				ray.first.y += ray.step.y;
				side = 1;
			}
			//printf("loop %d, checking map point (%d, %d) whose value is %c\n", loop, (int)ray.player_sqr.x, (int)ray.player_sqr.y, game->map.map[(int)ray.player_sqr.x + (int)ray.player_sqr.y * game->map.width]);

			if (game->map.map[(int)ray.player_sqr.x + (int)ray.player_sqr.y * game->map.width] == MAP_WALL)
			{
				//printf("wall hit at (%.3f, %.3f), column %d\n", ray.first.x - game->player.map_posi.x, ray.first.y - game->player.map_posi.y, x);
				//printf("dda break \n");
				break ;
			}
			//else
			//{
			//	//printf("setting %d, %d to visible\n",(int)ray.player_sqr.x, (int)ray.player_sqr.y);
			//	game->visible[(int)ray.player_sqr.x + game->map.width * (int)ray.player_sqr.y] = true;
			//	//printf("done\n");
			//}
				
			loop++;
		}
		game->hori_rays[x].side = side;
		
		float perpWallDist;
		if(side == 0) perpWallDist = (ray.first.x - ray.step.x);
			else          perpWallDist = (ray.first.y - ray.step.y);
		game->hori_rays[x].perpWallDist = perpWallDist;
		//printf("perpwalldist %.3f\n", perpWallDist);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);
		game->hori_rays[x].line_height = lineHeight;
		game->hori_rays[x].min_y = -lineHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / perpWallDist);
		game->hori_rays[x].max_y = lineHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2)/ perpWallDist);
		
		if (game->hori_rays[x].min_y > game->maxmin_hori)
			game->maxmin_hori = game->hori_rays[x].min_y;
		if (game->hori_rays[x].max_y < game->minmax_hori)
			game->minmax_hori = game->hori_rays[x].max_y;
		x++;
	}
}

