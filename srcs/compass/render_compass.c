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

void		compass_setup(t_compass *comp)
{
	comp->centre = (t_pixel){WIN_WIDTH / 4, WIN_HEIGHT / 4, rgba(255,0,0,0)};		//change to relative
	comp->radius = int_clamp(WIN_HEIGHT / 5, CCL_MIN_RAD, CCL_MAX_RAD);
	comp->color = rgba(255,0,0,255);
	comp->inner.radius = int_clamp((int)(comp->radius * 0.7f), (int)(CCL_MIN_RAD * 0.7f), (int)(CCL_MAX_RAD * 0.7f));
	comp->inner.color =  rgba(255,0,0,255);
	comp->letter_height = (int)(comp->radius * 0.1f);
	comp->letter_width = (int)(comp->radius * 0.05f);
	comp->letter_color =  rgba(255,255,255,255);
	comp->letter_radius = (int)(comp->radius * 0.8f);												//manual, clamp?
	comp->sqr_color = rgba(255,165,0,255);
	comp->sqr_height = int_clamp((int)(comp->radius * 0.2f), SQR_MIN_HEIGHT, SQR_MAX_HEIGHT);
	comp->map_centre = (t_pixel){WIN_WIDTH / 2, WIN_HEIGHT / 4, rgba(255,255,255,255)};			//para testes
	init_template_north(comp);
	init_template_south(comp);
	init_template_east(comp);
	init_template_west(comp);

	init_template_square(comp);

	init_inner_circle(comp);

	//init_template_south_circle(comp);
}

void	translate_compass(t_compass *comp, int dx, int dy)
{
	comp->centre.x += dx;
	comp->centre.y += dy;
}

void	render_compass(t_win_glfw *win, t_compass *comp)
{

	//t_pixel c_comp = {400, 400, rgba(255,255,255,255)};
//
	//render_full_circle_with_aa(win, c_comp, comp->radius, rgba(0,255,0,255));

	draw_ring_to_inner_circle(win, comp);
	

	render_north_letter(win, comp);
	render_south_letter(win, comp);
	render_east_letter(win, comp);
	render_west_letter(win, comp);


	//render_inner_square(win, comp, second);

	render_empty_circle_with_aa(win, comp->centre, comp->inner.radius, comp->color);

	//render_inner_circle(win, comp);
}

void		free_compass(t_compass *comp)
{
	free(comp->sqr_x_lim);
	free(comp->circle_x_lim);
}
