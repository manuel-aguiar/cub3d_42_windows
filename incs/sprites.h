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
# include "render_windows.h"
# include "hit_detection.h"
# include <float.h>



# define SPRITES "MAZXD"

typedef enum
{
	MEDIKIT,
	AMMOKIT,
	ENEMY,
	EXIT,
	DOOR,
	BULLET,
}	e_sprite_type;

typedef enum
{
	GONE,
	VISIBLE,
	NOT_VIS,
}	e_sprite_status;

typedef enum
{
	NS,	
	WE,
}	e_door_dir;

typedef enum
{
	STRAIGHT,
	INVERTED,
}	e_rendir;

typedef struct s_door
{
	t_vec2d				base_position;
	e_door_dir			orient;
	float				move_sense;
	float				dist_sense;
}	t_door;

typedef struct s_ammo
{
	int 				ammopoints;
	float				base_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
	float				float_radius;
}	t_ammo;

typedef struct s_medi
{
	int					lifepoints;
	float				float_radius;
	float				base_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
}	t_medi;

typedef struct s_enemy
{
	int					ms_to_swap;
	int					elapsed;
	float				base_z;
	float				z_sense;
	float				move_sense;
	float				unit_size;
	float				height;
	float				width;
	int					attack_val;
	int					health;
	int					attack_time;
	int					attack_elapsed;
}	t_enemy;

typedef enum
{
	BULL_FLYING,
	BULL_WALL,
}	e_bullet_state;

typedef struct s_bullet
{
	e_bullet_state		state;
	t_vec3d				dir;
	float				dir_len;
	t_vec3d				posi;
	float				base_z;
	float				move_sense;
	float				unit_size;
	float				height;
	int					attack_val;
	t_vec3d				hole;
}	t_bullet;


typedef struct s_exit
{
	float				base_z;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
}	t_exit;

typedef struct s_sprite
{
	e_sprite_type		type;
	e_sprite_status		status;
	t_vec2d				posi;
	float				cur_z;
	float				dist;
	float				height;
	float				width;
	float				unit_size;
	t_clock				clock;
	e_textures			tex;
	void				*data;
	bool				inverted;
	t_hitnode			my_hit[4];
}	t_sprite;

int	sprite_qs_comp(t_sprite *first, t_sprite *second);
void	sprite_qs_distance(t_sprite **sprites, int sprite_count, int (*cmp)(t_sprite * , t_sprite *));


#endif

