/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_pause_blur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:33:24 by marvin            #+#    #+#             */
/*   Updated: 2024/02/19 12:33:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

int		abgr_inversion(int r, int g, int b, int a);

void	window_transpose(char *dest, char *src, int width, int height, int rgb_size)
{
	int	row;
	int	col;
	int src_index;
	int	dest_index;

	row = 0;
	while (row < height)
	{
		col = 0;
		while(col < width)
		{
			src_index = (col + row * width) * rgb_size;
			dest_index = (row + col * height) * rgb_size;
			*(int *)(&dest[dest_index]) = *(int *)(&src[src_index]);
			//dest[dest_index + 0] = src[src_index + 0];
			//dest[dest_index + 1] = src[src_index + 1];
			//dest[dest_index + 2] = src[src_index + 2];
			//dest[dest_index + 3] = src[src_index + 3];
			col++;
		}
		row++;
	}
}

void	dump_blur_to_front_buf(t_win *win, t_pause_blur *blur, char *dump)
{
	int y;
	int index;
	int size;

	y = blur->kernel_size / 2;
	while (y < win->height - blur->kernel_size / 2)
	{
		index = (blur->kernel_size / 2 + y * win->width) * win->rgb_size;
		size = (win->width - (int)(blur->kernel_size / 2) * 2) * win->rgb_size;
		ft_memcpy(&win->front_buf[index], &dump[index], size);
		y++;
	}
}

void	blur_horizontal(t_pause_blur *blur, char *dest, char *src, int width, int height)
{
	int		blur_index;
	int		y;
	int		x;
	float	colors[4];
	int 	centre;
	char	*posi;
	int 	i;
	
	centre = blur->kernel_size / 2;
	y = blur->kernel_size / 2;
	while (y < height - blur->kernel_size / 2)
	{
		x = blur->kernel_size / 2;
		while (x < width - blur->kernel_size / 2)
		{
			blur_index = (y * width + x) * blur->rgb_size;
			ft_memset(colors, 0, sizeof(colors));
			i = 0;					
			while (i < blur->kernel_size)
			{
				blur->save_pixels[i] = *(int *)&src[(y * width + x - centre + i) * blur->rgb_size];
				colors[0] += rgb_r(blur->save_pixels[i]) * blur->kernel[i];
				colors[1] += rgb_g(blur->save_pixels[i]) * blur->kernel[i];
				colors[2] += rgb_b(blur->save_pixels[i]) * blur->kernel[i];
				colors[3] += rgb_a(blur->save_pixels[i]) * blur->kernel[i];
				(void)posi;
				//posi = &src[(y * width + x - centre + i) * blur->rgb_size];
				//colors[0] += (float)*(posi + 0) * blur->kernel[i];
				//colors[1] += (float)*(posi + 1) * blur->kernel[i];
				//colors[2] += (float)*(posi + 2) * blur->kernel[i];
				//colors[3] += (float)*(posi + 3) * blur->kernel[i];
				i++;
			}
			*(int *)&dest[blur_index] = rgba((int)colors[0], (int)colors[1], (int)colors[2], (int)colors[3]);
			//dest[blur_index + 0] = (char)(colors[0]);
			//dest[blur_index + 1] = (char)(colors[1]);
			//dest[blur_index + 2] = (char)(colors[2]);
			//dest[blur_index + 3] = (char)(colors[3]);
			x++;
		}
		y++;
	}
}


int	window_update_clock(t_win *win)
{
	ftime(&win->blur.clock.end);
	win->blur.clock.elapsed = (size_t) (1000.0 * (win->blur.clock.end.time - win->blur.clock.start.time)
	+ (win->blur.clock.end.millitm - win->blur.clock.start.millitm));
	win->blur.clock.start = win->blur.clock.end;
	//printf("clock says %u elapsed\n", win->blur.clock.elapsed);
	return (win->blur.clock.elapsed + 1);
}



static float pause_gaussian(float x, float sigma) {
    return exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * MY_PI) * sigma);
}

// Function to create a Gaussian kernel of size N with standard deviation sigma
static void pause_setup_kernel(t_pause_blur *blur)
{
	int 	centre;
	int 	i;
	float 	sum;

	centre = blur->kernel_size / 2;
	sum = 0;

	i = 0;
	while (i < blur->kernel_size)
	{
        blur->kernel[i] = pause_gaussian(i - centre, sqrt(blur->cur_sigma));
        sum += blur->kernel[i];	
		i++;	
	}
	i = 0;
	while (i < blur->kernel_size)
	{
		blur->kernel[i] /= sum;
		i++;
	}
}

void	blur_pause(t_win *win, t_pause_blur *blur, bool increase_blur)
{
	if (increase_blur)
		blur->elapsed = int_clamp(blur->elapsed + window_update_clock(win), 0, blur->pause_time);
	else
		blur->elapsed = int_clamp(blur->elapsed - window_update_clock(win), 0, blur->pause_time);
	blur->cur_sigma = blur->min_sigma + (int)(((float)blur->elapsed / (float)blur->pause_time) * (blur->max_sigma - blur->min_sigma));
	//printf("sigma is %d, elapsed is %ld\n", blur->cur_sigma, blur->elapsed);
	pause_setup_kernel(blur);
	blur_horizontal(blur, blur->first, blur->save_front, blur->width, blur->height);
	window_transpose(blur->second, blur->first, blur->width, blur->height, blur->rgb_size);
	blur_horizontal(blur, blur->first, blur->second, blur->height, blur->width);
	window_transpose(blur->second, blur->first, blur->height, blur->width, blur->rgb_size);
	dump_blur_to_front_buf(win, blur, blur->second);
}

void	window_pause_manager(t_game *game, t_win *win, e_pause_state state)
{
	t_pause_blur *blur;

	blur = &win->blur;
	if (state == PAUSE_ON)
	{
		if (blur->elapsed >= blur->pause_time)
		{
			blur->elapsed = blur->pause_time;
			//printf("hello?\n");
			return ;
		}
		if (blur->elapsed <= 0)
		{
			ft_memcpy(blur->save_front, win->front_buf, win->height * win->width * win->rgb_size);
			window_update_clock(win);
			blur->elapsed = 1;
		}
		//printf("blur elapsed on %d\n", blur->elapsed);
		if (((*game->keys) >> BIT_BLUR_T) & 1)
			blur_pause(win, blur, true);
		else
			blur->elapsed = int_clamp(blur->elapsed + window_update_clock(win), 0, blur->pause_time);;
	}
	else if (state == PAUSE_OFF)
	{
		//printf("elapsed off is %d\n", blur->elapsed);
		if (blur->elapsed <= 0)
		{
			blur->elapsed = 0;
			return ;
		}
		if (blur->elapsed >= blur->pause_time)
		{
			blur->elapsed = blur->pause_time;
			window_update_clock(win);
		}
			
		//printf("blur elapsed off %d\n", blur->elapsed);
		if (((*game->keys) >> BIT_BLUR_T) & 1)
			blur_pause(win, blur, false);
		else
			blur->elapsed = int_clamp(blur->elapsed - window_update_clock(win), 0, blur->pause_time);
	}
}
