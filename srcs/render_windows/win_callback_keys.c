/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_callback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:16:54 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:16:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_windows.h"

void	key_release(int keycode)
{
	if (keycode == KEY_ESC)
		g_keys &= ~(1 << BIT_ESC);
	else if (keycode == KEY_FRONT)
		g_keys &= ~(1 << BIT_FRONT);
	else if (keycode == KEY_BACK)
		g_keys &= ~(1 << BIT_BACK);
	else if (keycode == KEY_LEFT)
		g_keys &= ~(1 << BIT_LEFT);
	else if (keycode == KEY_RIGHT)
		g_keys &= ~(1 << BIT_RIGHT);
	else if (keycode == KEY_JUMP)
		g_keys &= ~(1 << BIT_JUMP);
	else if (keycode == KEY_SPRINT)
		g_keys &= ~(1 << BIT_SPRINT);
	else if (keycode == KEY_CROUCH)
		g_keys &= ~(1 << BIT_CROUCH);
	else if (keycode == KEY_PRONE)
		g_keys &= ~(1 << BIT_PRONE);
}

void	key_press(int keycode)
{
	if (keycode == KEY_ESC)
		g_keys |= (1 << BIT_ESC);
	else if (keycode == KEY_FRONT)
		g_keys |= (1 << BIT_FRONT);
	else if (keycode == KEY_BACK)
		g_keys |= (1 << BIT_BACK);
	else if (keycode == KEY_LEFT)
		g_keys |= (1 << BIT_LEFT);
	else if (keycode == KEY_RIGHT)
		g_keys |= (1 << BIT_RIGHT);
	else if (keycode == KEY_JUMP)
		g_keys |= (1 << BIT_JUMP);
	else if (keycode == KEY_SPRINT)
		g_keys |= (1 << BIT_SPRINT);
	else if (keycode == KEY_CROUCH)
		g_keys |= (1 << BIT_CROUCH);
	else if (keycode == KEY_PRONE)
		g_keys |= (1 << BIT_PRONE);
}



void	win_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
		key_press(key);
	else if (action == GLFW_RELEASE)
		key_release(key);
	
}