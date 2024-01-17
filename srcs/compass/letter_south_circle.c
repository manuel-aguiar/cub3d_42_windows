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

static void setPixel_south(t_win_glfw *win, int centreX, int centreY, int deltaX, int deltaY, int alphad)
{
    win->set_pixel(win, centreX + deltaX, centreY + deltaY, alphad);
    win->set_pixel(win, centreX - deltaX, centreY + deltaY, alphad);
    win->set_pixel(win, centreX + deltaX, centreY - deltaY, alphad);
    win->set_pixel(win, centreX - deltaX, centreY - deltaY, alphad);
}

static void chatgpt_anticircle_south(t_win_glfw *win, t_pixel centre, int radius, int color)
{

	int centreX = centre.x;
	int centreY = centre.y;
    int radius2 = radius * radius;
    static const int maxTransparency = 127;

    // Upper and lower halves
    int quarter = round(radius2 / sqrt(radius2 + radius2));
    for (int x = 0; x <= quarter; x++) {
        float y = radius * sqrt(1 - x * x / (float)radius2);
        float error = y - (int)(y);
        int transparency = (int)(error * maxTransparency);

		int alpha = avg_colour(0, color, transparency, maxTransparency);
		int alpha2 = avg_colour(0, color, (maxTransparency - transparency), maxTransparency);

        setPixel_south(win, centreX, centreY, x, (int)(y), alpha);
		setPixel_south(win, centreX, centreY, (int)(y), x, alpha);
        setPixel_south(win, centreX, centreY, x, (int)(y) + 1, alpha2);
		setPixel_south(win, centreX, centreY, (int)(y) + 1, x, alpha2);
    }
}

void	init_template_south_circle(t_compass *comp)
{
	comp->south_circle[CS_BOT_LEFT] = (t_pixel){-(comp->letter_width / 2 + 1), -(comp->letter_height / 2 + 1), comp->letter_color};
	comp->south_circle[CS_BOT_MID] = (t_pixel){0, -(comp->letter_height / 2 + 1), comp->letter_color};
	comp->south_circle[CS_MMB] = (t_pixel){0, (-comp->letter_height / 4 + 1), comp->letter_color};
	comp->south_circle[CS_MMT] = (t_pixel){0, (comp->letter_height / 4 + 1), comp->letter_color};
	comp->south_circle[CS_TOP_MID] = (t_pixel){0, (comp->letter_height / 2 + 1), comp->letter_color};
	comp->south_circle[CS_TOP_RIGHT] = (t_pixel){(comp->letter_width / 2 + 1), (comp->letter_height / 2 + 1), comp->letter_color};
}

void	render_south_letter_circle(t_win_glfw *win, t_compass *comp)
{
	t_pixel	south[CS_SIZE];
	int		i;
	int		dx;
	int		dy;

	ft_memcpy(south, comp->south_circle, sizeof(*south) * CS_SIZE);
	dx = comp->centre.x;
	dy = comp->centre.y + comp->letter_radius;
	i = 0;
	while (i < S_SIZE)
	{
		translate_point(&south[i], dx, dy);
		rotate_point(&south[i], comp->centre, -comp->cos_rad, -comp->sin_rad);
		i++;
	}
	xiaolinwu_line(win, south[CS_BOT_LEFT], south[CS_BOT_MID]);
	xiaolinwu_line(win, south[CS_TOP_MID], south[CS_TOP_RIGHT]);
	chatgpt_anticircle_south(win, south[CS_MMB], comp->letter_height / 4, comp->letter_color);
	chatgpt_anticircle_south(win, south[CS_MMT], comp->letter_height / 4, comp->letter_color);
}
