/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriteibles.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:55:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 09:55:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SPRITES_H

# define SPRITES_H

# include "libft.h"
# include "vector.h"
# include "parsing.h"
# include <float.h>

# define MAP_MEDI 'M'
# define MAP_AMMO 'A'
# define MAP_ENEMY 'Z'
# define MAP_EXIT 'X'
# define MAP_DOOR 'D'

# define ENEMY_HGT 0.8f
# define ENEMY_WDT 0.8f
# define ENEMY_Z ENEMY_HGT / 2 + ENEMY_HGT - 0.5f
# define ENEMY_UNIT 0.2f
# define ENEMY_Z_SENSE 0.005f
# define ENEMY_RESOURCE 50

# define DOOR_HGT 0.2f
# define DOOR_WDT 0.3f
# define DOOR_Z DOOR_HGT / 2 - DOOR_HGT + 0.5f
# define DOOR_UNIT 0.2f
# define DOOR_Z_SENSE 0.005f
# define DOOR_RESOURCE 50

# define EXIT_HGT 0.2f
# define EXIT_WDT 0.3f
# define EXIT_Z EXIT_HGT / 2 - EXIT_HGT + 0.5f
# define EXIT_UNIT 0.2f
# define EXIT_Z_SENSE 0.005f
# define EXIT_RESOURCE 50

# define MEDI_HGT 0.8f
# define MEDI_WDT 0.3f
# define MEDI_Z MEDI_HGT / 2 + MEDI_HGT - 0.5f
# define MEDI_UNIT 0.2f
# define MEDI_Z_SENSE 0.005f
# define MEDI_RESOURCE 50

# define AMMO_HGT 0.3f
# define AMMO_WDT 0.8f
# define AMMO_Z AMMO_HGT / 2 + AMMO_HGT - 0.5f
# define AMMO_UNIT 0.2f
# define AMMO_Z_SENSE 0.005f
# define AMMO_RESOURCE 50

# define SPRITES "MAZX"

typedef enum
{
	MEDIKIT,
	AMMOKIT,
	ENEMY,
	EXIT,
	DOOR,
}	e_sprite_type;

typedef enum
{
	VISIBLE,
	NOT_VIS,
	GONE,
}	e_sprite_status;

typedef struct s_sprite
{
	e_sprite_type		type;
	e_sprite_status	status;
	t_vector			posi;
	int					resource;
	float				base_z;
	float				cur_z;
	float				dist;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
	e_textures			tex;
}	t_sprite;

int		setup_sprites(t_map *map, t_sprite **place_arr, int *place_count);
int		sprite_qs_comp(float first_dist, float second_dist);
void	sprite_qs_distance(t_sprite *sprites, int sprite_count, int (*cmp)(float , float));

#endif

