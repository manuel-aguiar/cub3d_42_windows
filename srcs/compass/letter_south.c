/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_south.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	init_template_south(t_compass *comp, t_south *temp_south)
{
	temp_south->centre = (t_pixel){0, 0, comp->letter_color};
	temp_south->height = comp->letter_height;
	temp_south->width = comp->letter_width;
	temp_south->color = comp->letter_color;
	temp_south->x_off = 0;
	temp_south->y_off = comp->letter_radius;
	temp_south->bot_left = (t_pixel){-(comp->letter_width / 2 + 1), -(comp->letter_height / 2 + 1), comp->letter_color};
	temp_south->bot_right = (t_pixel){(comp->letter_width / 2 + 1), -(comp->letter_height / 2 + 1), comp->letter_color};
	temp_south->top_left = (t_pixel){-(comp->letter_width / 2 + 1), (comp->letter_height / 2 + 1), comp->letter_color};
	temp_south->top_right = (t_pixel){(comp->letter_width / 2 + 1), (comp->letter_height / 2 + 1), comp->letter_color};
	temp_south->mid_left = (t_pixel){-(comp->letter_width / 2 + 1), 0, comp->letter_color};
	temp_south->mid_right = (t_pixel){(comp->letter_width / 2 + 1), 0, comp->letter_color};
}

void	render_south_letter(t_win_glfw *win, t_compass *comp)
{
	t_south	south;
	int		dx;
	int		dy;

	south = comp->template_south;
	dx = comp->centre.x + south.x_off;
	dy = comp->centre.y + south.y_off;
	translate_point(&south.bot_left, dx, dy);
	translate_point(&south.bot_right, dx, dy);
	translate_point(&south.top_left, dx, dy);
	translate_point(&south.top_right, dx, dy);
	translate_point(&south.mid_left, dx, dy);
	translate_point(&south.mid_right, dx, dy);
	rotate_point(&south.bot_left, comp->centre, -comp->cos_rad, -comp->sin_rad);
	rotate_point(&south.bot_right, comp->centre, -comp->cos_rad, -comp->sin_rad);
	rotate_point(&south.top_left, comp->centre, -comp->cos_rad, -comp->sin_rad);
	rotate_point(&south.top_right, comp->centre, -comp->cos_rad, -comp->sin_rad);
	rotate_point(&south.mid_left, comp->centre, -comp->cos_rad, -comp->sin_rad);
	rotate_point(&south.mid_right, comp->centre, -comp->cos_rad, -comp->sin_rad);
	xiaolinwu_line(win, south.bot_left, south.bot_right);
	xiaolinwu_line(win, south.bot_right, south.mid_right);
	xiaolinwu_line(win, south.mid_right, south.mid_left);
	xiaolinwu_line(win, south.mid_left, south.top_left);
	xiaolinwu_line(win, south.top_left, south.top_right);
}
