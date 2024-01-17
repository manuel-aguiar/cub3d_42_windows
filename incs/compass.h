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
	The compass will have a centre marker	-> where player will be placed
											-> letter rotation using this centre
											-> circles drawn around this centre

	fdf: map is static and angles are all recalculated from base map
		same here: using templates for letters and squares with starting points
		starting square is centreed at 0,0, with hashtable built around that point
			any square to be rendered will simply be a copy of the template (with hashtable, after rotations)
				square rotates against its own centre (vs letters that rotate against the compass centre)
			and every point will be translated according to the square placement vs this centre
		
		starting letters will be centreed around (0,0) +/- their offset on the compass (0,0)
			then they are displaced to their positions (individual offsets)
			and finally they are rotated against the centre of the compass
				less calculations as their place in the circle will be already correct by rotating against the compass centre
			compass has a starting angle, letters' angle will be define as a function of this one

		the angles between the compass and the letters is determined by trigonometrics:

			north = compass
				cos (a)
				sin (a)
			east:
				cos (a + PI/2) = - sin (a);
				sin (a + PI / 2) = cos (a);
			south:
				cos (a + PI) = -cos (a);
				sin (a + PI) = -sin (a);
			west:
				cos (a - PI /2) = -sin (a);
				sin (a - PI /2) = cos (a);

		east and west are the same (symetrical nature), but their place vs the centre of the compass is different
		and that will lead them to rotate in diffent directions
		


*/

/*
typedef struct s_compass
{
	t_pixel		centre;
	t_circle	inner;
	t_circle	outer;
	float		radians;
	float		cos_rad;
	float		sen_rad;
	int			letter_height;
	int			letter_width;
	t_square	template_square;
	t_north		template_north;
	t_south		template_south;
	t_east		template_east;
	t_west		template_west;
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

enum e_east
{
	E_BOT_LEFT,
	E_BOT_RIGHT,
	E_TOP_LEFT,
	E_TOP_RIGHT,
	E_MID_LEFT,
	E_MID_RIGHT,
	E_SIZE,
};

enum e_north
{
	N_BOT_LEFT,
	N_BOT_RIGHT,
	N_TOP_LEFT,
	N_TOP_RIGHT,
	N_SIZE,
};

enum e_south
{
	S_BOT_LEFT,
	S_BOT_RIGHT,
	S_TOP_LEFT,
	S_TOP_RIGHT,
	S_MID_LEFT,
	S_MID_RIGHT,
	S_SIZE,
};

enum e_west
{
	W_TOP_LEFT,
	W_MB_LEFT,
	W_TOP_MID,
	W_MB_RIGHT,
	W_TOP_RIGHT,
	W_SIZE,
};

typedef struct s_compass
{
	t_pixel		centre;
	//t_circle	inner;
	//t_circle	outer;
	int			radius;
	float		radians;
	float		cos_rad;
	float		sin_rad;
	int			letter_height;
	int			letter_width;
	int			letter_radius;
	int			letter_color;
	t_square	template_square;
	t_pixel		north[N_SIZE];
	t_pixel		south[S_SIZE];
	t_pixel		east[E_SIZE];
	t_pixel		west[W_SIZE];
}	t_compass;

//letter_north.c
void	init_template_north(t_compass *comp);
void	render_north_letter(t_win_glfw *win, t_compass *comp);

//letter_south.c
void	init_template_south(t_compass *comp);
void	render_south_letter(t_win_glfw *win, t_compass *comp);

//letter_east.c
void	init_template_east(t_compass *comp);
void	render_east_letter(t_win_glfw *win, t_compass *comp);

//letter_west.c
void	init_template_west(t_compass *comp);
void	render_west_letter(t_win_glfw *win, t_compass *comp);


//win_circle.c
void	win_drawcircle_wo_antialiasing(t_win_glfw *win, t_pixel  centre, int radius, int color, int width);
void	win_full_circle(t_win_glfw *win, t_pixel centre, int radius, int color);


//win_square.c
void	init_square(t_square *sqr, t_pixel edge1, t_pixel edge2, t_pixel edge3, t_pixel edge4);
void    translate_square(t_square *sqr, int dx, int dy);
void	render_square(t_win_glfw *win, t_square *sqr);

void	rotate_square(t_square *sqr, t_pixel centre, float change);
void	new_init_square(t_square *sqr, t_pixel centre, int width, int color, int degrees);

void	draw_horizontal_line(t_win_glfw *win, int min_x, int max_x, int y, int color);

//translate_rotate.c
void	translate_point(t_pixel	*point, int dx, int dy);
void	backward_rotate_point(t_pixel *point, t_pixel centre, float cos, float sin);
void	rotate_point(t_pixel *point, t_pixel centre, float cos, float sin);

void		compass_template_setup(t_compass *comp, t_pixel centre, int radius, int radians);
void	rotate_compass(t_compass *comp, float diff_rad);
void	translate_compass(t_compass *comp, int dx, int dy);
void	render_compass(t_win_glfw *win, t_compass *comp);

#endif