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

void	setup_all_angles(t_game *game, float rad)
{
	game->player.angle = radian_truncate(rad);
	game->compass.angle = radian_truncate(-game->player.angle);
	game->player.cos_rad = cosf(game->player.angle);
	game->player.sin_rad = sinf(game->player.angle);
	game->compass.cos_rad = game->player.cos_rad;
	game->compass.sin_rad = -game->player.sin_rad;
	game->player.dir_vec = (t_vector){game->player.cos_rad, game->player.sin_rad};
	game->player.plane = vector_multi((t_vector){game->player.sin_rad, -game->player.cos_rad}, game->player.cur_fov);
	//printf("player rads %.3f, compass rads %.3f\n", game->player.angle, game->compass.angle);
	//printf("player cos sin (%.3f, %.3f)\n", game->player.cos_rad, game->player.sin_rad);
	//printf("compas cos sin (%.3f, %.3f)\n", game->compass.cos_rad, game->compass.sin_rad);
}

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
		setup_all_angles(game, P_MY_PI / 2); 
	if (direction == 'S')
		setup_all_angles(game, - P_MY_PI / 2);
	if (direction == 'E')
		setup_all_angles(game, 0);
	if (direction == 'W')
		setup_all_angles(game, P_MY_PI);
}

int		map_row(t_map *map, int index)
{
	return (index / map->width);
}	

int		map_col(t_map *map, int index)
{
	return (index % map->width);
}

void		game_find_player_set_angles(t_game *game)
{
	int i;

	i = 0;
	while (i < game->map.len)
	{
		if (char_in_set(game->map.map[i], VALID_STARt_vector))
			break ;
		i++;
	}
	game->player.map_posi.x = (float)map_col(&game->map, i) + 0.5f;
	game->player.map_posi.y = (float)map_row(&game->map, i) + 0.5f;
	game_starting_angle(game, game->map.map[i]);
}

int	new_win_init_window(t_win_glfw *win);

// GLOBALS NEEDED BY GLFW
void	player_start_timers(t_player *player);
void	player_get_timer(t_player *player, int timer);


int		game_start(t_game *game, char *game_config)
{
	*game = (t_game){};
	if (!map_parsing(&game->map, game_config))
		return (0);
	game_find_player_set_angles(game);
	apply_all_settings(game);
	compass_setup(&game->compass);
	player_setup(&game->player);
	new_win_init_window(&game->win);
	game_setup_keys(game);
	
	//didn t work, went slower even if better cache
	//game->hori_rays = malloc(sizeof(*game->hori_rays) * game->win.width);
	
	game->tex[NO_TEX] = xpm_to_tex_transposed(g_north);
	game->tex[SO_TEX] = xpm_to_tex_transposed(g_south);
	game->tex[EA_TEX] = xpm_to_tex_transposed(g_east);
	game->tex[WE_TEX] = xpm_to_tex_transposed(g_west);

	//player_start_timers(&game->player);
	////game->tex[F_TEX] = xpm_to_tex_hashtable(g_teste);
//
	//player_get_timer(&game->player, CLOCK_MOVE);
	//printf("dementor elapsed: %u\n", game->player.timer[CLOCK_MOVE].elapsed);

	//exit(0);
	game->tex[C_TEX] = NULL;
	//xpm_tex_transpose(game->teste);
	return (1);
}

