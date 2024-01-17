/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_east.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	init_template_east(t_compass *comp, t_east *temp_east)
{
	temp_east->centre = (t_pixel){0, 0, comp->letter_color};
	temp_east->height = comp->letter_height;
	temp_east->width = comp->letter_width;
	temp_east->color = comp->letter_color;
	temp_east->x_off = 0;
	temp_east->y_off = comp->letter_radius;
	temp_east->bot_left = (t_pixel){-(comp->letter_width / 2 + 1), -(comp->letter_height / 2 + 1), comp->letter_color};
	temp_east->bot_right = (t_pixel){(comp->letter_width / 2 + 1), -(comp->letter_height / 2 + 1), comp->letter_color};
	temp_east->top_left = (t_pixel){-(comp->letter_width / 2 + 1), (comp->letter_height / 2 + 1), comp->letter_color};
	temp_east->top_right = (t_pixel){(comp->letter_width / 2 + 1), (comp->letter_height / 2 + 1), comp->letter_color};
	temp_east->mid_left = (t_pixel){-(comp->letter_width / 2 + 1), 0, comp->letter_color};
	temp_east->mid_right = (t_pixel){(comp->letter_width / 2 + 1), 0, comp->letter_color};
}

void	render_east_letter(t_win_glfw *win, t_compass *comp)
{
	t_east	east;
	int		dx;
	int		dy;

	east = comp->template_east;
	dx = comp->centre.x + east.x_off;
	dy = comp->centre.y + east.y_off;
	translate_point(&east.bot_left, dx, dy);
	translate_point(&east.bot_right, dx, dy);
	translate_point(&east.top_left, dx, dy);
	translate_point(&east.top_right, dx, dy);
	translate_point(&east.mid_left, dx, dy);
	translate_point(&east.mid_right, dx, dy);
	rotate_point(&east.bot_left, comp->centre, -comp->sin_rad, comp->cos_rad);
	rotate_point(&east.bot_right, comp->centre, -comp->sin_rad, comp->cos_rad);
	rotate_point(&east.top_left, comp->centre, -comp->sin_rad, comp->cos_rad);
	rotate_point(&east.top_right, comp->centre, -comp->sin_rad, comp->cos_rad);
	rotate_point(&east.mid_left, comp->centre, -comp->sin_rad, comp->cos_rad);
	rotate_point(&east.mid_right, comp->centre, -comp->sin_rad, comp->cos_rad);
	xiaolinwu_line(win, east.bot_left, east.top_left);
	xiaolinwu_line(win, east.top_left, east.top_right);
	xiaolinwu_line(win, east.bot_left, east.bot_right);
	xiaolinwu_line(win, east.mid_left, east.mid_right);
}
