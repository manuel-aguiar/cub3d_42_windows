/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:45:11 by marvin            #+#    #+#             */
/*   Updated: 2024/01/11 14:45:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# define GLFW_DLL
# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include <unistd.h>
# include <fcntl.h>

# include "libft.h"

# define TOTAL_TEXTURES 6

# define VALID_MAP_CHARS "01NSWE "

typedef struct s_parsing
{
	t_vdmlist	*list;
	char		*file;
	int			file_len;
	int			fd;
	t_gnl_len	*gnl;
	char		*tex_data[TOTAL_TEXTURES];
	char		*map;
	t_uint		map_width;
	t_uint		map_height;
	bool		found_player;
}	t_parsing;



enum	e_textures
{
	NO_TEX,
	SO_TEX,
	WE_TEX,
	EA_TEX,
	F_TEX,
	C_TEX,
};

#endif