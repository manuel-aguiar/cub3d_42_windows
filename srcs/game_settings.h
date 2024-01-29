/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:43:49 by marvin            #+#    #+#             */
/*   Updated: 2024/01/29 19:43:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_SETTINGS_H

# define GAME_SETTINGS_H



/* window settings */
# define MAX_WIN_WIDTH 1920
# define MIN_WIN_WIDTH 800
# define MAX_WIN_HEIGHT 1024
# define MIN_WIN_HEIGHT 600

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1024
# define WIN_NAME "Cub3d\0"

# define RGB_SIZE 4

# define RGBA(r, g, b, a) (((r) << 24) | ((g) << 16) | ((b) << 8) | (a))

/* compass settings */
# define COMP_CENTRE_X WIN_WIDTH / 6 
# define COMP_CENTRE_Y WIN_HEIGHT / 4 

# define COMP_MAX_RAD 300
# define COMP_MIN_RAD 50
# define COMP_OUTER_RAD WIN_HEIGHT / 5
# define COMP_INNER_COLOR RGBA(255, 0, 0, 255)
# define COMP_INNER_RAD_PERC 0.8f
# define COMP_LETTER_RAD_PERC 0.9f
# define COMP_COLOR RGBA(255, 0, 0, 255)

# define COMP_LETTER_HGT_PERC 0.1f
# define COMP_LETTER_WDT_PERC 0.05f
# define COMP_LETTER_COLOR RGBA(255, 255, 255, 255)

# define COMP_SQR_COLOR RGBA(255, 165, 0, 255)

/* compass squares */
# define SQR_MAX_HEIGHT_PERC 0.5f
# define SQR_MIN_HEIGHT_PERC 0.005f
# define SQR_HEIGHT_PERC 0.2f
# define COMP_PLAY_RAD 0.2f

/* player settings */
# define PLAY_UNIT_SIZE 0.2f
# define PLAY_FORWARD_MOVE_SENSE 0.003f
# define PLAY_SIDE_MOVE_SENSE 0.0015f
# define PLAY_BACK_MOVE_SENSE 0.0008f
# define PLAY_SPRINT_MULTI 1.5f
# define PLAY_BASE_PITCH 0
# define PLAY_BASE_Z_HEIGHT 0
# define PLAY_ROT_SENSE 0.00008f
# define PLAY_PITCH_SENSE PLAY_ROT_SENSE * 1200

#endif