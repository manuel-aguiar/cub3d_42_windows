/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:47:40 by marvin            #+#    #+#             */
/*   Updated: 2024/01/29 19:47:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"
# include "game_settings.h"

void    apply_all_settings(t_game *game)
{
    //window settings
    game->win.width = int_clamp(WIN_WIDTH, MIN_WIN_WIDTH, MAX_WIN_WIDTH);
    game->win.height = int_clamp(WIN_HEIGHT, MIN_WIN_HEIGHT, MAX_WIN_HEIGHT);
    game->win.rgb_size = RGB_SIZE;
    ft_memcpy(game->win.name, WIN_NAME, sizeof(game->win.name));

    //compass settings
    game->compass.centre = (t_pixel){COMP_CENTRE_X, COMP_CENTRE_Y, rgba(255,0,0,0)};
    game->compass.radius = int_clamp(COMP_OUTER_RAD, COMP_MIN_RAD, COMP_MAX_RAD);
    game->compass.color = COMP_COLOR;
    game->compass.inner.radius = game->compass.radius * COMP_INNER_RAD_PERC;
    game->compass.inner.color = COMP_INNER_COLOR;
    game->compass.letter_radius = game->compass.radius * COMP_LETTER_RAD_PERC;
    game->compass.letter_width = game->compass.radius * COMP_LETTER_WDT_PERC;
    game->compass.letter_height = game->compass.radius * COMP_LETTER_HGT_PERC;
    game->compass.letter_color = COMP_LETTER_COLOR;
    game->compass.sqr_color = COMP_SQR_COLOR;
    game->compass.sqr_height = int_clamp ((int)(game->compass.radius * SQR_HEIGHT_PERC), \
                            (int)(game->compass.radius * SQR_MIN_HEIGHT_PERC), \
                            (int)(game->compass.radius * SQR_MAX_HEIGHT_PERC));
    game->compass.map_centre = (t_pixel){WIN_WIDTH / 2, WIN_HEIGHT / 4, rgba(255,255,255,255)};			            //para testes
    game->compass.sqr.height = game->compass.sqr_height;
    game->compass.sqr.centre = (t_pixel){0, 0, game->compass.sqr_color};
    game->compass.sqr.color = game->compass.sqr_color;
    game->compass.sqr.biggest_z = 1 + sqrt((COMP_MAX_RAD * SQR_MAX_HEIGHT_PERC) * (COMP_MAX_RAD * SQR_MAX_HEIGHT_PERC) * 2);
    game->compass.player_rad = game->compass.sqr.height * COMP_PLAY_RAD;

    //player settings

	game->player.forward_move = PLAY_FORWARD_MOVE_SENSE;
    game->player.side_move = PLAY_SIDE_MOVE_SENSE;
    game->player.back_move = PLAY_BACK_MOVE_SENSE;
    game->player.rot_sense = PLAY_ROT_SENSE;
    game->player.pitch_sense = PLAY_PITCH_SENSE;
	game->player.unit_size = PLAY_UNIT_SIZE;
	game->player.pitch = PLAY_BASE_PITCH;
	game->player.z_height = PLAY_BASE_Z_HEIGHT;

}