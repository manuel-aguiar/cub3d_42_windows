/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:51:20 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 11:51:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void		compass_template_setup(t_compass *comp, t_pixel centre, int radius, int radians)
{
	comp->centre = centre;
	comp->radius = radius;
	comp->letter_height = (int)(radius * 0.1f);
	comp->letter_width = (int)(radius * 0.05f);
	comp->letter_color = RGBA(255, 255, 255, 255);
	comp->letter_radius = (int)(radius * 0.8f);												//manual
	comp->radians = radians;
	comp->cos_rad = cosf(radians);
	comp->sin_rad = sinf(radians);
	init_template_north(comp);
	init_template_south(comp);
	init_template_east(comp);
	init_template_west(comp);
}

void	rotate_compass(t_compass *comp, float diff_rad)
{
	comp->radians += diff_rad;
	comp->cos_rad = cosf(comp->radians);
	comp->sin_rad = sinf(comp->radians);
	//printf("called, radians are %f\n", comp->radians);
}

void	translate_compass(t_compass *comp, int dx, int dy)
{
	comp->centre.x += dx;
	comp->centre.y += dy;
}

void	render_compass(t_win_glfw *win, t_compass *comp)
{
	chatgpt_anticircle(win, comp->centre, comp->radius, RGBA(255, 0, 255, 0));
	render_north_letter(win, comp);
	render_south_letter(win, comp);
	render_east_letter(win, comp);
	render_west_letter(win, comp);
}