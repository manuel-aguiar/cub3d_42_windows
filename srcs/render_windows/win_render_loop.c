/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_render_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:21:38 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:21:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "compass.h"


int		win_render(t_win_glfw *win, void (*win_key_press)())
{
	t_pixel centre = {500, 500, 0, RGBA(255, 0, 0, 255)};


	t_square sqr;
	new_init_square(&sqr, centre, 200, RGBA(255, 165, 0,255), 45);

	glfwSetKeyCallback(win->window, win_key_press);
	glViewport(0, 0, (*win).win_width, (*win).win_height);
    while (!glfwWindowShouldClose(win->window))
	{
		glRasterPos2f(-1, -1);
		ft_memset(win->front_buf, 0, WIN_WIDTH * WIN_HEIGHT * RGB_SIZE * sizeof(*(win->front_buf)));

		if (glfwGetKey(win->window, GLFW_KEY_S))
        	translate_square(&sqr, 0, -1);
		if (glfwGetKey(win->window, GLFW_KEY_W))
        	translate_square(&sqr, 0, 1);
		if (glfwGetKey(win->window, GLFW_KEY_A))
        	translate_square(&sqr, -1, 0);
		if (glfwGetKey(win->window, GLFW_KEY_D))
        	translate_square(&sqr, 1, 0);
		if (glfwGetKey(win->window, GLFW_KEY_Q))
        	rotate_square(&sqr, -0.0045f);
		if (glfwGetKey(win->window, GLFW_KEY_E))
        	rotate_square(&sqr, 0.0045f);

		render_square(win, &sqr);
		
		t_pixel hey = {200, 200, 1000, RGBA(255, 0, 255, 0)};
		chatgpt_anticircle(win, hey, 100, RGBA(255, 0, 255, 0));
		//win_full_circle(win, hey, 50, RGBA(0, 255, 0, 127));
		
		//render_square(win, &sqr);

		glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(win->win_width, win->win_height, GL_RGBA, GL_UNSIGNED_BYTE, win->front_buf);

		glfwSwapBuffers(win->window);
        glfwPollEvents();
    }
	return (1);
}

/*
letters
	t_pixel center = {1000, 500, 1000, RGBA(255, 0, 0, 255)};
	t_east east;
	init_east_letter(&east, center, 67, 33, RGBA(255, 0, 0, 255));

	t_pixel wcent = {1000, 600, 1000, RGBA(255, 0, 0, 255)}; 

	t_west west;
	init_west_letter(&west, wcent, 67, 67, RGBA(255, 0, 0, 255));

	t_pixel ncent = {1000, 800, 1000, RGBA(255, 0, 0, 255)};
	t_north north;
	init_north_letter(&north, ncent, 67, 33, RGBA(255, 0, 0, 255));

	t_pixel scent = {1000, 400, 1000, RGBA(255, 0, 0, 255)};
	t_south south;
	init_south_letter(&south, scent, 67, 33, RGBA(255, 0, 0, 255)); 

		render_east_letter(win, &east);
		render_west_letter(win, &west);
		render_north_letter(win, &north);
		render_south_letter(win, &south);

*/

/*
circle

t_pixel hey = {200, 200, 1000, RGBA(255, 0, 0, 255)};
win_drawcircle_wo_antialiasing(win, hey, 300, RGBA(255, 0, 0, 255), 10);

*/

//GL_RGBA - rgb alpha, it is equivalent to mlx 4-byte format

		/*

		KEYS

		if (glfwGetKey(win->window, GLFW_KEY_UP))
        	adjust_offset(win, &win->view.y_offset, 1 + (int)(win->mcols / 100));
		if (glfwGetKey(win->window, GLFW_KEY_DOWN))
        	adjust_offset(win, &win->view.y_offset, -1 - (int)(win->mcols / 100));
		if (glfwGetKey(win->window, GLFW_KEY_RIGHT))
        	adjust_offset(win, &win->view.x_offset, 1 + (int)(win->mcols / 100));
		if (glfwGetKey(win->window, GLFW_KEY_LEFT))
        	adjust_offset(win, &win->view.x_offset, -1 - (int)(win->mcols / 100));
		if (glfwGetKey(win->window, GLFW_KEY_O))
        	adjust_zoom(win, 1);
		if (glfwGetKey(win->window, GLFW_KEY_P))
        	adjust_zoom(win, -1);
		if (glfwGetKey(win->window, GLFW_KEY_S))
        	key_rotate_x(win, 0.005f);
		if (glfwGetKey(win->window, GLFW_KEY_W))
        	key_rotate_x(win, -0.005f);
		if (glfwGetKey(win->window, GLFW_KEY_A))
        	key_rotate_y(win, 0.005f);
		if (glfwGetKey(win->window, GLFW_KEY_D))
        	key_rotate_y(win, -0.005f);
		if (glfwGetKey(win->window, GLFW_KEY_Q))
        	key_rotate_z(win, 0.005f);
		if (glfwGetKey(win->window, GLFW_KEY_E))
        	key_rotate_z(win, -0.005f);
		if (glfwGetKey(win->window, GLFW_KEY_B))
        	apply_projection(win, 1);
		if (glfwGetKey(win->window, GLFW_KEY_N))
        	apply_projection(win, 2);
		if (glfwGetKey(win->window, GLFW_KEY_M))
        	apply_projection(win, 3);
		if (glfwGetKey(win->window, GLFW_KEY_I))
        	apply_projection(win, 2);
		if (glfwGetKey(win->window, GLFW_KEY_H))
        	change_height(win, 0.01f);
		if (glfwGetKey(win->window, GLFW_KEY_L))
        	change_height(win, -0.01f);
		*/