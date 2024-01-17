/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter_north.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:51:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:51:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	init_template_north(t_compass *comp, t_north *temp_north)
{
	temp_north->centre = (t_pixel){0, 0, comp->letter_color};
	temp_north->height = comp->letter_height;
	temp_north->width = comp->letter_width;
	temp_north->color = comp->letter_color;
	temp_north->x_off = 0;
	temp_north->y_off = comp->letter_radius;
	temp_north->bot_left = (t_pixel){-(comp->letter_width / 2 + 1), -(comp->letter_height / 2 + 1), comp->letter_color};
	temp_north->bot_right = (t_pixel){+(comp->letter_width / 2 + 1), -(comp->letter_height / 2 + 1), comp->letter_color};
	temp_north->top_left = (t_pixel){-(comp->letter_width / 2 + 1), +(comp->letter_height / 2 + 1), comp->letter_color};
	temp_north->top_right = (t_pixel){+(comp->letter_width / 2 + 1), +(comp->letter_height / 2 + 1), comp->letter_color};
}

void	render_north_letter(t_win_glfw *win, t_compass *comp)
{
	t_north	north;
	int		dx;
	int		dy;

	north = comp->template_north;
	dx = comp->centre.x + north.x_off;
	dy = comp->centre.y + north.y_off;
	translate_point(&north.bot_left, dx, dy);
	translate_point(&north.bot_right, dx, dy);
	translate_point(&north.top_left, dx, dy);
	translate_point(&north.top_right, dx, dy);
	rotate_point(&north.bot_left, comp->centre, comp->cos_rad, comp->sin_rad);
	rotate_point(&north.bot_right, comp->centre, comp->cos_rad, comp->sin_rad);
	rotate_point(&north.top_left, comp->centre, comp->cos_rad, comp->sin_rad);
	rotate_point(&north.top_right, comp->centre, comp->cos_rad, comp->sin_rad);
	xiaolinwu_line(win, north.bot_left, north.top_left);
	xiaolinwu_line(win, north.top_left, north.bot_right);
	xiaolinwu_line(win, north.bot_right, north.top_right);
}
