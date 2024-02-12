/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:25:46 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 10:25:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "collectibles.h"

/*

	e_collect_type		type;
	e_collect_status	status;
	t_vector			posi;
	float				base_z;
	float				cur_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
	e_textures			tex;
*/

static void			extract_ammo(t_map *map, t_collect *collect, int place, int map_index)
{
	collect[place].type = AMMOKIT;
	collect[place].status = NOT_VIS;
	collect[place].posi.x = (float)map_col(map, map_index) + 0.5f;
	collect[place].posi.y = (float)map_row(map, map_index) + 0.5f;
	collect[place].base_z = AMMO_Z;
	collect[place].cur_z = AMMO_Z,
	collect[place].z_sense = AMMO_Z_SENSE;
	collect[place].unit_size = AMMO_UNIT;
	collect[place].height = AMMO_HGT;
	collect[place].width = AMMO_WDT;
	collect[place].resource = AMMO_RESOURCE;
}

static void			extract_medi(t_map *map, t_collect *collect, int place, int map_index)
{
	collect[place] = (t_collect){};
	collect[place].type = MEDIKIT;
	collect[place].status = NOT_VIS;
	collect[place].posi.x = (float)map_col(map, map_index) + 0.5f;
	collect[place].posi.y = (float)map_row(map, map_index) + 0.5f;
	collect[place].base_z = MEDI_Z;
	collect[place].cur_z = MEDI_Z,
	collect[place].z_sense = MEDI_Z_SENSE;
	collect[place].unit_size = MEDI_UNIT;
	collect[place].height = MEDI_HGT;
	collect[place].width = MEDI_WDT;
	collect[place].resource = MEDI_RESOURCE;
}

void		extract_collectibles(t_map *map, t_collect *collect, int count)
{
	int	i;
	int	cur;

	i = 0;
	cur = 0;
	while (cur < count)
	{
		while (i < map->len && (map->map[i] != MAP_MEDI || map->map[i] != MAP_AMMO))
			i++;
		if (map->map[i] == MAP_MEDI)
			extract_medi(map, collect, cur, i);
		else if (map->map[i] == MAP_MEDI)
			extract_ammo(map, collect, cur, i);
		cur++;
	}
}

int		setup_collectibles(t_map *map, t_collect **place_arr, int *place_count)
{
	t_collect	*collect;
	int			count;
	int			i;

	i = 0;
	count = 0;
	while (i < map->len)
	{
		if (map->map[i] == MAP_MEDI || map->map[i] == MAP_AMMO)
			count++;
		i++;
	}
	collect = malloc(sizeof(*collect) * count);
	if (!collect)
		return (perror_msg_int("malloc", 0));
	extract_collectibles(map, collect, count);
	*place_arr = collect;
	*place_count = count;
	return (1);
}