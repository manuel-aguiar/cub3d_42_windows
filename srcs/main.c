/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:31 by marvin            #+#    #+#             */
/*   Updated: 2024/01/11 14:43:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <stdio.h>

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_parsing	parsing;
	
	if (ac != 2)
		return (0 & ft_printf_fd(STDERR_FILENO, "cub3d: invalid number of arguments\n"));
	if (!parsing_input(&parsing, av[1]))
		return (1);
	return (0);
}

int main2(void)
{
	t_win_glfw *win;

	win = win_init_window();

	win_render(win, &win_key_press);

	win_free_glfw(win);
	return (0);
}
