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
		game->player_angle_rad = 0;
	if (direction == 'S')
		game->player_angle_rad = 1;
	if (direction == 'E')
		game->player_angle_rad = 0.5f;
	if (direction == 'W')
		game->player_angle_rad = -0.5f;
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
	game->player_position.x = (float)map_col(&game->map, i) + 0.5f;
	game->player_position.y = (float)map_row(&game->map, i) + 0.5f;
	game_starting_angle(game, game->map.map[i]);
}

int	new_win_init_window(t_win_glfw *win);

int		game_start(t_game *game, char *game_config)
{
	*game = (t_game){};
	if (!map_parsing(&game->map, game_config))
		return (0);									//unprotected
	game_find_player(game);
	compass_template_setup(&game->compass, game->player_angle_rad);
	new_win_init_window(&game->win);
	return (1);
}

