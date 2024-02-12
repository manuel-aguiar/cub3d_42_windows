/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:35:48 by marvin            #+#    #+#             */
/*   Updated: 2024/01/22 10:35:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "render_windows.h"
# include "vector.h"
# include "pixel_point.h"

# define TOTAL_TEXTURES 6

# define VALID_MAP_CHARS "01NSWEMA "

# define VALID_STARt_vector "NSWE"

# define START_ALPHA 255
# define MAX_COLOR 255
# define MIN_COLOR 0

typedef	enum
{
	NO_TEX,
	SO_TEX,
	WE_TEX,
	EA_TEX,
	F_TEX,
	C_TEX,
	MEDI_TEX,
	AMMO_TEX,
	ENEMY_TEX,
	BULLET_TEX,
	GUN_TEX,
	NUM_TEX,
}	e_textures;

enum e_tex_type
{
	PATH_TEX,
	COLOR_TEX,
};

typedef struct s_tex
{
	int		type;
	char	*path;
	int		color;
}	t_tex;

typedef struct s_parsing
{
	t_vdmlist	*list;
	char		*file;
	int			file_len;
	int			fd;
	t_gnl_len	*gnl;
	t_tex		tex_data[NUM_TEX];
	char		*map;
	int			map_width;
	int			map_height;
	bool		found_player;
}	t_parsing;

typedef struct s_map
{
	char		*map;
	int			width;
	int			height;
	int			len;
	t_tex		tex_data[NUM_TEX];
}	t_map;


//parsing.c
int		map_parsing(t_map *map, char *av_file);
void	free_map(t_map *map);

//textures.c
int		analise_textures(t_parsing *parsing);


//parsing_print_utils.c
void	print_tex_data(t_parsing *parsing);
void	gnl_len_print_line(void	*str);
void	print_map(t_map *map);

int		map_row(t_map *map, int index);
int		map_col(t_map *map, int index);

#endif