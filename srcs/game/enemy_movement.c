/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:13 by marvin            #+#    #+#             */
/*   Updated: 2024/02/27 15:19:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

static inline float	float_ternary(bool cond, float yes, float no)
{
	if (cond)
		return (yes);
	return (no);
}

static inline void setup_hit_ray(t_game *game, t_ray *ray, t_vec2d dir)
{
	ray->start = game->player.map_posi;
	ray->ray_dir = dir;
	
	ray->step.x = float_ternary(ray->ray_dir.x == 0, FLT_MAX , ft_fabs(1.0f / ray->ray_dir.x));
	ray->step.y = float_ternary(ray->ray_dir.y == 0, FLT_MAX , ft_fabs(1.0f / ray->ray_dir.y));
	ray->player_sqr = (t_vec2d){(float)((int)ray->start.x), (float)((int)ray->start.y)};
	ray->first.x = float_ternary(ray->ray_dir.x < 0, (ray->start.x - ray->player_sqr.x), \
				((ray->player_sqr.x + 1) - ray->start.x));
	ray->first.y = float_ternary(ray->ray_dir.y < 0, (ray->start.y - ray->player_sqr.y), \
				((ray->player_sqr.y + 1) - ray->start.y));
	ray->first = vector_product(ray->first, ray->step);
	ray->side = !(ray->first.x < ray->first.y);
	ray->axis_move.x = ft_ternary(ray->ray_dir.x < 0, -1, 1);
	ray->axis_move.y = ft_ternary(ray->ray_dir.y < 0, -1, 1);
	ray->wall_dist = 0;
}

static inline void move_ray(t_ray *ray)
{
	if (ray->first.x < ray->first.y)
	{
		ray->player_sqr.x += ray->axis_move.x;
		ray->first.x += ray->step.x;
		ray->side = 0;
		ray->wall_dist = (ray->first.x - ray->step.x);
	}
	else
	{
		ray->player_sqr.y += ray->axis_move.y;
		ray->first.y += ray->step.y;
		ray->side = 1;
		ray->wall_dist = (ray->first.y - ray->step.y);
	}    
}

int	enemy_sees_player(t_game *game, t_sprite *sprite, t_vec2d dir)
{
	t_ray	ray;
	int		map_index;

	
	setup_hit_ray(game, &ray, dir);
	while(1)
	{
		move_ray(&ray);
		map_index = (int)ray.player_sqr.x \
		+ (int)ray.player_sqr.y * game->map.width;
		//printf("current square %d, %d\n", (int)ray.player_sqr.x, (int)ray.player_sqr.y);
		if (game->map.map[map_index] == MAP_WALL)
			return (0);
		if ((int)ray.player_sqr.x == (int)sprite->posi.x
		|| (int)ray.player_sqr.y == (int)sprite->posi.y)
			return (1);
	}
	return (1);
}

void	enemy_movement(t_game *game, t_sprite *sprite, t_enemy *enemy)
{
	t_vec2d dir;
	//(void)dir; (void)potential; (void)enemy;
	dir = (t_vec2d){sprite->posi.x - game->player.map_posi.x, sprite->posi.y - game->player.map_posi.y};
	dir = vector_norm(dir, vector_len(dir));
	if (enemy_sees_player(game, sprite, dir))
	{
		dir = vector_multi(vector_multi(dir, enemy->move_sense * game->player.timer[CLOCK_MOVE].elapsed), -1);
		handle_collisions(game, &sprite->posi, dir, sprite->unit_size);
		//printf("sees\n");
	}
	//else
	//	printf("doesn't seee\n");
}