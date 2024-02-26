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

/*
		speed = player->cur_move_multi;
		if (player->is_sprinting && player->hgt_state == HGT_NORMAL && (g_keys >> BIT_FRONT) & 1)
			speed *= player->sprint_move_multi;
		player->cur_walk_sense += 0.015f * speed * player->timer[CLOCK_MOVE].elapsed;
		//printf("walk sense %.3f\n", player->cur_walk_sense);
		player->walk_z_mod += - sinf(player->cur_walk_sense) / (150 * ( 1 / speed));

		if (player->cur_walk_sense > 2 * MY_PI)
		{
			player->is_walking = false;
			player->walk_z_mod = 0;
		}
*/

void		update_ammokit(t_game *game, t_sprite *sprite)
{
	t_ammo *ammo;

	ammo = (t_ammo *)sprite->data;
	sprite->cur_z = ammo->base_z - game->float_sin * ammo->float_radius;
	if (sprite->dist <= game->player.unit_size \
	&& game->player.ammo[CTR_CUR] < game->player.ammo[CTR_MAX])
	{
		game->player.ammo[CTR_CUR] = ft_min(game->player.ammo[CTR_CUR] \
		+ ammo->ammopoints, game->player.ammo[CTR_MAX]);
		sprite->status = GONE;
	}

}

void		update_medikit(t_game *game, t_sprite *sprite)
{
	t_medi *medi;

	medi = (t_medi *)sprite->data;
	sprite->cur_z = medi->base_z - game->float_sin * medi->float_radius;
	if (sprite->dist <= game->player.unit_size \
	&& game->player.health[CTR_CUR] < game->player.health[CTR_MAX])
	{
		game->player.health[CTR_CUR] = ft_min(game->player.health[CTR_CUR] \
		+ medi->lifepoints, game->player.health[CTR_MAX]);
		sprite->status = GONE;
	}

}

void		update_enemy(t_game *game, t_sprite *sprite)
{
	t_enemy *enemy;

	enemy = (t_enemy *)sprite->data;
	if (enemy->health <= 0)
	{
		sprite->status = GONE;
		return ;
	}
	enemy->elapsed += game->player.timer[CLOCK_MOVE].elapsed;
	if (enemy->elapsed >= enemy->ms_to_swap)
		sprite->inverted = !sprite->inverted;
	enemy->elapsed %= enemy->ms_to_swap;
	if (enemy->attack_elapsed != -1)
		enemy->attack_elapsed += game->player.timer[CLOCK_MOVE].elapsed;
	if (enemy->attack_elapsed >= enemy->attack_time)
		enemy->attack_elapsed = -1;
	if (sprite->dist <= game->player.unit_size + sprite->unit_size)
	{
		if (enemy->attack_elapsed == -1)
		{
			game->player.health[CTR_CUR] = ft_max(game->player.health[CTR_CUR] - enemy->attack_val, 0);
			enemy->attack_elapsed = 0;
		}
	}
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

	clean_hitmap(game);
	sprite_calc_dist(game);
	sprite_qs_distance(game->sprites, game->sprite_count, sprite_qs_comp);

	game->floating += game->float_sense * game->player.timer[CLOCK_MOVE].elapsed;
	game->float_sin = sinf(game->floating);
	if (game->floating > 2 * MY_PI)
		game->floating -= 2 * MY_PI;
	//count_gone = 0;
	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].status == GONE)
		{
			ft_free_set_null(&game->sprites[i].data);
			//count_gone++;
		}
		else
		{
			
			if (game->sprites[i].type == DOOR)
				update_door(game, &game->sprites[i]);
			if (game->sprites[i].type == ENEMY)
				update_enemy(game, &game->sprites[i]);
			if (game->sprites[i].type == MEDIKIT)
				update_medikit(game, &game->sprites[i]);
			if (game->sprites[i].type == AMMOKIT)
				update_ammokit(game, &game->sprites[i]);
			if (game->sprites[i].status != GONE)
				sprite_place_hitmap(game, &game->sprites[i]);			
		}

		i++;
	}
	//game->sprite_count -= count_gone;
}

void		game_actions(t_game *game)
{
	//ft_memset(win->front_buf, 0, win->width * win->height * win->rgb_size * sizeof(*(win->front_buf)));
	player_get_timer(&game->player, CLOCK_MOVE);
	player_get_timer(&game->player, CLOCK_AIM);
	if ((*(game->keys) >> BIT_PAUSE_T) & 1 || (!((*(game->keys) >> BIT_PAUSE_T) & 1) && game->win.blur.elapsed > 0))
		return ;
	update_sprites(game);
	game_key_manager(game);
	game_mouse_manager(game);
	player_actions(game);
	
}

void	dda_visible_and_wallcast(t_game *game);

void		game_render(t_game *game)
{
	//t_pixel first = {300, 300, rgba(0, 0, 255, 255)};

	//player_start_timers(&game->player);
	//xpm_to_window(&game->win, game->tex[NO_TEX], first, game->tex[NO_TEX]->width, game->tex[NO_TEX]->height);
	//printf("dda visible next\n");
	if ((*(game->keys) >> BIT_PAUSE_T) & 0xff)
		window_pause_manager(&game->win, PAUSE_ON, (*(game->keys) >> BIT_BLUR_T) & 1);
	else if (game->win.blur.elapsed > 0)
		window_pause_manager(&game->win, PAUSE_OFF, (*(game->keys) >> BIT_BLUR_T) & 1);
	else
	{
		ft_memset(game->win.front_buf, 0, game->win.height * game->win.width * game->win.rgb_size);
		hori_raycasting(game);
		floorcast(game);


		sprite_cast(game);

		
		game->compass.blur_on = (*(game->keys) >> BIT_BLUR_T) & 1;
		if (((*game->keys) >> BIT_HUD_T) & 1)
		{
			render_compass(&game->win, &game->compass);
			render_map_inside_compass(game);
			render_player_inside_compass(game);
			render_stats_bars(game);
		}
		
		
	}
	game->win.set_pixel(&game->win, game->win.width / 2, game->win.height / 2, (unsigned int)-1);
}