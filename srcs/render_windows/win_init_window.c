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

t_win_glfw	*win_init_window(void)
{
	t_win_glfw	*win;

	win = malloc(sizeof(*win));
	if (!win)
		return (perror_msg_ptr("malloc", NULL));
	win->win_width = WIN_WIDTH;
	win->win_height = WIN_HEIGHT;
	if (!glfwInit())
        return (NULL);      // no free, potencial memleak
	win->window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, NULL, NULL);
	if (!win->window)
	{
		glfwTerminate();
		return (NULL);		// no free, potencial memleak
	}
	glfwMakeContextCurrent(win->window);
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return (NULL);		// no free, potencial memleak
	}
	win->front_buf = malloc(sizeof(*win->front_buf) * WIN_WIDTH * WIN_HEIGHT * RGB_SIZE);
	if (!win->front_buf)
		return (NULL);		// no free, potencial memleak
	win->set_pixel = win_set_pixel;
	win->get_pixel = win_get_pixel;
	return (win);	
}

int	free_win_glfw(t_win_glfw *win)
{
	glfwDestroyWindow(win->window);
	glfwTerminate();
	free(win->front_buf);
	free(win);
	return (1);
}