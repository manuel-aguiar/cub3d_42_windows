/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shot_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:26:24 by marvin            #+#    #+#             */
/*   Updated: 2024/02/24 11:26:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	print_hit_map(t_map *map)
{
	int i;
	int j;

	i = map->len - map->width;
	while (i >= 0)
	{
		j = 0;
		printf("\n");
		while (j < map->width)
		{
			if (map->map[i + j] != ' ')
				printf("%d", map->hit[i + j].len);
			else
				printf("%c", map->map[i + j]);
			j++;
		}
		i -= map->width;
	}
	printf("\n");
}

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
	ray->first = vec2d_product(ray->first, ray->step);
	ray->side = !(ray->first.x < ray->first.y);
	ray->axis_move.x = ft_ternary(ray->ray_dir.x < 0, -1, 1);
	ray->axis_move.y = ft_ternary(ray->ray_dir.y < 0, -1, 1);
}

static inline void move_ray(t_ray *ray)
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
}

static inline void check_wall_hit(t_game *game, t_ray *ray)
{
	t_vec2d		wall_hit;
	float		wall_dist;
	float		z;
	t_vec2d		floor_ceil;

	if (ray->side == 0)
	{
		wall_dist = (ray->first.x - ray->step.x);
		wall_hit.y = game->player.map_posi.y + wall_dist * ray->ray_dir.y;
		wall_hit.x = ray->player_sqr.x + (ray->player_sqr.x <= game->player.map_posi.x);
		z = vec3d_get_z_from_xy(game->player.posi_3d, game->player.dir_3d, wall_hit);
		if (z < 0)
		{
			floor_ceil = vec3d_get_xy_from_z(game->player.posi_3d, game->player.dir_3d, 0);
			printf("floor hit at %.3f, %.3f\n", floor_ceil.x, floor_ceil.y);
			return ;
		}
		else if (z > 1)
		{
			floor_ceil = vec3d_get_xy_from_z(game->player.posi_3d, game->player.dir_3d, 1);
			printf("ceiling hit at %.3f, %.3f\n", floor_ceil.x, floor_ceil.y);
			return ;
		}
		printf("wall hit at %.3f, %.3f %.3f\n", wall_hit.x, wall_hit.y, z);
		return ;
	}
	else
	{
		wall_dist = (ray->first.y - ray->step.y);
		wall_hit.x = game->player.map_posi.x + wall_dist * ray->ray_dir.x;
		wall_hit.y = ray->player_sqr.y + (ray->player_sqr.y <= game->player.map_posi.y);
		z = vec3d_get_z_from_xy(game->player.posi_3d, game->player.dir_3d, wall_hit);
		if (z < 0)
		{
			floor_ceil = vec3d_get_xy_from_z(game->player.posi_3d, game->player.dir_3d, 0);
			printf("floor hit at %.3f, %.3f\n", floor_ceil.x, floor_ceil.y);
			return ;
		}
		else if (z > 1)
		{
			floor_ceil = vec3d_get_xy_from_z(game->player.posi_3d, game->player.dir_3d, 1);
			printf("ceiling hit at %.3f, %.3f\n", floor_ceil.x, floor_ceil.y);
			return ;
		}
		printf("wall hit at %.3f, %.3f %.3f\n", wall_hit.x, wall_hit.y, z);
		return ;
	}	
}

t_vec2d get_wall_hit(t_game *game, t_ray *ray)
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

void	enemy_take_hit(t_game *game, t_sprite *sprite)
{
	t_enemy *enemy;

	if (sprite->type != ENEMY)
		return ;
	enemy = (t_enemy *)sprite->data;
	enemy->health -= game->player.attack;
}

int	shot_hit_enemy(t_game *game, int index, t_vec2d check[2])
{
	t_sprite	*sprite;
	t_hitnode	*node;
	t_vec2d		box[2];
	t_vec2d		collision[2];
	float		z;

	node = game->map.hit[index].head;
	//printf("checking map at %d %d, number of sprites %d\n", 
	//map_col(&game->map, index), map_row(&game->map, index), 
	//game->map.hit[index].len);
	while (node)
	{
		sprite = node->sprite;
		box[0] = (t_vec2d){sprite->posi.x - sprite->unit_size, sprite->posi.y - sprite->unit_size};
		box[1] = (t_vec2d){sprite->posi.x + sprite->unit_size, sprite->posi.y + sprite->unit_size};
		//printf("checking collision at %d, %d, box (%.3f, %.3f) to (%.3f, %.3f): 
		//ray (%.3f, %.3f to %.3f %.3f)\n", (int)sprite->posi.x, (int)sprite->posi.y,
		//box[0].x,
		//box[0].y,
		//box[1].x,
		//box[1].y,
		//check[0].x,
		//check[0].y,
		//check[1].x,
		//check[1].y
		//
		//);
		if (liang_barsky_hit(box, check, collision))
		{
			(void)z;
			z = vec3d_get_z_from_xy(game->player.posi_3d, game->player.dir_3d, collision[0]);
			printf("first z %.3f cur_z %.3f height %.3f\n", z, sprite->cur_z, sprite->height);
			if (z >= sprite->cur_z && z <= sprite->height)
			{
				printf("sprite %d at %.3f, %.3f was hit\n", sprite->type, sprite->posi.x, sprite->posi.y);
				enemy_take_hit(game, sprite);
				return (1);
			}
			z = vec3d_get_z_from_xy(game->player.posi_3d, game->player.dir_3d, collision[1]);
			printf("second %.3f cur_z %.3f height %.3f\n", z, sprite->cur_z, sprite->height);
			if (z >= sprite->cur_z && z <= sprite->height)
			{
				printf("sprite %d at %.3f, %.3f was hit\n", sprite->type, sprite->posi.x, sprite->posi.y);
				enemy_take_hit(game, sprite);
				return (1);
			}
		}
		node = node->next;
	}
	return (0);
}

void	shot_raycasting(t_game *game, t_vec2d dir)
{
	t_ray		ray;
	t_vec2d		check[2];
	int			map_index;


	//print_hit_map(&game->map);
	setup_hit_ray(game, &ray, dir);
	check[0] = game->player.map_posi;
	while (1)
	{
		map_index = (int)ray.player_sqr.x \
		+ (int)ray.player_sqr.y * game->map.width;
		//printf("current square %d, %d\n", (int)ray.player_sqr.x, (int)ray.player_sqr.y);
		if (game->map.map[map_index] == MAP_WALL)
		{
			return (check_wall_hit(game, &ray));
		}
		else
		{
			move_ray(&ray);
			check[1] = get_wall_hit(game, &ray);
			if (shot_hit_enemy(game, map_index, check))
				return ;
		}
		check[0] = check[1];
	}
}