/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_west.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:47 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	init_template_west(t_compass *comp, t_west *temp_west)
{
	temp_west->centre = (t_pixel){0, 0, comp->letter_color};
	temp_west->height = comp->letter_height;
	temp_west->width = comp->letter_width * 2;
	temp_west->color = comp->letter_color;
	temp_west->x_off = 0;
	temp_west->y_off = comp->letter_radius;
	temp_west->top_left = (t_pixel){-(temp_west->width / 2 + 1),(comp->letter_height / 2 + 1), comp->letter_color};
	temp_west->mid_bot_left = (t_pixel){-(temp_west->width / 4), -(comp->letter_height / 2 + 1), comp->letter_color};
	temp_west->mid_top = (t_pixel){0, (comp->letter_height / 2 + 1), comp->letter_color};
	temp_west->mid_bot_right = (t_pixel){(temp_west->width / 4), -(comp->letter_height / 2 + 1), comp->letter_color};
	temp_west->top_right = (t_pixel){(temp_west->width / 2 + 1),(comp->letter_height / 2 + 1), comp->letter_color};
}

void	backward_rotate_point(t_pixel *point, t_pixel centre, float cos, float sin)
{
	t_pixel og;

	og = *point;
    point->x = cos * (og.x - centre.x) + sin * (og.y - centre.y) + centre.x;
    point->y = sin * (og.x - centre.x) - cos * (og.y - centre.y) + centre.y;
}

void	render_west_letter(t_win_glfw *win, t_compass *comp)
{
	t_west	west;
	int		dx;
	int		dy;

	west = comp->template_west;
	dx = comp->centre.x + west.x_off;
	dy = comp->centre.y + west.y_off;
	translate_point(&west.top_left, dx, dy);
	translate_point(&west.mid_bot_left, dx, dy);
	translate_point(&west.mid_top, dx, dy);
	translate_point(&west.mid_bot_right, dx, dy);
	translate_point(&west.top_right, dx, dy);
	backward_rotate_point(&west.top_left, comp->centre, -comp->sin_rad, -comp->cos_rad);
	backward_rotate_point(&west.mid_bot_left, comp->centre, -comp->sin_rad, -comp->cos_rad);
	backward_rotate_point(&west.mid_top, comp->centre, -comp->sin_rad, -comp->cos_rad);
	backward_rotate_point(&west.mid_bot_right, comp->centre, -comp->sin_rad, -comp->cos_rad);
	backward_rotate_point(&west.top_right, comp->centre, -comp->sin_rad, -comp->cos_rad);
	xiaolinwu_line(win, west.top_left, west.mid_bot_left);
	xiaolinwu_line(win, west.mid_bot_left, west.mid_top);
	xiaolinwu_line(win, west.mid_top, west.mid_bot_right);
	xiaolinwu_line(win, west.mid_bot_right, west.top_right);
}
