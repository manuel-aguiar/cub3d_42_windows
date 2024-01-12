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

typedef struct s_game
{
	char	*NO_data;
	char	*SO_data;
	char	*WE_data;
	char	*EA_data;
	char	*F_data;
	char	*C_data;
	
}   t_game;

typedef struct s_parsing
{
	t_vdmlist	*list;
	char		*file;
	int			file_len;
	int			fd;
	t_gnl_len	*gnl;
	t_uint		map_width;
	t_uint		map_height;	
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