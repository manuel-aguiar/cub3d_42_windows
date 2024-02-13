/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:37:43 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 12:37:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void		update_enemy(t_game *game, t_sprite *sprite)
{
	t_enemy *enemy;

	enemy = (t_enemy *)sprite->data;
	enemy->elapsed += game->player.timer[CLOCK_MOVE].elapsed;
	if (enemy->elapsed >= enemy->ms_to_swap)
		sprite->inverted = !sprite->inverted;
	enemy->elapsed %= enemy->ms_to_swap;
}

void		update_door(t_game *game, t_sprite *sprite)
{
	t_door *door;
	float dist;

	door = (t_door *)sprite->data;
	dist = fpow_2(game->player.map_posi.x - door->base_position.x) \
								 + fpow_2(game->player.map_posi.y - door->base_position.y);
	if (dist < door->dist_sense)
	{
		if (door->orient == NS)
			sprite->posi.x = float_clamp(sprite->posi.x - door->move_sense * game->player.timer[CLOCK_MOVE].elapsed, door->base_position.x - 1.0f, door->base_position.x);
		else
			sprite->posi.y = float_clamp(sprite->posi.y - door->move_sense * game->player.timer[CLOCK_MOVE].elapsed, door->base_position.y - 1.0f, door->base_position.y);
	}
	else
	{
		if (door->orient == NS)
			sprite->posi.x = float_clamp(sprite->posi.x + door->move_sense * game->player.timer[CLOCK_MOVE].elapsed, door->base_position.x - 1.0f, door->base_position.x);
		else
			sprite->posi.y = float_clamp(sprite->posi.y + door->move_sense * game->player.timer[CLOCK_MOVE].elapsed, door->base_position.y - 1.0f, door->base_position.y);
	}
} 

void		update_sprites(t_game *game)
{
	int i;
	sprite_calc_dist(game);
	sprite_qs_distance(game->sprites, game->sprite_count, sprite_qs_comp);
	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].status == GONE && game->sprites[i].data)
			ft_free_set_null(&game->sprites[i].data);
		if (game->sprites[i].type == DOOR)
			update_door(game, &game->sprites[i]);
		if (game->sprites[i].type == ENEMY)
			update_enemy(game, &game->sprites[i]);
		i++;
	}

}

void		game_actions(t_game *game)
{
	t_win_glfw *win;

	win = &game->win;
	ft_memset(win->front_buf, 0, win->width * win->height * win->rgb_size * sizeof(*(win->front_buf)));
	player_get_timer(&game->player, CLOCK_MOVE);
	player_get_timer(&game->player, CLOCK_AIM);
	game_key_manager(game);
	game_mouse_manager(game);
	player_actions(game);
	update_sprites(game);
}

void		game_render(t_game *game)
{
	//t_pixel first = {300, 300, rgba(0, 0, 255, 255)};

	//player_start_timers(&game->player);
	//xpm_to_window(&game->win, game->tex[NO_TEX], first, game->tex[NO_TEX]->width, game->tex[NO_TEX]->height);
	//printf("dda visible next\n");


	dda_visible(game);
	//super_debug_print(game);
	floorcast_dda_visible(game);
	wallcast_dda_visible(game);
	sprite_cast(game);

	//exit(0);
	//floorcast(game);
	//wallcast(game);
	render_compass(&game->win, &game->compass);
	render_map_inside_compass(game);
	render_player_inside_compass(game);

}