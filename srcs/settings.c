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

int 	g_def_keys;

void    apply_all_settings(t_game *game)
{
    game->wall_reflection = GAME_WALL_REFLECTION;
    game->float_sense = GAME_FLOAT_SENSE;

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
    game->compass.player_colour = COMP_PLAYER_COLOR;


    game->compass.blur_on = BLUR_ON;
    game->compass.blur = (t_blur){};
    game->compass.blur.max_kernel = BLUR_KERNEL_MAX;
    game->compass.blur.kernel_size = BLUR_KERNEL_SIZE;
    game->compass.blur.sigma = BLUR_KERNEL_SIGMA;

    game->win.blur = (t_pause_blur){};
    game->win.blur.max_kernel = BLUR_KERNEL_MAX;
    game->win.blur.kernel_size = BLUR_KERNEL_SIZE;
    game->win.blur.kernel_centre = game->win.blur.kernel_size / 2;
    game->win.blur.cur_sigma = WIN_MIN_SIGMA;
    game->win.blur.min_sigma = WIN_MIN_SIGMA;
    game->win.blur.max_sigma = WIN_MAX_SIGMA;
    game->win.blur.pause_time = WIN_PAUSE_TIME;
    game->win.blur.elapsed = 0;
    game->win.blur.rgb_size = game->win.rgb_size;
    game->win.blur.height = game->win.height;
    game->win.blur.width = game->win.width;
    //player settings

	game->player.forward_move = PLAY_FORWARD_MOVE_SENSE;
    game->player.side_move = PLAY_SIDE_MOVE_SENSE;
    game->player.back_move = PLAY_BACK_MOVE_SENSE;
    game->player.rot_sense = PLAY_ROT_SENSE;
    game->player.pitch_sense = PLAY_PITCH_SENSE;
	game->player.unit_size = PLAY_UNIT_SIZE;
	game->player.pitch = PLAY_BASE_PITCH;


    game->player.hgt_state = HGT_NORMAL;
    game->player.stance_z[HGT_NORMAL] = PLAY_HGT_NORMAL;
    game->player.stance_z[HGT_PRONE] = PLAY_HGT_PRONE;
    game->player.stance_z[HGT_CROUCH] = PLAY_HGT_CROUCH;    
    game->player.cur_z = game->player.stance_z[HGT_NORMAL];
    game->player.hgt_sense = PLAY_HGT_SENSE;


    game->player.base_fov = PLAY_BASE_FOV;
    game->player.cur_fov = game->player.base_fov;
    game->player.base_dir_len = PLAY_BASE_DIR_LEN;
    game->player.aim_dir_len = PLAY_AIM_DIR_LEN;
    game->player.cur_dir_len = game->player.base_dir_len;
    game->player.aim_sense = PLAY_AIM_SENSE;
    game->player.aim_rot_multi = PLAY_AIM_ROT_MULTI;


    game->player.cur_jump_sense = 0;
    game->player.vertical_gravity = PLAY_VERTICAL_GRAVITY;
	game->player.jump_init = PLAY_JUMP_INIT;
	game->player.jump_inc = PLAY_JUMP_INC;
	game->player.jump_press_cap = PLAY_JUMP_PRESS_CAP;
	game->player.jump_release_cap = PLAY_JUMP_RELEASE_CAP;
    game->player.jump_z_mod = 0;


	game->player.cur_move_multi = PLAY_NORMAL_MOVE_MULTI;
	game->player.move_multi[HGT_NORMAL] = PLAY_NORMAL_MOVE_MULTI;
	game->player.move_multi[HGT_CROUCH]= PLAY_CROUCH_MOVE_MULTI;
	game->player.move_multi[HGT_PRONE] = PLAY_PRONE_MOVE_MULTI;
    game->player.move_multi[HGT_JUMP] = 1.0f;
	game->player.aim_move_multi = PLAY_AIM_MOVE_MULTI;
    game->player.sprint_move_multi = PLAY_SPRINT_MOVE_MULTI;


    game->player.walking_gravity = PLAY_WALKING_GRAVITY;
    game->player.walk_radius = PLAY_WALK_RADIUS;
    game->player.crouch_radius = PLAY_CROUCH_RADIUS;
    game->player.prone_radius = PLAY_PRONE_RADIUS;



    game->player.cur_walk_sense = 0;
    game->player.walk_z_mod = 0;
    game->player.walk_sway_mod = 0;

    game->player.verti_angle = PITCH_ANGLE_BASE;
    game->player.verti_tan = tanf(game->player.verti_angle);
    game->player.verti_cos = cosf(game->player.verti_angle);
    game->player.verti_sin = sinf(game->player.verti_angle);
    game->player.verti_min = PITCH_ANGLE_MIN;
    game->player.verti_max = PITCH_ANGLE_MAX;
    game->player.verti_sense = VERTI_SENSE;
    // setting default keys;

    game->max_vis_dist = MAX_VISIBLE_DISTANCE;

    game->player.health[CTR_CUR] = PLAY_HEALTH_START;
    game->player.health[CTR_MIN] = PLAY_HEALTH_MIN;
    game->player.health[CTR_MAX] = PLAY_HEALTH_MAX;
    game->player.ammo[CTR_CUR] = PLAY_AMMO_START;
    game->player.ammo[CTR_MIN] = PLAY_AMMO_MIN;
    game->player.ammo[CTR_MAX] = PLAY_AMMO_MAX;
    game->player.attack = PLAY_BULLET_DAMAGE;

    //game->view_adj = (1 /((float)game->win.width / (float)game->win.height));
    game->view_adj = 1;

    game->template_door = (t_door){};
    game->template_door.move_sense = DOOR_MOVE_SENSE;
    game->template_door.dist_sense = fpow_2(DOOR_DIST_SENSE);

    game->template_ammo = (t_ammo){};
    game->template_ammo.ammopoints = AMMO_RESOURCE;
    game->template_ammo.unit_size = AMMO_UNIT;
    game->template_ammo.height = AMMO_HGT;
    game->template_ammo.float_radius = AMMO_FLOAT_RADIUS;
    game->template_ammo.width = AMMO_WDT;
    game->template_ammo.base_z = AMMO_Z;
    game->template_ammo.z_sense = AMMO_Z_SENSE;

    game->template_enemy = (t_enemy){};
    game->template_enemy.unit_size = ENEMY_UNIT;
    game->template_enemy.height = ENEMY_HGT;
    game->template_enemy.width = ENEMY_WDT;
    game->template_enemy.base_z = ENEMY_Z;
    game->template_enemy.z_sense = ENEMY_Z_SENSE;
    game->template_enemy.ms_to_swap = ENEMY_MS_SWAP;
    game->template_enemy.elapsed = 0;
    game->template_enemy.attack_val = ENEMY_ATTACK;
    game->template_enemy.health = ENEMY_HEALTH;
    game->template_enemy.attack_time = ENEMY_TIME_ATTACK;
    game->template_enemy.attack_elapsed = 0;

    game->template_exit = (t_exit){};
    game->template_exit.unit_size = EXIT_UNIT;
    game->template_exit.height = EXIT_HGT;
    game->template_exit.width = EXIT_WDT;
    game->template_exit.base_z = EXIT_Z;
    game->template_exit.z_sense = EXIT_Z_SENSE;

    game->template_medi = (t_medi){};
    game->template_medi.lifepoints = MEDI_RESOURCE;
    game->template_medi.unit_size = MEDI_UNIT;
    game->template_medi.height = MEDI_HGT;
    game->template_medi.width = MEDI_WDT;
    game->template_medi.float_radius = MEDI_FLOAT_RADIUS;
    game->template_medi.base_z = MEDI_Z;
    game->template_medi.z_sense = MEDI_Z_SENSE;

/*
	//game->floating += 0.015f * game->player.timer[CLOCK_MOVE].elapsed;
	//game->float_sin = sinf(game->floating);
	//game->float_sin = 0;
	//if (game->floating > 2 * MY_PI)
	//	game->floating -= 2 * MY_PI;*/

}