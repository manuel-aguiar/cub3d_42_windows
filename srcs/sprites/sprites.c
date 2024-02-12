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

# include "sprites.h"

/*

	e_sprite_type		type;
	e_sprite_status	status;
	t_vector			posi;
	float				base_z;
	float				cur_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
	e_textures			tex;
*/

static void			extract_exit(t_map *map, t_sprite *sprite, int place, int map_index)
{
	sprite[place] = (t_sprite){};
	sprite[place].type = EXIT;
	sprite[place].status = NOT_VIS;
	sprite[place].posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite[place].posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite[place].base_z = AMMO_Z;
	sprite[place].cur_z = AMMO_Z;
	sprite[place].z_sense = AMMO_Z_SENSE;
	sprite[place].unit_size = AMMO_UNIT;
	sprite[place].height = AMMO_HGT;
	sprite[place].width = AMMO_WDT;
	sprite[place].resource = AMMO_RESOURCE;
	sprite[place].dist = FLT_MAX;
	sprite[place].tex = EXIT_TEX;
}

static void			extract_enemy(t_map *map, t_sprite *sprite, int place, int map_index)
{
	sprite[place] = (t_sprite){};
	sprite[place].type = ENEMY;
	sprite[place].status = NOT_VIS;
	sprite[place].posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite[place].posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite[place].base_z = AMMO_Z;
	sprite[place].cur_z = AMMO_Z;
	sprite[place].z_sense = AMMO_Z_SENSE;
	sprite[place].unit_size = AMMO_UNIT;
	sprite[place].height = AMMO_HGT;
	sprite[place].width = AMMO_WDT;
	sprite[place].resource = AMMO_RESOURCE;
	sprite[place].dist = FLT_MAX;
	sprite[place].tex = ENEMY_TEX;
}

static void			extract_ammo(t_map *map, t_sprite *sprite, int place, int map_index)
{
	sprite[place] = (t_sprite){};
	sprite[place].type = AMMOKIT;
	sprite[place].status = NOT_VIS;
	sprite[place].posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite[place].posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite[place].base_z = AMMO_Z;
	sprite[place].cur_z = AMMO_Z;
	sprite[place].z_sense = AMMO_Z_SENSE;
	sprite[place].unit_size = AMMO_UNIT;
	sprite[place].height = AMMO_HGT;
	sprite[place].width = AMMO_WDT;
	sprite[place].resource = AMMO_RESOURCE;
	sprite[place].dist = FLT_MAX;
	sprite[place].tex = AMMO_TEX;
}

static void			extract_medi(t_map *map, t_sprite *sprite, int place, int map_index)
{
	sprite[place] = (t_sprite){};
	sprite[place].type = MEDIKIT;
	sprite[place].status = NOT_VIS;
	sprite[place].posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite[place].posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite[place].base_z = MEDI_Z;
	sprite[place].cur_z = MEDI_Z;
	sprite[place].z_sense = MEDI_Z_SENSE;
	sprite[place].unit_size = MEDI_UNIT;
	sprite[place].height = MEDI_HGT;
	sprite[place].width = MEDI_WDT;
	sprite[place].resource = MEDI_RESOURCE;
	sprite[place].dist = FLT_MAX;
	sprite[place].tex = MEDI_TEX;
}

void		extract_sprites(t_map *map, t_sprite *sprite, int count)
{
	int	i;
	int	cur;

	i = 0;
	cur = 0;
	while (cur < count)
	{
		while ((map->map[i] != MAP_MEDI && map->map[i] != MAP_AMMO && map->map[i] != MAP_ENEMY && map->map[i] != MAP_EXIT))
			i++;
		if (map->map[i] == MAP_MEDI)
			extract_medi(map, sprite, cur, i);
		else if (map->map[i] == MAP_AMMO)
			extract_ammo(map, sprite, cur, i);
		else if (map->map[i] == MAP_ENEMY)
			extract_enemy(map, sprite, cur, i);
		else if (map->map[i] == MAP_EXIT)
			extract_exit(map, sprite, cur, i);
		i++;
		cur++;
	}
}

int		setup_sprites(t_map *map, t_sprite **place_arr, int *place_count)
{
	t_sprite	*sprite;
	int			count;
	int			i;

	i = 0;
	count = 0;
	while (i < map->len)
	{
		if (map->map[i] == MAP_MEDI || map->map[i] == MAP_AMMO || map->map[i] == MAP_ENEMY || map->map[i] == MAP_EXIT)
			count++;
		i++;
	}
	sprite = malloc(sizeof(*sprite) * count);
	if (!sprite)
		return (perror_msg_int("malloc", 0));
	extract_sprites(map, sprite, count);
	*place_arr = sprite;
	*place_count = count;
	return (1);
}