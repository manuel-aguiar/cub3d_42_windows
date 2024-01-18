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
	comp->inner.radius = (int)(radius * 0.7f);
	comp->inner.color = RGBA(255, 255, 255, 255);
	comp->letter_height = (int)(radius * 0.1f);
	comp->letter_width = (int)(radius * 0.05f);
	comp->letter_color = RGBA(255, 255, 255, 255);
	comp->letter_radius = (int)(radius * 0.8f);												//manual
	comp->radians = radians;
	comp->cos_rad = cosf(radians);
	comp->sin_rad = sinf(radians);
	comp->sqr_color = RGBA(255, 165, 0,255);
	comp->sqr_width = (int)(radius * 0.5f);
	comp->map_centre = centre;			//random;
	init_template_north(comp);
	init_template_south(comp);
	init_template_east(comp);
	init_template_west(comp);

	init_template_square(comp);

	init_inner_circle(comp);

	//init_template_south_circle(comp);
}

void	rotate_compass(t_compass *comp, float diff_rad)
{
	comp->radians += diff_rad;
	comp->cos_rad = cosf(comp->radians);
	comp->sin_rad = sinf(comp->radians);
	rotate_template_square(comp, &comp->sqr);

}

void	translate_compass(t_compass *comp, int dx, int dy)
{
	comp->centre.x += dx;
	comp->centre.y += dy;
}

void	render_compass(t_win_glfw *win, t_compass *comp)
{
	t_pixel first = {-50, 50, RGBA(255, 165, 0, 255)};
	render_new_square(win, comp, first);


	chatgpt_anticircle(win, comp->centre, comp->radius, RGBA(255, 0, 255, 0));
	render_north_letter(win, comp);
	render_south_letter(win, comp);
	render_east_letter(win, comp);
	render_west_letter(win, comp);

	t_pixel start = {680, 700, RGBA(255, 0, 255, 255)};
	t_pixel end = {720, 800, RGBA(255, 165, 0,255)};
	xiaolinwu_line(win, start, end);

	
	t_pixel second = {50, -50, RGBA(255, 165, 0, 255)};
	
	render_new_square(win, comp, second);

	render_inner_circle(win, comp);


}