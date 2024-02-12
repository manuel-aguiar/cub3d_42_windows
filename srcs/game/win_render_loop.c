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
	(void)win_key_press;
	glfwSetKeyCallback(win->window, win_key_callback);
	glfwSetMouseButtonCallback(win->window, win_mouse_button_callback);
	glfwSetScrollCallback(win->window, win_mouse_scroll_callback);
	glViewport(0, 0, win->width, win->height);
	glfwSetCursorPos(win->window, win->width / 2, win->height / 2);
	player_start_timers(&game->player);
	//set_fps_start(&win->fps);
    while (!glfwWindowShouldClose(win->window))
	{
		glRasterPos2f(-1, -1);
		ft_memset(win->front_buf, 0, win->width * win->height * win->rgb_size * sizeof(*(win->front_buf)));

		player_get_timer(&game->player, CLOCK_MOVE);
		player_get_timer(&game->player, CLOCK_AIM);
		

		glfwGetCursorPos(win->window, &game->mouse->cur_x, &game->mouse->cur_y);

		
		//printf("%d pitch change\n", (int)((mouse.y - win->height / 2) * game->player.pitch_sense * game->player.timer[CLOCK_MOVE].elapsed));



		
		//printf("rotate %.3f, rot sense %.10f, elapsed %u, res %.10f\n", rotate, game->player.rot_sense, 
		//game->player.timer[CLOCK_MOVE].elapsed, (float)(rotate * game->player.rot_sense * game->player.timer[CLOCK_MOVE].elapsed));
		

		//if (glfwGetKey(win->window, GLFW_KEY_X))
		//	game->player.z_height += 20;
		//if (glfwGetKey(win->window, GLFW_KEY_SPACE))
		//	game->player.z_height -= 20;

		player_actions(game);


		//player_jump_cur_z(&game->player);
		game_key_manager(game);
		game_mouse_manager(game);
		//if (glfwGetKey(win->window, GLFW_KEY_S))
        //	game->compass.map_centre.y--;
		//if (glfwGetKey(win->window, GLFW_KEY_W))
        //	game->compass.map_centre.y++;
		//if (glfwGetKey(win->window, GLFW_KEY_A))
        //	game->compass.map_centre.x--;
		//if (glfwGetKey(win->window, GLFW_KEY_D))
        //	game->compass.map_centre.x++;

        glfwSetCursorPos(win->window, win->width / 2, win->height / 2);	
		game_render(game);

		
		//printf("after redner\n");

		glClear(GL_COLOR_BUFFER_BIT);
		//fps_calc_print(&win->fps);
        glDrawPixels(win->width, win->height, GL_RGBA, GL_UNSIGNED_BYTE, win->front_buf);
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