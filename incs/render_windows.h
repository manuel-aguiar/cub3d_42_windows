/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_windows.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:10:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:10:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_WINDOWS_H

# define RENDER_WINDOWS_H

# define GLFW_DLL
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <sys\timeb.h> 

# define MY_PI 3.14159265f

# include "libft.h"
# include "vector.h"
# include "pixel_point.h"
# include "user_inputs.h"

# define RGB_SIZE 4 

typedef struct s_win t_win;
typedef struct s_pixel t_pixel;


typedef struct s_fps_counter
{
    struct timeb  start;
    struct timeb  end;
    long int    count;
    char        fps[12];
}   t_fps_counter;

typedef struct s_clock
{
    struct timeb  	start;
    struct timeb  	end;
    size_t			elapsed;
}   t_clock;

typedef struct s_pause_blur
{
	float	kernel[31];
	int		save_pixels[31];
	int		kernel_size;
	int		max_kernel;
	int		cur_sigma;
	int		min_sigma;
	int		max_sigma;
	int		pause_time;
	t_clock	clock;
	int		elapsed;
	char	*first;
	char	*second;
	char	*save_front;
	int		rgb_size;
	int		height;
	int		width;
}	t_pause_blur;

typedef enum
{
	PAUSE_OFF,
	PAUSE_ON,
}	e_pause_state;

struct s_win
{
	GLFWwindow		*window;
	char			*front_buf;
	int				width;
	int				height;
	int				rgb_size;
	char			name[6];
	t_clock			fps;
	t_pause_blur	blur;
	void			(*set_pixel)(t_win *win, int x, int y, int color);
	int				(*get_pixel)(t_win *win, int x, int y);
};



//win_init_window.c
int			win_init_window(t_win *win);
int			free_win_glfw(t_win *win);

//win_keys.c
void	win_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void 	win_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void	win_mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//win_render_loop.c


//win_pixels.c
void	win_set_pixel(t_win *win, int x, int y, int color);
int		win_get_pixel(t_win *win, int x, int y);
int		avg_colour(int start, int end, int num, int den);
void	swap_pixels(t_pixel *start, t_pixel *end);



void chatgpt_anticircle(t_win *win, t_pixel centre, int radius, int color);

//win_fps_counter.c
void    set_fps_start(t_fps_counter *fps);
void    fps_calc_print(t_fps_counter *fps);



//win_pause_blur.c

void	window_pause_manager(t_win *win, e_pause_state state);

#endif