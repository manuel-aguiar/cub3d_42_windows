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

static inline float	float_ternary(bool cond, float yes, float no)
{
	if (cond)
		return (yes);
	return (no);
}

static inline void setup_this_ray(t_ray *ray, int win_x)
{
	ray->cam_x = 2 * win_x / (float)ray->w - 1;
	ray->ray_dir = (t_vec2d){ray->dir_vec.x + ray->plane.x \
		* ray->cam_x, ray->dir_vec.y + ray->plane.y * ray->cam_x};
	ray->step.x = float_ternary(ray->ray_dir.x == 0, FLT_MAX , ft_fabs(1.0f / ray->ray_dir.x));
	ray->step.y = float_ternary(ray->ray_dir.y == 0, FLT_MAX , ft_fabs(1.0f / ray->ray_dir.y));
	ray->player_sqr = (t_vec2d){(float)((int)ray->start.x), (float)((int)ray->start.y)};
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
	ray->pitch_mod = ray->h / 2 + game->player.pitch;
	ray->z_mod = (game->player.cur_z + game->player.jump_z_mod + \
		game->player.walk_z_mod) * ray->h - ray->h / 2;
}

void	move_this_ray(t_ray *ray, float perc, float *wall_dist_place)
{
	if (ray->first.x < ray->first.y)
	{
		ray->player_sqr.x += ray->axis_move.x * perc;
		ray->first.x += ray->step.x * perc;
		ray->side = 0;
		if (wall_dist_place)
			*wall_dist_place = ray->first.x - ray->step.x;
	}
	else
	{
		ray->player_sqr.y += ray->axis_move.y * perc;
		ray->first.y += ray->step.y * perc;
		ray->side = 1;
		if (wall_dist_place)
			*wall_dist_place = ray->first.y - ray->step.y;
	}
}

void	update_ray_door(t_game *game, t_ray *ray, int map_index, int x)
{
	t_door 		*door;
	t_dda_hor	hori;
	t_vec2d wall_hit;
	float 		wallll;
	t_ray		save;
	float		hit;

	save = *ray;
	door = (t_door*)game->map.doors[map_index]->data;
	move_this_ray(&save, 1.0f, NULL);
	if (save.first.x < save.first.y)
	{
		hori.wall_dist = save.first.x - save.step.x;
		wallll = game->player.map_posi.y + hori.wall_dist * save.ray_dir.y;
		wall_hit.y = game->player.map_posi.y + hori.wall_dist * ray->ray_dir.y;
		wall_hit.x = ray->player_sqr.x + (ray->player_sqr.x <= game->player.map_posi.x);
		hit = ft_fabs((wallll - (int)(wallll)));
	}
		
	else
	{
		hori.wall_dist = save.first.y - save.step.y;
		wall_hit.x = game->player.map_posi.x + hori.wall_dist * ray->ray_dir.x;
		wall_hit.y = ray->player_sqr.y + (ray->player_sqr.y <= game->player.map_posi.y);
		wallll = game->player.map_posi.x + hori.wall_dist * save.ray_dir.x;
		hit = ft_fabs((wallll - (int)(wallll)));
	}
	//printf("hit %.3f side %d wall hit x  %.3f y %.3f\n", hit, save.side, wall_hit.x, wall_hit.y);	
	(void)hit;
	(void)wall_hit;
	if (save.side == ray->side)
	{
		save = *ray;
		move_this_ray(&save, 0.5f, &hori.wall_dist);
		hori.line_h = (int)((save.h / hori.wall_dist) * game->view_adj);
		save.hgt_mod = save.pitch_mod - (int)(save.z_mod / hori.wall_dist * game->view_adj);
		hori.min_y = -hori.line_h / 2 + save.hgt_mod;
		hori.max_y = hori.line_h / 2 + save.hgt_mod;
		hori.reflect_den = ft_abs((int)(hori.wall_dist * 100));
		hori.reflect_num = int_clamp(-hori.reflect_den + (int)((game->max_vis_dist / game->player.cur_dir_len * game->player.base_dir_len) * 100), 0, (int)(hori.wall_dist * 100 * game->wall_reflection));
		door->end = hori;
		printf("x %d: min y %d max %d\n", x, door->end.min_y, door->end.max_y);
		door->end_x = x;
		door->wall_end = wallll;
		if (door->start_x == -1)
		{
			door->start = door->end;
			door->start_x = door->end_x;
			door->wall_start = door->wall_end;
		}
		door->visible = true;	
	}
	else
	{
		if (save.first.x < save.first.y)
		{
			hori.wall_dist = save.first.x - save.step.x;
			wallll = game->player.map_posi.y + hori.wall_dist * save.ray_dir.y;
			if (wallll - (int)wallll < 0.5f)
			{
				printf("x %d there could be a pixel %.3f\n", x, wallll);
			}
			else
				printf("x %d keep going to wall %.3f\n", x, wallll);
		}
			
		else
		{
			hori.wall_dist = save.first.y - save.step.y;
			wallll = game->player.map_posi.x + hori.wall_dist * save.ray_dir.x;
			if (wallll - (int)wallll < 0.5f)
			{
				printf("x %d there could be a pixel %.3f\n", x, wallll);
			}
			else
				printf("x %d keep going to wall  %.3f\n", x, wallll);
		}
	}
	//else
	//	printf("hit is %.3f, side %d\n", hit, save.side);
}

//static inline void cast_this_ray(t_game *game, t_ray *ray, int x)
static inline void cast_this_ray(t_game *game, t_ray *ray)
{
	int map_index;

	while (1)
	{
		if (ray->first.x < ray->first.y)
		{
			ray->player_sqr.x += ray->axis_move.x;
			ray->first.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->player_sqr.y += ray->axis_move.y;
			ray->first.y += ray->step.y;
			ray->side = 1;
		}
		map_index = (int)ray->player_sqr.x \
		+ (int)ray->player_sqr.y * game->map.width;
		if (game->map.map[map_index] == MAP_WALL)
			break ;
		//else if (game->map.map[map_index] == MAP_DOOR)
		//	update_ray_door(game, ray, map_index, x);
	}
}

void	hori_raycasting(t_game *game)
{
	t_ray		ray;
	t_dda_hor	hori;
	int			x;

	setup_common_ray(game, &ray);
	game->minmax_hori = game->win.height;
	game->maxmin_hori = 0;
	x = 0;
	while (x < ray.w)
	{
		setup_this_ray(&ray, x);
		cast_this_ray(game, &ray);
		hori.side = ray.side;
		hori.wall_dist = float_ternary(ray.side == 0, (ray.first.x - ray.step.x), \
			(ray.first.y - ray.step.y));
		hori.line_h = (int)((ray.h / hori.wall_dist) * game->view_adj);
		ray.hgt_mod = ray.pitch_mod - (int)(ray.z_mod / hori.wall_dist * game->view_adj);
		hori.min_y = -hori.line_h / 2 + ray.hgt_mod;
		hori.max_y = hori.line_h / 2 + ray.hgt_mod;
		hori.reflect_den = ft_abs((int)(hori.wall_dist * 100));
		hori.reflect_num = int_clamp(-hori.reflect_den + (int)((game->max_vis_dist / game->player.cur_dir_len * game->player.base_dir_len) * 100), 0, (int)(hori.wall_dist * 100 * game->wall_reflection));
		// multithread mutex here
		game->maxmin_hori = ft_max(hori.min_y, game->maxmin_hori);
		game->minmax_hori = ft_min(hori.max_y, game->minmax_hori);
		game->hori_rays[x] = hori;
		wallcast(game, &ray, &hori, x);
		x++;
	}
}
