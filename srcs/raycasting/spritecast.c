/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:05:50 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 13:05:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"


void	print_sorted_sprites(t_game *game)
{
	int i;

	i = 0;
	while (i < game->sprite_count)
	{
		printf("sprite %d, dist %.10f, posi (%.3f, %.3f)", game->sprites[i].type, game->sprites[i].dist, game->sprites[i].posi.x, game->sprites[i].posi.y);
		printf("cur_z %.3f, height %.3f, width %.3f, \n", game->sprites[i].cur_z, game->sprites[i].height, game->sprites[i].width);
		i++;
	}
}

typedef struct s_sp_cast
{
	int			win_w;
	int			win_h;
	t_vec2d		play_posi;
	t_vec2d		play_dir;
	t_vec2d		play_plane;
	float		inv_camera;
	float		pitch_mod;
	float		play_z_mod;
	t_sprite	*sprite;
	t_vec2d		relative;
	t_vec2d		trans;
	float		sp_z_mod;
	int			total_z_mod;
	int			centre_pix_x;
	int			sp_pix_h;
	int			sp_pix_w;
	int			bot_pix_y;
	int			top_pix_y;
	int			left_pix_x;
	int			right_pix_x;
	float		tex_exact_x;
	float		tex_exact_y;
	float		tex_step_x;
	float		tex_step_y;
	float		shade_wgt;
	int			tex_pix_x;
	int			tex_pix_y;
	t_xpm_tex 	*tex;
	int			color;
}	t_sp_cast;

void	setup_common_spritecast(t_game *game, t_sp_cast *cast)
{
	cast->win_w = game->win.width;
	cast->win_h = game->win.height;
	cast->play_posi = game->player.map_posi;
	cast->play_dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);
	cast->play_plane = game->player.plane;
	cast->pitch_mod = game->player.pitch;
	cast->play_z_mod = game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod;
	cast->inv_camera = 1.0f / (cast->play_plane.x * cast->play_dir.y - cast->play_plane.y * cast->play_dir.x);
	
}

/*

		float invDet = 1.0f / (game->player.plane.x * dir.y - game->player.plane.y * dir.x);
	
		tex = game->tex[game->sprites[i].tex];
		sprite_rel = vector_sub(game->sprites[i].posi, game->player.map_posi);
		transform.x = (dir.y * sprite_rel.x - dir.x * sprite_rel.y) / game->view_adj;
		transform.y = (-game->player.plane.y * sprite_rel.x + game->player.plane.x * sprite_rel.y) / game->view_adj;
		transform = vector_multi(transform, invDet);
		int spriteScreenX = (int)((w / 2) * (1 + transform.x / transform.y));
		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(h * game->sprites[i].height / (transform.y))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod + 0.5f - game->sprites[i].height / 2 - game->sprites[i].cur_z) * h - h / 2) / transform.y);
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod + 0.5f - game->sprites[i].height / 2 - game->sprites[i].cur_z) * h - h / 2) / transform.y);
		if(drawEndY >= h) drawEndY = h - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (w * game->sprites[i].unit_size * 2 / (transform.y)) );
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= w) drawEndX = w - 1;
		//printf("first stripe let's go\n");

*/

void	setup_this_spritecast(t_game *game, t_sp_cast *cast, int i)
{
	cast->sprite = game->sorted[i];
	cast->tex = game->tex[cast->sprite->tex];
	cast->relative = vector_sub(cast->sprite->posi, cast->play_posi);
	cast->trans.x = (cast->play_dir.y * cast->relative.x - cast->play_dir.x * cast->relative.y) / game->view_adj;
	cast->trans.y = (-cast->play_plane.y * cast->relative.x + cast->play_plane.x * cast->relative.y) / game->view_adj;
	cast->trans = vector_multi(cast->trans, cast->inv_camera);
	cast->sp_z_mod = (0.5f - cast->sprite->height / 2 - cast->sprite->cur_z);
	cast->centre_pix_x = (int)((cast->win_w / 2) * (1 + cast->trans.x / cast->trans.y));
	cast->sp_pix_h = ft_abs((int)(cast->win_h * cast->sprite->height / cast->trans.y));
	cast->sp_pix_w = ft_abs((int)(cast->win_w * cast->sprite->unit_size * 2 / cast->trans.y));
	cast->total_z_mod = cast->win_h / 2 + cast->pitch_mod \
		- (int)(((cast->play_z_mod + cast->sp_z_mod) * cast->win_h \
		- cast->win_h / 2) / cast->trans.y);
	cast->bot_pix_y = cast->total_z_mod - cast->sp_pix_h / 2;
	cast->top_pix_y = cast->total_z_mod + cast->sp_pix_h / 2;
	cast->left_pix_x = cast->centre_pix_x - cast->sp_pix_w / 2;
	cast->right_pix_x = cast->centre_pix_x + cast->sp_pix_w / 2;
	cast->tex_step_x = cast->tex->height / (float)cast->sp_pix_w;
	cast->tex_step_y = cast->tex->width / (float)cast->sp_pix_h;
	cast->tex_exact_x = 0;
	cast->tex_exact_y = 0;
	cast->shade_wgt = cast->trans.y / (game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
}


void	sprite_cast(t_game *game)
{
	t_sp_cast	cast;
	int			i;
	int			x;
	int			y;

	setup_common_spritecast(game, &cast);
	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sorted[i]->type == DOOR)
			doorcast(game, game->sorted[i]);
		if (game->sorted[i]->status != GONE)
		{
			setup_this_spritecast(game, &cast, i);

			if (cast.trans.y > 0)
			{
				cast.tex_exact_x = cast.tex_step_x * (0 - cast.left_pix_x) * (0 > cast.left_pix_x);
				x = ft_max(0, cast.left_pix_x);
				cast.right_pix_x = ft_min(cast.win_w - 1, cast.right_pix_x);
				while (x < cast.right_pix_x)
				{
					cast.tex_pix_x = (int)(cast.tex_exact_x);
					cast.tex_exact_x += cast.tex_step_x;
					if (cast.sprite->inverted)
						cast.tex_pix_x = cast.tex->height - cast.tex_pix_x - 1;
					if (x > 0 && x < cast.win_w && cast.trans.y < game->hori_rays[x].wall_dist)
					{
						cast.tex_exact_y = cast.tex_step_y * (0 - cast.bot_pix_y) * (0 > cast.bot_pix_y);
						y = ft_max(0, cast.bot_pix_y);
						cast.top_pix_y = ft_min(cast.win_h - 1, cast.top_pix_y);
						while (y < cast.top_pix_y)
						{
							cast.tex_pix_y = (int)(cast.tex_exact_y);
							cast.tex_exact_y += cast.tex_step_y;
							cast.color = cast.tex->pixels[cast.tex_pix_x * cast.tex->width + (cast.tex->width - cast.tex_pix_y - 1)];
							if (cast.color != 255)
							{
								cast.color = add_shade(cast.color, cast.shade_wgt);
								game->win.set_pixel(&game->win, x, y, cast.color);
							}
							
							//printf("placing %d, %d\n", x, y);
							
							y++;
						}
					}
					x++;
				}
			}
			
			
		
		}
		i++;
	}
}

/*

void	sprite_cast(t_game *game)
{

	int	i;
	int w = game->win.width;
	int h = game->win.height;
	t_xpm_tex 	*tex;
	t_vec2d	sprite_rel;
	t_vec2d	transform;
	t_vec2d	dir = vector_multi(game->player.dir_vec, game->player.cur_dir_len);

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].type == DOOR)
			doorcast(game, &game->sprites[i]);
		else
		{
			float invDet = 1.0f / (game->player.plane.x * dir.y - game->player.plane.y * dir.x);
		
			tex = game->tex[game->sprites[i].tex];
			sprite_rel = vector_sub(game->sprites[i].posi, game->player.map_posi);
			transform.x = (dir.y * sprite_rel.x - dir.x * sprite_rel.y) / game->view_adj;
			transform.y = (-game->player.plane.y * sprite_rel.x + game->player.plane.x * sprite_rel.y) / game->view_adj;
			transform = vector_multi(transform, invDet);
			int spriteScreenX = (int)((w / 2) * (1 + transform.x / transform.y));
			//calculate height of the sprite on screen
			int spriteHeight = abs((int)(h * game->sprites[i].height / (transform.y))); //using 'transformY' instead of the real distance prevents fisheye
			//calculate lowest and highest pixel to fill in current stripe
			int drawStartY = -spriteHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod + 0.5f - game->sprites[i].height / 2 - game->sprites[i].cur_z) * h - h / 2) / transform.y);
			if(drawStartY < 0) drawStartY = 0;
			int drawEndY = spriteHeight / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod + 0.5f - game->sprites[i].height / 2 - game->sprites[i].cur_z) * h - h / 2) / transform.y);
			if(drawEndY >= h) drawEndY = h - 1;

			//calculate width of the sprite
			int spriteWidth = abs( (int) (w * game->sprites[i].unit_size * 2 / (transform.y)) );
			int drawStartX = -spriteWidth / 2 + spriteScreenX;
			if(drawStartX < 0) drawStartX = 0;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
			if(drawEndX >= w) drawEndX = w - 1;
			//printf("first stripe let's go\n");

			

			for(int x = drawStartX; x < drawEndX; x++)
			{
				int texX = (int)((x - (-spriteWidth / 2 + spriteScreenX)) * tex->height / spriteWidth);
				if (game->sprites[i].inverted)
					texX = (tex->width - texX - 1);
				//the conditions in the if are:
				//1) it's in front of camera plane so you don't see things behind you
				//2) it's on the screen (left)
				//3) it's on the screen (right)
				//4) ZBuffer, with perpendicular distance
				if(transform.y > 0 && x > 0 && x < w && transform.y < game->hori_rays[x].wall_dist)
				{
					//printf("visible\n");
					for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
					{
						float d = (y - game->player.pitch + (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod + 0.5f - game->sprites[i].height / 2 - game->sprites[i].cur_z) * h - h / 2) / transform.y)) - h / 2 + spriteHeight / 2; //256 and 128 factors to avoid floats
						int texY = ((d * tex->width) / spriteHeight);
						int color = tex->pixels[texX * tex->width + (tex->width - texY - 1)]; //get current color from the texture
						//if (game->sprites[i].type == MEDIKIT)
						//{
						//	printf("x %d y %d, color %d, width %d height %d, index %d len %d\n", 
						//	texX, texY , color,tex->width, tex->height, texY * tex->width + (tex->width - texX - 1), tex->width* tex->height );
						//}
						
						//int color = rgba(0,0,255,255);
						//if (color != 255)
						//{
							color = add_shade(color, transform.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
							game->win.set_pixel(&game->win, x, y, color);
						//}
						//else
						//	game->win.set_pixel(&game->win, x, y, 0);
					}
				}
				//else
				//	printf("not visible\n");
			}
					//if (game->sprites[i].type == MEDIKIT)
					//	exit(0);
			
		}
		i++;
	}
}

*/