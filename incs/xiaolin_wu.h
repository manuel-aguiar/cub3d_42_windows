/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolin_wu.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:42:53 by marvin            #+#    #+#             */
/*   Updated: 2024/01/12 17:42:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XIAOLIN_WU_H

# define XIAOLIN_WU_H

# include "libft.h"
# include "pixel.h"
# include "render_windows.h"

typedef struct s_win_glfw t_win_glfw;



typedef struct s_xldata
{
	unsigned short	err_adj;
	unsigned short	err_acc;
	unsigned short	err_temp;
	short			dx;
	short			dy;
	short			save;
	short			slope;
	int				colour;
}	t_xldata;

void	swap_pixels(t_pixel *start, t_pixel *end);

int	xiaolinwu_line(t_win_glfw *win, t_pixel start, t_pixel end);

#endif