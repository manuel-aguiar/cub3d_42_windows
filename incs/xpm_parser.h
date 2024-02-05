/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:29:38 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 11:29:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_PARSER_H

# define XPM_PARSER_H

# include "pixel_point.h"
# include "libft.h"

typedef struct s_xpm_pair
{
	char	*id;
	int		color;
}	t_xpm_pair;

typedef struct s_xpm_tex
{
	int	width;
	int	height;
	int	*pixels;
}	t_xpm_tex;

extern char *g_teste[];
extern char *g_north[];
extern char *g_south[];
extern char *g_east[];
extern char *g_west[];


t_xpm_tex	*xpm_to_tex(char *xpm[]);
void		xpm_tex_transpose(t_xpm_tex *tex);
t_xpm_tex	*xpm_to_tex_transposed(char *xpm[]);

#endif

