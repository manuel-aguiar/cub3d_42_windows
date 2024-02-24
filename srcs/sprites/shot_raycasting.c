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
	ray->side = 0;
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

int	shot_hit_enemy(t_game *game, int index, t_vec2d check[2])
{
	t_sprite	*sprite;
	t_hitnode	*node;
	t_vec2d	box[2];

	node = game->map.hit[index].head;
	//printf("checking map at %d %d, number of sprites %d\n", 
	//map_col(&game->map, index), map_row(&game->map, index), 
	//game->map.hit[index].len);
	while (node)
	{
		sprite = node->sprite;
		box[0] = (t_vec2d){sprite->posi.x - sprite->unit_size, sprite->posi.y - sprite->unit_size};
		box[1] = (t_vec2d){sprite->posi.x + sprite->unit_size, sprite->posi.y + sprite->unit_size};
		//printf("checking collision at %d, %d: ", (int)sprite->posi.x, (int)sprite->posi.y);
		if (liang_barsky_hit(box[0], box[1], check[0], check[1]))
		{
			printf("sprite %d at %.3f, %.3f was hit\n", sprite->type, sprite->posi.x, sprite->posi.y);
			return (1);
		}
		//printf(" didn't hit\n");
		node = node->next;
	}
	return (0);
}

double get_z_coordinate(t_vec3d point, t_vec3d dir, double x, double y) {
    // Check if the direction vector has a non-zero component to avoid division by zero
    if (dir.x == 0 && dir.y == 0) {
        printf("Error: The line is parallel to the xy-plane.\n");
        return 0.0;
    }
	printf("player z is %.3f\n", point.z);
    double t;
    // Use one of the parametric equations to solve for t
    if (dir.x != 0) {
        t = (x - point.x) / dir.x;
    } else {
        t = (y - point.y) / dir.y;
    }

    // Compute the z-coordinate using the found value of t
    double z = point.z + dir.z * t;

    return z;
}

static inline void check_wall_hit(t_game *game, t_ray *ray)
{
	t_vec2d		wall_hit;
	float		wall_dist;
	float		z;

	if (ray->side == 0)
	{
		wall_dist = (ray->first.x - ray->step.x);
		wall_hit.y = game->player.map_posi.y + wall_dist * ray->ray_dir.y;
		wall_hit.x = ray->player_sqr.x + (ray->player_sqr.x <= game->player.map_posi.x);
		z = get_z_coordinate(game->player.posi_3d, game->player.dir_3d, wall_hit.x, wall_hit.y);
		printf("wall hit at %.3f, %.3f %.3f\n", wall_hit.x, wall_hit.y, z);
		return ;
	}
	else
	{
		wall_dist = (ray->first.y - ray->step.y);
		wall_hit.x = game->player.map_posi.x + wall_dist * ray->ray_dir.x;
		wall_hit.y = ray->player_sqr.y + (ray->player_sqr.y <= game->player.map_posi.y);
		z = get_z_coordinate(game->player.posi_3d, game->player.dir_3d, wall_hit.x, wall_hit.y);
		printf("wall hit at %.3f, %.3f %.3f\n", wall_hit.x, wall_hit.y, z);
		return ;
	}	
}

void	shot_raycasting(t_game *game, t_vec2d dir)
{
	t_ray		ray;
	t_vec2d		check[2];
	int			map_index;


	//print_hit_map(&game->map);
	setup_hit_ray(game, &ray, dir);
	while (1)
	{
		check[0] = ray.player_sqr;
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
			check[1] = ray.player_sqr;
			if (shot_hit_enemy(game, map_index, check))
				return ;
		}
	}
}