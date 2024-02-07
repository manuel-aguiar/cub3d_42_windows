/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:22:07 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:22:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_windows.h"

void	win_key_press(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}