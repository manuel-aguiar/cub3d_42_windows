/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GAME.C                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:51:29 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 10:51:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

int		char_in_set(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

void		game_starting_angle(t_game *game, char direction)
{
	if (direction == 'N')
		game->player.angle = - P_MY_PI / 2; 
	if (direction == 'S')
		game->player.angle = P_MY_PI / 2;
	if (direction == 'E')
		game->player.angle = 0;
	if (direction == 'W')
		game->player.angle = P_MY_PI;
	game->player.cos_rad = cosf(game->player.angle);
	game->player.sin_rad = sinf(game->player.angle);
}

int		map_row(t_map *map, int index)
{
	return (index / map->width);
}	

int		map_col(t_map *map, int index)
{
	return (index % map->width);
}

void		game_find_player(t_game *game)
{
	int i;

	i = 0;
	while (i < game->map.len)
	{
		if (char_in_set(game->map.map[i], VALID_START_POSI))
			break ;
		i++;
	}
	game->player.map_posi.x = (float)map_col(&game->map, i) + 0.5f;
	game->player.map_posi.y = (float)map_row(&game->map, i) + 0.5f;
	game_starting_angle(game, game->map.map[i]);
}

int	new_win_init_window(t_win_glfw *win);

int		game_start(t_game *game, char *game_config)
{
	*game = (t_game){};
	if (!map_parsing(&game->map, game_config))
		return (0);
	game_find_player(game);
	compass_template_setup(&game->compass, radian_truncate(-game->player.angle));
	setup_player(&game->player, 0.2f, game->player.angle);
	new_win_init_window(&game->win);
	return (1);
}

