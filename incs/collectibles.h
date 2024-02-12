/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:55:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 09:55:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COLLECTIBLES_H

# define COLLECTIBLES_H

# include "libft.h"
# include "vector.h"
# include "parsing.h"

# define MAP_MEDI 'M'
# define MAP_AMMO 'A'

# define MEDI_HGT 10
# define MEDI_WDT 10
# define MEDI_Z 0.2f
# define MEDI_UNIT 0.2f
# define MEDI_Z_SENSE 0.005f
# define MEDI_RESOURCE 50

# define AMMO_HGT 10
# define AMMO_WDT 10
# define AMMO_Z 0.2f
# define AMMO_UNIT 0.2f
# define AMMO_Z_SENSE 0.005f
# define AMMO_RESOURCE 50

typedef enum
{
	MEDIKIT,
	AMMOKIT,
}	e_collect_type;

typedef enum
{
	VISIBLE,
	NOT_VIS,
	GONE,
}	e_collect_status;

typedef struct s_collect
{
	e_collect_type		type;
	e_collect_status	status;
	t_vector			posi;
	int					resource;
	float				base_z;
	float				cur_z;
	float				distance;
	float				z_sense;
	float				unit_size;
	float				height;
	float				width;
	e_textures			tex;
}	t_collect;

int		setup_collectibles(t_map *map, t_collect **place_arr, int *place_count);

#endif

