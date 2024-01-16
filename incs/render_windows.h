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

# include "libft.h"
# include "xiaolin_wu.h"


# define WIN_WIDTH 1920
# define WIN_HEIGHT 1024
# define WIN_NAME "Cub3d"

//RGBA - alpha channel, set to 255 for full opaque
# define RGB_SIZE 4 

# define RGBA(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

typedef struct s_win_glfw t_win_glfw;
typedef struct s_pixel t_pixel;


struct s_win_glfw
{
	GLFWwindow	*window;
	char		*front_buf;
	int			win_width;
	int			win_height;
	void		(*set_pixel)(t_win_glfw *win, int x, int y, int color);
	int			(*get_pixel)(t_win_glfw *win, int x, int y);
};


enum e_keys_vals
{
	KEY_ESC = 65307,
	KEY_RY_L = 'a',
	KEY_RY_R = 'd',
	KEY_RX_L = 's',
	KEY_RX_R = 'w',
	KEY_RZ_L = 'q',
	KEY_RZ_R = 'e',
	KEY_H_UP = 'r',
	KEY_H_DOWN = 'f',
	KEY_ZIN = 'z',
	KEY_ZOUT = 'x',
	KEY_VISO = 'b',
	KEY_VPLL = 'n',
	KEY_VTOP = 'm',
	KEY_HELP = 'h',
};

enum e_keys_bits
{
	BIT_ESC,
	BIT_RY_L,
	BIT_RY_R,
	BIT_RX_L,
	BIT_RX_R,
	BIT_RZ_L,
	BIT_RZ_R,
	BIT_H_UP,
	BIT_H_DOWN,
	BIT_ZIN,
	BIT_ZOUT,
	BIT_VISO,
	BIT_VPLL,
	BIT_VTOP,
	BIT_HELP,
};


//win_init_window.c
t_win_glfw	*win_init_window(void);
int			win_free_glfw(t_win_glfw *win);

//win_keys.c
void	win_key_press(GLFWwindow* window, int key, int scancode, int action, int mods);

//win_render_loop.c
int		win_render(t_win_glfw *win, void (*win_key_press)());

//win_pixels.c
void	win_set_pixel(t_win_glfw *win, int x, int y, int color);
int		win_get_pixel(t_win_glfw *win, int x, int y);
int		avg_colour(int start, int end, int num, int den);
void	swap_pixels(t_pixel *start, t_pixel *end);

void chatgpt_anticircle(t_win_glfw *win, t_pixel center, int radius, int color);


#endif