/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:25:46 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 10:25:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

int			extract_door(t_game *game, t_map *map, int place, int map_index)
{
	t_door 		*data;
	t_sprite 	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_door, sizeof(*data));
	sprite->data = data;
	sprite->type = DOOR;
	sprite->status = NOT_VIS;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	map->doors[map_index] = sprite;
	sprite->cur_z = 0;
	sprite->height = 0;
	sprite->width = 0;
	sprite->dist = FLT_MAX;
	sprite->tex = DOOR_TEX;
	if (map->map[map_index + 1] == MAP_WALL \
	&& map->map[map_index - 1] == MAP_WALL \
	&& map->map[map_index + map->width] != MAP_WALL \
	&& map->map[map_index - map->width] != MAP_WALL)
		data->orient = NS;
	else if (map->map[map_index + 1] != MAP_WALL \
	&& map->map[map_index - 1] != MAP_WALL \
	&& map->map[map_index + map->width] == MAP_WALL \
	&& map->map[map_index - map->width] == MAP_WALL)
		data->orient = WE;
	else
		return (error_msg_int("cub3d: doors are missplaced\n", STDERR_FILENO, 0));
	data->base_position = sprite->posi;
	return (1);
}

int			extract_exit(t_game *game, t_map *map, int place, int map_index)
{
	t_exit 		*data;
	t_sprite 	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_exit, sizeof(*data));
	sprite->data = data;
	sprite->type = EXIT;
	sprite->status = NOT_VIS;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = EXIT_TEX;
	return (1);
}

int			extract_enemy(t_game *game, t_map *map, int place, int map_index)
{
	t_enemy 		*data;
	t_sprite 	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_enemy, sizeof(*data));
	sprite->data = data;
	sprite->type = ENEMY;
	sprite->status = NOT_VIS;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = ENEMY_TEX;
	return (1);
}

int			extract_ammo(t_game *game, t_map *map, int place, int map_index)
{
	t_ammo 		*data;
	t_sprite 	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_ammo, sizeof(*data));
	sprite->data = data;
	sprite->type = AMMOKIT;
	sprite->status = NOT_VIS;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = AMMO_TEX;
	return (1);
}

int			extract_medi(t_game *game, t_map *map, int place, int map_index)
{
	t_medi 		*data;
	t_sprite 	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_medi, sizeof(*data));
	sprite->data = data;
	sprite->type = MEDIKIT;
	sprite->status = NOT_VIS;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->width = data->width;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = MEDI_TEX;
	return (1);
}

int		extract_sprites(t_game *game, t_map *map)
{
	int	i;
	int	cur;

	i = 0;
	cur = 0;
	while (cur < game->sprite_count)
	{
		while (!char_in_charset(map->map[i], SPRITES))
			i++;
		if ((map->map[i] == MAP_MEDI && !extract_medi(game, map, cur, i)) \
		|| (map->map[i] == MAP_AMMO && !extract_ammo(game, map, cur, i)) \
		|| (map->map[i] == MAP_EXIT && !extract_exit(game, map, cur, i)) \
		|| (map->map[i] == MAP_DOOR && !extract_door(game, map, cur, i)) \
		|| (map->map[i] == MAP_ENEMY && !extract_enemy(game, map, cur, i)))
			return (0);
		i++;
		cur++;
	}
	return (1);
}

int	place_bullet(t_game *game, int place)
{
	t_bullet	*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_bullet, sizeof(*data));
	sprite->data = data;
	sprite->type = BULLET;
	sprite->status = GONE;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->unit_size = data->unit_size;
	sprite->dist = FLT_MAX;
	sprite->tex = BULLET_TEX;
	return (1);
}

int	fill_with_bullets(t_game *game)
{
	int i;

	i = 0;
	while (i < game->max_bullets)
	{
		if (!place_bullet(game, game->sprite_count + i))
			return (0);
		i++;
	}
	return (1);
}


void	fill_sorted_pointers(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		game->sorted[i] = &game->sprites[i];
		i++;
	}
}


int		setup_sprites(t_game *game)
{
	t_sprite	*sprite;
	t_map 		*map;
	int			count;
	int			i;

	map = &game->map;
	i = 0;
	count = 0;
	while (i < map->len)
	{
		if (char_in_charset(map->map[i], SPRITES))
			count++;
		i++;
	}
	sprite = malloc(sizeof(*sprite) * (count + game->max_bullets));
	if (!sprite)
		return (perror_msg_int("malloc", 0));
	game->sprites = sprite;
	game->sprite_count = count;
	if (!extract_sprites(game, map))
		return (0);
	printf("extracted tex\n");
	if (!fill_with_bullets(game))
		return (0);
	game->sprite_count += game->max_bullets;
	printf("filled with bullets\n");
	game->sorted = malloc(sizeof(*game->sorted) * game->sprite_count);
	if (!game->sorted)
		return (perror_msg_int("malloc", 0));
	fill_sorted_pointers(game);
	printf("done\n");
	return (1);
}