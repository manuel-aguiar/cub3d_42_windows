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


# include "game.h"


int		win_render(t_game *game, t_win_glfw *win, void (*win_key_press)())
{			
	glfwSetKeyCallback(win->window, win_key_press);
	glViewport(0, 0, (*win).win_width, (*win).win_height);
	//set_fps_start(&win->fps);
    while (!glfwWindowShouldClose(win->window))
	{
		glRasterPos2f(-1, -1);
		ft_memset(win->front_buf, 0, WIN_WIDTH * WIN_HEIGHT * RGB_SIZE * sizeof(*(win->front_buf)));

		if (glfwGetKey(win->window, GLFW_KEY_Q))
			game_rotate_view_angle(game, -0.045f);
		if (glfwGetKey(win->window, GLFW_KEY_E))
			game_rotate_view_angle(game, 0.045f);

		move_player(&game->player, glfwGetKey(win->window, GLFW_KEY_W), glfwGetKey(win->window, GLFW_KEY_S), glfwGetKey(win->window, GLFW_KEY_A), glfwGetKey(win->window, GLFW_KEY_D));
		//if (glfwGetKey(win->window, GLFW_KEY_S))
        //	game->compass.map_centre.y--;
		//if (glfwGetKey(win->window, GLFW_KEY_W))
        //	game->compass.map_centre.y++;
		//if (glfwGetKey(win->window, GLFW_KEY_A))
        //	game->compass.map_centre.x--;
		//if (glfwGetKey(win->window, GLFW_KEY_D))
        //	game->compass.map_centre.x++;

        	
		game_render(game);

		glClear(GL_COLOR_BUFFER_BIT);
		//fps_calc_print(&win->fps);
        glDrawPixels(win->win_width, win->win_height, GL_RGBA, GL_UNSIGNED_BYTE, win->front_buf);
		//set_fps_start(&win->fps);
		glfwSwapBuffers(win->window);
        glfwPollEvents();
    }
	return (1);
}

/*
letters
	t_pixel centre = {1000, 500, 1000, ARGB(255, 0, 0, 255)};
	t_east east;
	init_east_letter(&east, centre, 67, 33, ARGB(255, 0, 0, 255));

	t_pixel wcent = {1000, 600, 1000, ARGB(255, 0, 0, 255)}; 

	t_west west;
	init_west_letter(&west, wcent, 67, 67, ARGB(255, 0, 0, 255));

	t_pixel ncent = {1000, 800, 1000, ARGB(255, 0, 0, 255)};
	t_north north;
	init_north_letter(&north, ncent, 67, 33, ARGB(255, 0, 0, 255));

	t_pixel scent = {1000, 400, 1000, ARGB(255, 0, 0, 255)};
	t_south south;
	init_south_letter(&south, scent, 67, 33, ARGB(255, 0, 0, 255)); 

		render_east_letter(win, &east);
		render_west_letter(win, &west);
		render_north_letter(win, &north);
		render_south_letter(win, &south);

*/

/*
circle

t_pixel hey = {200, 200, 1000, ARGB(255, 0, 0, 255)};
win_drawcircle_wo_antialiasing(win, hey, 300, ARGB(255, 0, 0, 255), 10);

*/

//GL_ARGB - rgb alpha, it is equivalent to mlx 4-byte format

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