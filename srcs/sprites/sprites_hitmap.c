/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_hitmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:42:16 by marvin            #+#    #+#             */
/*   Updated: 2024/02/24 10:42:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	sprite_calc_dist(t_game *game)
{
	int i;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].status == GONE)
			game->sprites[i].dist = FLT_MAX;
		else
			game->sprites[i].dist = fpow_2(game->player.map_posi.x - game->sprites[i].posi.x) \
								 + fpow_2(game->player.map_posi.y - game->sprites[i].posi.y);
		i++;
	}
}

void	clean_hitnodes_and_map(t_game *game, t_sprite *sprite)
{
	int map_index;

	//map_index = (int)(sprite->posi.x) + (int)(sprite->posi.y) * game->map.width;
	//if (game->map.hit[map_index].len != 0)
	//	ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	map_index = (int)(sprite->posi.x - sprite->unit_size) + (int)(sprite->posi.y - sprite->unit_size) * game->map.width;
	if (game->map.hit[map_index].len != 0)
		ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	map_index = (int)(sprite->posi.x + sprite->unit_size) + (int)(sprite->posi.y + sprite->unit_size) * game->map.width;
	if (game->map.hit[map_index].len != 0)
		ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	map_index = (int)(sprite->posi.x - sprite->unit_size) + (int)(sprite->posi.y + sprite->unit_size) * game->map.width;
	if (game->map.hit[map_index].len != 0)
		ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	map_index = (int)(sprite->posi.x + sprite->unit_size) + (int)(sprite->posi.y - sprite->unit_size) * game->map.width;
	if (game->map.hit[map_index].len != 0)
		ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[0].next = NULL;
	sprite->my_hit[0].prev = NULL;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[1].next = NULL;
	sprite->my_hit[1].prev = NULL;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[2].next = NULL;
	sprite->my_hit[2].prev = NULL;
	sprite->my_hit[3].sprite = sprite;
	sprite->my_hit[3].next = NULL;
	sprite->my_hit[3].prev = NULL;
}

void    clean_hitmap(t_game *game)
{
	int         i;
	t_sprite    *sprite;

	//ft_memset(&game->map.hit[0], 0, sizeof(t_hitlist) * game->map.len);
	i = 0;
	while (i < game->sprite_count)
	{
		sprite = game->sorted[i];
		if (sprite->type == ENEMY)
			clean_hitnodes_and_map(game, sprite);
		i++;
	}
}

void	sprite_place_hitmap(t_game *game, t_sprite *sprite)
{
	int         map_index;

	if (sprite->type != ENEMY)
		return ;
	//map_index = (int)(sprite->posi.x) + (int)(sprite->posi.y) * game->map.width;
	//hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[0]);
	map_index = (int)(sprite->posi.x - sprite->unit_size) + (int)(sprite->posi.y - sprite->unit_size) * game->map.width;
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[0]);
	map_index = (int)(sprite->posi.x + sprite->unit_size) + (int)(sprite->posi.y + sprite->unit_size) * game->map.width;
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[1]);
	map_index = (int)(sprite->posi.x - sprite->unit_size) + (int)(sprite->posi.y + sprite->unit_size) * game->map.width;
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[2]);
	map_index = (int)(sprite->posi.x + sprite->unit_size) + (int)(sprite->posi.y - sprite->unit_size) * game->map.width;
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit[3]);
}

void    setup_hitmap(t_game *game)
{
	int         i;
	t_sprite    *sprite;

	sprite_calc_dist(game);
	sprite_qs_distance(game->sorted, game->sprite_count, sprite_qs_comp);
	i = 0;
	while (i < game->sprite_count)
	{
		sprite = game->sorted[i];
		if (sprite->type == ENEMY)
			sprite_place_hitmap(game, sprite);
		i++;
	}
	printf("hitmap done\n");
}

