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

void    clean_hitmap(t_game *game)
{
	int         i;
	int         map_index;
	t_sprite    *sprite;

	//ft_memset(&game->map.hit[0], 0, sizeof(t_hitlist) * game->map.len);
	i = 0;
	while (i < game->sprite_count)
	{
		sprite = &game->sprites[i];
		map_index = (int)sprite->posi.x
		+ (int)sprite->posi.y * game->map.width;
		if (game->map.hit[map_index].len != 0)
			ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
			//hitlist_del_tail(&game->map.hit[map_index]);
		sprite->my_hit.next = NULL;
		sprite->my_hit.prev = NULL;
		i++;
	}
}

void    setup_hitmap(t_game *game)
{
	int         i;
	int         map_index;
	t_sprite    *sprite;

	sprite_calc_dist(game);
	sprite_qs_distance(game->sprites, game->sprite_count, sprite_qs_comp);
	i = 0;
	while (i < game->sprite_count)
	{
		sprite = &game->sprites[i];
		map_index = (int)sprite->posi.x \
		+ (int)sprite->posi.y * game->map.width;
		hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit);
		i++;
	}
}

void	sprite_place_hitmap(t_game *game, t_sprite *sprite)
{
	int         map_index;

	sprite->my_hit.sprite = sprite;
	map_index = (int)sprite->posi.x \
		+ (int)sprite->posi.y * game->map.width;

	
	//if (map_index == 21 + 10 * game->map.width)
	//{
	//	printf("list len %d, head empty? %d, sprite %d, %d, map %d, %d\n",
	//	 game->map.hit[map_index].head == NULL,
	//	game->map.hit[map_index].len,
	//	(int)sprite->posi.x, 
	//	(int)sprite->posi.y, map_col(&game->map, map_index), map_row(&game->map, map_index));
	//	if (game->map.hit[map_index].len != 0)
	//		printf("BEFORE 21 10 head posi is %d %d\n",(int)game->map.hit[map_index].head->sprite->posi.x 
	//	,(int)game->map.hit[map_index].head->sprite->posi.y);
	//}
	
	hitlist_in_head(&game->map.hit[map_index], &sprite->my_hit);
	//if (map_index == 21 + 10 * game->map.width)
	//{
	//	printf("list len nowis %d  ", game->map.hit[map_index].len);
	//
	//	printf("AFTER 21 10 head posi is %d %d",(int)game->map.hit[map_index].head->sprite->posi.x 
	//	,(int)game->map.hit[map_index].head->sprite->posi.y);
	//	printf ("vs sprite posi %d %d\n\n", (int)sprite->posi.x, 
	//	(int)sprite->posi.y);
	//}
}