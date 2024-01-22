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


# define TOTAL_TEXTURES 6

# define VALID_MAP_CHARS "01NSWE "

# define START_ALPHA 255
# define MAX_COLOR 255
# define MIN_COLOR 0

enum	e_textures
{
	NO_TEX,
	SO_TEX,
	WE_TEX,
	EA_TEX,
	F_TEX,
	C_TEX,
	NUM_TEX,
};

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
	t_uint		map_width;
	t_uint		map_height;
	bool		found_player;
}	t_parsing;

//parsing.c
int		parsing_input(t_parsing *parsing, char *av_file);
void	free_parsing_contents(t_parsing *parsing);

//textures.c
int		analise_textures(t_parsing *parsing);


//parsing_print_utils.c
void	print_tex_data(t_parsing *parsing);
void	gnl_len_print_line(void	*str);
void	print_map(t_parsing *parsing);

#endif