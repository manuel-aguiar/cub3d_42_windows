/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_correction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:11:11 by marvin            #+#    #+#             */
/*   Updated: 2024/02/27 15:14:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline float	float_ternary(bool cond, float yes, float no)
{
	if (cond)
		return (yes);
	return (no);
}

static inline void setup_correction_ray(t_game *game, t_ray *ray)
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
	ray->cam_x = 0;
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

static inline void cast_this_ray(t_game *game, t_ray *ray)
{
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
		if (game->map.map[(int)ray->player_sqr.x \
		+ (int)ray->player_sqr.y * game->map.width] == MAP_WALL)
			break ;
	}
}

static t_vec2d get_wall_hit_vertical(t_game *game, t_ray *ray)
{
	t_vec2d		wall_hit;
	float		wall_dist;

	if (ray->side == 0)
	{
		wall_dist = (ray->first.x - ray->step.x);
		wall_hit.y = game->player.map_posi.y + wall_dist * ray->ray_dir.y;
		wall_hit.x = ray->player_sqr.x + (ray->player_sqr.x <= game->player.map_posi.x);
	}
	else
	{
		wall_dist = (ray->first.y - ray->step.y);
		wall_hit.x = game->player.map_posi.x + wall_dist * ray->ray_dir.x;
		wall_hit.y = ray->player_sqr.y + (ray->player_sqr.y <= game->player.map_posi.y);		
	}
	return (wall_hit);
}

t_vec3d	direction_vector(t_vec3d from, t_vec3d to)
{
	t_vec3d direction;

	direction.x = to.x - from.x;
	direction.y = to.y - from.y;
	direction.z = to.z - from.z;
	return (direction);
}

float	vertical_coefficient(t_game *game)
{
	t_ray		ray;
	t_dda_hor	hori;
	t_vec2d		wall_hit;
	int			new_pitch;
	float		new_tan;
	t_vec3d		play_3d;
	t_vec3d		wall_3d;
	t_vec3d		diff;

// game->player.pitch = (int)(game->player.cur_dir_len / game->player.base_dir_len * game->player.verti_tan * game->win.height / 2);

	setup_correction_ray(game, &ray);
	cast_this_ray(game, &ray);
	wall_hit = get_wall_hit_vertical(game, &ray);
	hori.side = ray.side;
	hori.wall_dist = float_ternary(ray.side == 0, (ray.first.x - ray.step.x), \
		(ray.first.y - ray.step.y));
	hori.line_h = (int)((ray.h / hori.wall_dist));
	new_pitch = hori.line_h / 2;
	new_tan = new_pitch * 2 / (float)game->win.height * (float)game->player.base_dir_len / (float)game->player.cur_dir_len;
	//printf("new_tan : %.3f  ", new_tan);
	play_3d = (t_vec3d){game->player.map_posi.x, game->player.map_posi.y, (game->player.cur_z + game->player.jump_z_mod + \
		game->player.walk_z_mod)};
	wall_3d = (t_vec3d){wall_hit.x, wall_hit.y, 1};
	diff = (t_vec3d){wall_3d.x - play_3d.x, wall_3d.y - play_3d.y, wall_3d.z - play_3d.z};
	//printf("diff %.3f, %.3f , %.3f, player dir vec %.3f %.3f\n", diff.x, diff.y, diff.z, game->player.dir_vec.x, game->player.dir_vec.y);
	float t;
	if (game->player.dir_vec.x == 0)
		t = diff.y / game->player.dir_vec.y;
	else
		t = diff.x / game->player.dir_vec.x;
	//printf("t : %.3f  ", t);
	float dir_z = diff.z / t;
	//printf("dir_z : %.3f  ", dir_z);
	float coefficient = dir_z / new_tan;
	//printf("new coefficient %.3f\n", coefficient);
	return (coefficient);
}