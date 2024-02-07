/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:23:14 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:23:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


// globals required by GLFW

int 	g_keys;
t_mouse g_mouse;

void	game_setup_keys(t_game *game)
{
	game->mouse = &g_mouse;
	game->keys = &g_keys;
}