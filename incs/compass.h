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



#endif