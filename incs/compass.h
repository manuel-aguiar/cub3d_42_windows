/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:27:51 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:27:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPASS_H

# define COMPASS_H

# include "render_windows.h"

# include "math.h"

# define MY_PI 3.14159

//easier and more symetrical if letter height/width is an odd number
# define LETTER_HEIGHT 9
# define LETTER_WIDTH 5

typedef struct s_circle t_circle;
typedef struct s_north t_north;
typedef struct s_south t_south;
typedef struct s_east t_east;
typedef struct s_west t_west;

/*
typedef struct s_compass
{
	t_pixel		centre;
	t_circle	inner;
	t_circle	outer;
	t_circle	letters;
	int			letter_height;
	int			letter_width;
	t_north		north;
	t_south		south;
	t_east		east;
	t_west		west;
}	t_compass;
*/

typedef struct s_square
{
	t_pixel centre;
	t_pixel	og_edge1;
	t_pixel og_edge2;
	t_pixel og_edge3;
	t_pixel og_edge4;	
	t_pixel	edge1;
	t_pixel edge2;
	t_pixel edge3;
	t_pixel edge4;
	int		width;
	int		color;
	float	radians;
	float	cos_rad;
	float	sen_rad;
	int		min_y;
	int		max_y;
	int		biggest_z;
	int		real_z;
	int		*min_max;
}	t_square;


struct	s_circle
{
	t_pixel	centre;
	int		radius;
	t_pixel start;
	t_pixel	end;
};

struct s_north
{
	t_pixel	centre;
	int		height;
	int		width;
	int		color;
	t_pixel	bot_left;
	t_pixel	bot_right;
	t_pixel	top_left;
	t_pixel	top_right;
};

struct s_better_south
{
	t_pixel		centre;
	int			height;
	int			width;
	int			color;
	t_circle	top;
	t_circle	bottom;
	t_pixel		bot_left;
	t_pixel		bot_right;
	t_pixel		top_left;
	t_pixel		top_right;
};

struct s_south
{
	t_pixel	centre;
	int		height;
	int		width;
	int		color;
	t_pixel	bot_left;
	t_pixel	bot_right;
	t_pixel	top_left;
	t_pixel	top_right;
	t_pixel	mid_left;
	t_pixel	mid_right;
};

struct s_east
{
	t_pixel	centre;
	int		height;
	int		width;
	int		color;
	t_pixel	bot_left;
	t_pixel	bot_right;
	t_pixel	top_left;
	t_pixel	top_right;
	t_pixel	mid_left;
	t_pixel	mid_right;
};

struct s_west
{
	t_pixel	centre;
	int		height;
	int		width;
	int		color;
	t_pixel	top_left;
	t_pixel	mid_bot_left;
	t_pixel	mid_top;
	t_pixel	mid_bot_right;
	t_pixel	top_right;
};

//letter_north.c
void	init_north_letter(t_north *north, t_pixel centre, int height, int width, int color);
void	rotate_north_letter(t_north *north, int rotate);
void	render_north_letter(t_win_glfw *win, t_north *north);

//letter_south.c
void	init_south_letter(t_south *south, t_pixel centre, int height, int width, int color);
void	rotate_south_letter(t_south *south, int rotate);
void	render_south_letter(t_win_glfw *win, t_south *south);

//letter_east.c
void	init_east_letter(t_east *east, t_pixel centre, int height, int width, int color);
void	rotate_east_letter(t_east *east, int rotate);
void	render_east_letter(t_win_glfw *win, t_east *east);

//letter_west.c
void	init_west_letter(t_west *west, t_pixel centre, int height, int width, int color);
void	rotate_west_letter(t_west *west, int rotate);
void	render_west_letter(t_win_glfw *win, t_west *west);


//win_circle.c
void	win_drawcircle_wo_antialiasing(t_win_glfw *win, t_pixel  center, int radius, int color, int width);
void	win_full_circle(t_win_glfw *win, t_pixel center, int radius, int color);


//win_square.c
void	init_square(t_square *sqr, t_pixel edge1, t_pixel edge2, t_pixel edge3, t_pixel edge4);
void    translate_square(t_square *sqr, int dx, int dy);
void	render_square(t_win_glfw *win, t_square *sqr);

void	rotate_square(t_square *sqr, float change);
void	new_init_square(t_square *sqr, t_pixel centre, int width, int color, int degrees);

void	draw_horizontal_line(t_win_glfw *win, int min_x, int max_x, int y, int color);

#endif