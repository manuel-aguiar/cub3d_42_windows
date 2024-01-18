/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:25:51 by marvin            #+#    #+#             */
/*   Updated: 2024/01/18 19:25:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "compass.h"

void	render_inner_circle(t_win_glfw *win, t_compass *comp)
{
	t_circle	*inner;
	int	i;

	inner = &comp->inner;
	i = 0;
	while (i < inner->radius * 2 + 1)
	{
		win->set_pixel(win, inner->min_max[i], i + inner->min_y, inner->color);
		win->set_pixel(win, inner->min_max[i + inner->radius * 2 + 1], i + inner->min_y, inner->color);
		i++;
	}
	win->set_pixel(win, inner->centre.x, inner->max_y, inner->color);
	win->set_pixel(win, inner->centre.x, inner->min_y, inner->color);
}

void	inner_all_decisions(t_circle *inner, int tgt_x, int tgt_y)
{

		inner->min_max[tgt_y - inner->min_y] -= (inner->min_max[tgt_y - inner->min_y] - (tgt_x)) * (inner->min_max[tgt_y - inner->min_y] > (tgt_x));
		inner->min_max[tgt_y - inner->min_y + 2 * inner->radius + 1] += \
		((tgt_x) - (inner->min_max[tgt_y - inner->min_y + 2 * inner->radius + 1])) * \
		((tgt_x) > (inner->min_max[tgt_y - inner->min_y + 2 * inner->radius + 1]));
}

void	inner_circle_min_max(t_circle *inner)
{
	int x;
	int y;
	int decision;

	x = inner->radius;
	y = 0;
	decision = 1 - inner->radius;

		//sqr->min_max[y1 - sqr->min_y] -= (sqr->min_max[y1 - sqr->min_y] - x1) * (x1 < sqr->min_max[y1 - sqr->min_y]);
		//sqr->min_max[y1 + sqr->real_z - sqr->min_y] += (x1 - sqr->min_max[y1 + sqr->real_z - sqr->min_y]) * (x1 > sqr->min_max[y1 + sqr->real_z - sqr->min_y]);

	while (y <= x)
	{

		inner_all_decisions(inner, x + inner->centre.x, y + inner->centre.y);
		inner_all_decisions(inner, -x + inner->centre.x, y + inner->centre.y);
		inner_all_decisions(inner, x + inner->centre.x, -y + inner->centre.y);
		inner_all_decisions(inner, -x + inner->centre.x, -y + inner->centre.y);
		inner_all_decisions(inner, y + inner->centre.x, x + inner->centre.y);
		inner_all_decisions(inner, -y + inner->centre.x, x + inner->centre.y);
		inner_all_decisions(inner, y + inner->centre.x, -x + inner->centre.y);
		inner_all_decisions(inner, -y + inner->centre.x, -x + inner->centre.y);
		y++;
		if (decision <= 0)
			decision += 2 * y + 1;
		else
		{
			x--;
			decision += 2 * (y - x) + 1;
		}
	}
}

int init_inner_circle(t_compass *comp)
{
	t_circle *inner;
	int      i;

	inner = &comp->inner;
	inner->centre = comp->centre;
	inner->min_max = malloc(sizeof(*inner->min_max) * inner->radius * 4 + 2);
	if (!inner->min_max)
		return (0);					//mallloc failed perror
	inner->min_x = inner->centre.x - inner->radius;
	inner->max_x = inner->centre.x + inner->radius;
	inner->min_y = inner->centre.y - inner->radius;
	inner->max_y = inner->centre.y + inner->radius;
	i = 0;
	while (i < inner->radius * 2 + 1)
		inner->min_max[i++] = INT_MAX;
	while (i < inner->radius * 4 + 2)
		inner->min_max[i++] = INT_MIN;
	inner_circle_min_max(inner);

	return (1);
}