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

/*
	Prepare blur with a fixed kernel 1,4,6,4,1 (normalized is aproximatelly gaussian)

	Do horizontal pass and then vertical, not cache optimal but i don't want to transpose
*/
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to transpose a square matrix represented as a 1D array
void transpose(int mat[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // Calculate indices in the 1D array
            int index1 = i * size + j;
            int index2 = j * size + i;
            swap(&mat[index1], &mat[index2]);
        }
    }
}

void	blur_compass(t_win_glfw *win, t_compass *comp)
{
	int		height;
	int		blur_index;
	int		img_x;
	int		img_y;
	int		y;
	int		x;
	float		colors[4];
	t_blur	*blur;

	blur = &comp->blur;
	height = blur->blur_height;
	img_x = (comp->centre.x - comp->inner.radius);
	img_y = (comp->centre.y - comp->inner.radius);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < height)
		{
			blur_index = y * height + x;
			int i;
			int centre;
			i = 0;
			centre = blur->kernel_size / 2;
			
			while (i < blur->kernel_size)
			{
				blur->save_pixels[i] = win->get_pixel(win, (x + img_x) - centre + i, (y + img_y));
				i++;
			}
			
			ft_memset(colors, 0, sizeof(colors));
			i = 0;
			while (i < blur->kernel_size)
			{
				colors[0] += rgb_r(blur->save_pixels[i]) * blur->kernel[i];
				colors[1] += rgb_g(blur->save_pixels[i]) * blur->kernel[i];
				colors[2] += rgb_b(blur->save_pixels[i]) * blur->kernel[i];
				colors[3] += rgb_a(blur->save_pixels[i]) * blur->kernel[i];
				i++;
			}
			blur->hori_blur[blur_index] = rgba((int)(colors[0]), (int)(colors[1]), (int)(colors[2]), (int)(colors[3]));
			x++;
		}
		y++;
	}
	transpose(blur->hori_blur, height);


	y = blur->kernel_size / 2;
	while ( y < height - blur->kernel_size / 2)
	{
		x = blur->kernel_size / 2;
		while (x < height - blur->kernel_size / 2)
		{
			blur_index = y * height + x;
			int i;
			int centre;
			i = 0;
			centre = blur->kernel_size / 2;
			while (i < blur->kernel_size)
			{
				blur->save_pixels[i] = blur->hori_blur[blur_index - centre + i];
				i++;
			}
			ft_memset(colors, 0, sizeof(colors));
			i = 0;
			while (i < blur->kernel_size)
			{
				colors[0] += rgb_r(blur->save_pixels[i]) * blur->kernel[i];
				colors[1] += rgb_g(blur->save_pixels[i]) * blur->kernel[i];
				colors[2] += rgb_b(blur->save_pixels[i]) * blur->kernel[i];
				colors[3] += rgb_a(blur->save_pixels[i]) * blur->kernel[i];
				i++;
			}
			blur->verti_blur[blur_index] = rgba((int)(colors[0]), (int)(colors[1]), (int)(colors[2]), (int)(colors[3]));
			x++;
		}
		y++;
	}
	
	transpose(blur->verti_blur, height);

}



void	render_inner_circle(t_win_glfw *win, t_compass *comp)
{
	t_circle	*inner;
	int	y_adj;
	int	i;

	inner = &comp->inner;
	i = 0;
	y_adj = inner->min_max[MM_MIN_Y] + inner->centre.y;
	while (i < inner->radius * 2 + 1)
	{
		win->set_pixel(win, comp->circle_x_lim[i].min + inner->centre.x, i + y_adj, inner->color);
		win->set_pixel(win, comp->circle_x_lim[i].max + inner->centre.x, i + y_adj, inner->color);
		i++;
	}
	win->set_pixel(win, inner->centre.x, y_adj, inner->color);
	win->set_pixel(win, inner->centre.x, y_adj, inner->color);
}

void	inner_all_decisions(t_compass *comp, t_circle *inner, int x, int y)
{
		comp->circle_x_lim[y + inner->radius].min = ft_min(comp->circle_x_lim[y + inner->radius].min, x);
		comp->circle_x_lim[y + inner->radius].max = ft_max(comp->circle_x_lim[y + inner->radius].max, x);
}

void	inner_circle_circle_x_lim(t_compass *comp, t_circle *inner)
{
	int x;
	int y;
	int decision;

	x = inner->radius;
	y = 0;
	decision = 1 - inner->radius;

		//sqr->lut[y1 - sqr->min_y] -= (sqr->lut[y1 - sqr->min_y] - x1) * (x1 < sqr->lut[y1 - sqr->min_y]);
		//sqr->lut[y1 + sqr->real_z - sqr->min_y] += (x1 - sqr->lut[y1 + sqr->real_z - sqr->min_y]) * (x1 > sqr->lut[y1 + sqr->real_z - sqr->min_y]);

	while (y <= x)
	{

		inner_all_decisions(comp, inner, x, y);
		inner_all_decisions(comp, inner, -x, y);
		inner_all_decisions(comp, inner, x, -y);
		inner_all_decisions(comp, inner, -x, -y);
		inner_all_decisions(comp, inner, y, x);
		inner_all_decisions(comp, inner, -y, x);
		inner_all_decisions(comp, inner, y, -x);
		inner_all_decisions(comp, inner, -y, -x);
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

	
	comp->circle_x_lim = malloc(sizeof(*comp->circle_x_lim) * (inner->radius * 2 + 1));
	if (!comp->circle_x_lim)
		return (perror_msg_int("malloc",0));				//mallloc failed perror

	inner->min_max[MM_MIN_X] = - inner->radius;
	inner->min_max[MM_MAX_X] = + inner->radius;
	inner->min_max[MM_MIN_Y] = - inner->radius;
	inner->min_max[MM_MAX_Y] = + inner->radius;
	i = 0;
	while (i < inner->radius * 2 + 1)
	{
		comp->circle_x_lim[i].min = INT_MAX;
		comp->circle_x_lim[i].max = INT_MIN;
		i++;
	}
	inner_circle_circle_x_lim(comp, inner);

	return (1);
}