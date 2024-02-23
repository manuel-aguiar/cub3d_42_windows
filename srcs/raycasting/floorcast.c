/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:51:01 by marvin            #+#    #+#             */
/*   Updated: 2024/02/07 15:51:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

static inline float	float_ternary(bool cond, float yes, float no)
{
	if (cond)
		return (yes);
	return (no);
}

typedef struct s_floor_line
{
	t_xpm_tex	*tex;
	int			win_h;
	int			win_w;
	t_vector	ray_left;
	t_vector	ray_right;
	float		row_z;
	float		pitch_mod;
	float		row_dist;
	float		tile_exact_x;
	float		tile_exact_y;
	float		tile_step_x;
	float		tile_step_y;
	int			tile_x;
	int			tile_y;
	int			tex_pix_x;
	int			tex_pix_y;
	int			color;
	float		shade_wgt;
}	t_floor_line;

static inline void setup_common_floor_line(t_game *game, t_floor_line *line)
{
	t_vector	dir;

	dir = vector_multi(vector_multi(game->player.dir_vec, game->player.cur_dir_len), -1);
	line->win_h = game->win.height;
	line->win_w = game->win.width;
	line->ray_left = vector_add(dir, game->player.plane);
	line->ray_right = vector_sub(dir, game->player.plane);
	line->row_z = (game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * line->win_h;
	line->pitch_mod = line->win_h / 2 + game->player.pitch;
}

static inline void setup_common_ceiling_line(t_game *game, t_floor_line *line)
{
	t_vector	dir;

	dir = vector_multi(vector_multi(game->player.dir_vec, game->player.cur_dir_len), 1);
	line->win_h = game->win.height;
	line->win_w = game->win.width;
	line->ray_left = vector_add(dir, game->player.plane);
	line->ray_right = vector_sub(dir, game->player.plane);
	line->row_z = (1 - (game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod)) * line->win_h;
	line->pitch_mod = line->win_h / 2 + game->player.pitch;
}

static inline void setup_this_floor_line(t_game *game, t_floor_line *line, int y)
{
	int	this_pitch;

	this_pitch = y - line->pitch_mod;
	line->row_dist = float_ternary(ft_fabs(line->pitch_mod) < 0.0001f, 2000, line->row_z / this_pitch);
	game->verti_rays[y].row_distance = line->row_dist;
	line->tile_step_x = line->row_dist * (line->ray_right.x - line->ray_left.x) / line->win_w;
	line->tile_step_y = line->row_dist * (line->ray_right.y - line->ray_left.y) / line->win_w;
	line->tile_exact_x = game->player.map_posi.x + line->row_dist * line->ray_left.x;
	line->tile_exact_y = game->player.map_posi.y + line->row_dist * line->ray_left.y;
	line->shade_wgt = float_clamp(ft_fabs(line->row_dist / game->max_vis_dist \
		* game->player.cur_dir_len / game->player.base_dir_len), 0.0f, 1.0f);
}

static inline void setup_this_ceiling_line(t_game *game, t_floor_line *line, int y)
{
	int	this_pitch;

	this_pitch = y - line->pitch_mod;
	line->row_dist = float_ternary(ft_fabs(line->pitch_mod) < 0.0001f, 2000, line->row_z / this_pitch);
	game->verti_rays[y].row_distance = line->row_dist;
	line->tile_step_x = line->row_dist * (line->ray_right.x - line->ray_left.x) / line->win_w;
	line->tile_step_y = line->row_dist * (line->ray_right.y - line->ray_left.y) / line->win_w;
	line->tile_exact_x = game->player.map_posi.x + line->row_dist * line->ray_right.x;
	line->tile_exact_y = game->player.map_posi.y + line->row_dist * line->ray_right.y;
	line->shade_wgt = float_clamp(ft_fabs(line->row_dist / game->max_vis_dist \
		* game->player.cur_dir_len / game->player.base_dir_len), 0.0f, 1.0f);
}

void	floorcast(t_game *game)
{
	t_floor_line	line;
	t_xpm_tex 		*floor;
	int x;
	int	y;
	int end;
	
	ft_memset(game->verti_rays, 0, game->win.height);
	setup_common_floor_line(game, &line);
	
	floor = game->tex[F_TEX];
	end = ft_min(game->maxmin_hori, line.win_h - 1);
	y = 0;
	while (y < end)
	{
		setup_this_floor_line(game, &line, y);
		x = 0;
		while(x < line.win_w)
		{
			line.tile_x = (int)(line.tile_exact_x);
			line.tile_y = (int)(line.tile_exact_y);
			line.tex_pix_x = ft_abs((int)(floor->width * (line.tile_exact_x - line.tile_x)) % floor->width);
			line.tex_pix_y = ft_abs((int)(floor->height * (line.tile_exact_y - line.tile_y)) % floor->height);
			line.tile_exact_x += line.tile_step_x;
			line.tile_exact_y += line.tile_step_y;
			line.color = floor->pixels[floor->width * (floor->height - line.tex_pix_y - 1) + line.tex_pix_x];
			line.color = add_shade(line.color, line.shade_wgt);
			game->win.set_pixel(&game->win, x, y, line.color);
			x++;
			while(x < line.win_w && y >= game->hori_rays[x].min_y)
			{
				line.tile_exact_x += line.tile_step_x;
				line.tile_exact_y += line.tile_step_y;
				x++;
			}
		}
		y++;
	}
	setup_common_ceiling_line(game, &line);
	y = ft_max(game->minmax_hori + 1, 0);
	floor = game->tex[C_TEX];
	while (y < line.win_h)
	{
		setup_this_ceiling_line(game, &line, y);
		x = 0;
		while(x < line.win_w)
		{
			line.tile_x = (int)(line.tile_exact_x);
			line.tile_y = (int)(line.tile_exact_y);
			line.tex_pix_x = ft_abs((int)(floor->width * (line.tile_exact_x - line.tile_x)) % floor->width);
			line.tex_pix_y = ft_abs((int)(floor->height * (line.tile_exact_y - line.tile_y)) % floor->height);
			line.tile_exact_x -= line.tile_step_x;
			line.tile_exact_y -= line.tile_step_y;
			line.color = floor->pixels[floor->width * line.tex_pix_y + line.tex_pix_x];
			line.color = add_shade(line.color, line.shade_wgt);
			game->win.set_pixel(&game->win, x, y, line.color);
			x++;
			while(x < line.win_w && y <= game->hori_rays[x].max_y)
			{
				line.tile_exact_x -= line.tile_step_x;
				line.tile_exact_y -= line.tile_step_y;
				x++;
			}
		}
		y++;
	}
}