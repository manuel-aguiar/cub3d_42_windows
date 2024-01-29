/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:13:01 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:13:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_windows.h"

int	new_win_init_window(t_win_glfw *win)
{
	if (!win)
		return (perror_msg_int("malloc", 0));
	if (!glfwInit())
        return (0);      // no free, potencial memleak
	win->window = glfwCreateWindow(win->width, win->height, win->name, NULL, NULL);
	if (!win->window)
	{
		glfwTerminate();
		return (0);		// no free, potencial memleak
	}
	glfwMakeContextCurrent(win->window);
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return (0);		// no free, potencial memleak
	}
	win->front_buf = malloc(sizeof(*win->front_buf) * win->width * win->height * win->rgb_size);
	if (!win->front_buf)
		return (0);		// no free, potencial memleak
	win->set_pixel = win_set_pixel;
	win->get_pixel = win_get_pixel;
	glfwSetInputMode(win->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	return (1);	
}

int	free_win_glfw(t_win_glfw *win)
{
	glfwSetInputMode(win->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwDestroyWindow(win->window);
	glfwTerminate();
	free(win->front_buf);
	return (1);
}