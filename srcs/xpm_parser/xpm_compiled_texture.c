/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_compiled_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:32:34 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 11:32:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "xpm_parser.h"

void	print_tex(t_xpm_tex *tex)
{
	printf("tex: width %d, height %d\n", tex->width, tex->height);
	int i;

	i = 0;
	while (i < tex->width * tex->height)
	{
		if (i % tex->width == 0)
			printf("\n");
		printf("index %d = %d    ", i, tex->pixels[i]);
		i++;
	}
	printf("\n");
}

void	print_xpm_pair(t_xpm_pair *id_color, int color_count)
{
	printf("id color:\n");
	int i;
	
	i = 0;
	while (i < color_count)
	{
		printf("id : [%s], color [%d]\n", id_color[i].id, id_color[i].color);
		i++;
	}
}

void	*free_xpm_tex(t_xpm_tex **tex)
{
	if (((*tex)->pixels))
		free((*tex)->pixels);
	ft_free_set_null(tex);
	return (NULL);
}

void	*free_xpm_pair(t_xpm_pair **id_color, int color_count)
{
	int			i;
	t_xpm_pair *og;

	og = *id_color;
	i = 0;
	while (i < color_count)
	{
		if (og[i].id)
			free(og[i].id);
		i++;
	}
	ft_free_set_null(id_color);
	return (NULL);
}

int		xpm_pair_has_dups(t_xpm_pair *id_color, int color_count, int id_len)
{
	int i;
	int	j;

	i = 0;
	while (i < color_count)
	{
		j = i + 1;
		while (j < color_count)
		{
			if (!ft_strncmp(id_color[i].id, id_color[j].id, id_len))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		color_at_target(t_xpm_pair *id_color, int color_count, char *target, int id_len)
{
	int	i;

	i = 0;
	while (i < color_count)
	{
		if (!ft_strncmp(target, id_color[i].id, id_len))
			return (id_color[i].color);
		i++;
	}
	return (-1);
}

int	rgb_to_rgba(int rgb)
{
	return ((rgb << 8) | 0xFF);
}

t_xpm_tex	*xpm_to_tex(char *xpm[])
{
	t_xpm_tex	*tex;
	t_xpm_pair	*id_color;
	char		**split;
	int			s_count;
	int			color_count;
	int			id_len;

	//get dimensions
	if (!xpm || ! xpm[0])
		return (NULL);
	tex = malloc(sizeof(*tex));
	if (!tex)
		return (NULL);
	*tex = (t_xpm_tex){};
	split = ft_split_count(xpm[0], " ", &s_count);
	if (!split)
		return (free_xpm_tex(&tex));
		
	if (s_count != 4)
	{
		ft_free_charmat_null(&split, free);
		return (free_xpm_tex(&tex));
	}
	tex->width = ft_atoi(split[0]);
	tex->height = ft_atoi(split[1]);
	color_count = ft_atoi(split[2]);
	id_len = ft_atoi(split[3]);
	ft_free_charmat_null(&split, free);
	if (tex->width <= 0 || tex->height <= 0 || color_count <= 0 || id_len <= 0)
		return (free_xpm_tex(&tex));
	tex->pixels = malloc(sizeof(*tex->pixels) * tex->width * tex->height);
	if (!tex->pixels)
		return (free_xpm_tex(&tex));
	id_color = ft_calloc(color_count, sizeof(*id_color));
	if (!id_color)
		return (free_xpm_tex(&tex));


	//get array of id and colors
	int i;
	int	j;

	i = 0;
	while (i < color_count)
	{
		if (!xpm[1 + i])
			return (free_xpm_tex(&tex));		
		id_color[i].id = malloc(sizeof(char) * (id_len + 1));
		if (!id_color[i].id)
		{
			free_xpm_pair(&id_color, color_count);
			return (free_xpm_tex(&tex));
		}
		j = -1;
		while (++j < id_len)
			id_color[i].id[j] = xpm[1 + i][j];
		id_color[i].id[j] = '\0';
		while (xpm[1 + i][j] != '#')
			j++;
		if (!xpm[1 + i][j])
		{
			free_xpm_pair(&id_color, color_count);
			return (free_xpm_tex(&tex));
		}
		id_color[i].color = ft_atoi_base(&xpm[1 + i][j + 1], "0123456789ABCDEF");
		i++;
	}
	if (xpm_pair_has_dups(id_color, color_count, id_len))
	{
		free_xpm_pair(&id_color, color_count);
		return (free_xpm_tex(&tex));
	}

	print_xpm_pair(id_color, color_count);

	//translate image into pixel array
	int index;
	index = 0;
	i = 1 + color_count;

	while (i < 1 + color_count + tex->height)
	{
		if (!xpm[i] || ! xpm[i][0])
		{
			free_xpm_pair(&id_color, color_count);
			return (free_xpm_tex(&tex));
		}
		j = 0;
		while (j < tex->width * id_len)
		{
			if (!xpm[i][j])
			{
				free_xpm_pair(&id_color, color_count);
				return (free_xpm_tex(&tex));
			}
			tex->pixels[index] = color_at_target(id_color, color_count, &xpm[i][j], id_len);
			//printf("at index %d, color is %d\n", index, tex->pixels[index]);
			if (tex->pixels[index] == -1)
			{
				free_xpm_pair(&id_color, color_count);
				return (free_xpm_tex(&tex));
			}
			//printf(" rgb %d ", tex->pixels[index]);
			tex->pixels[index] = rgb_to_rgba(tex->pixels[index]);
			//printf(" rgb   A   %d ", tex->pixels[index]);
			index++;
			j += id_len;
		}
		i++;
	}
	//free_xpm_pair(&id_color, color_count);
	//print_tex(tex);
	return (tex);
}

t_xpm_tex	*xpm_to_tex_transposed(char *xpm[])
{
	t_xpm_tex	*tex;
	t_xpm_pair	*id_color;
	char		**split;
	int			s_count;
	int			color_count;
	int			id_len;

	//get dimensions
	if (!xpm || ! xpm[0])
		return (NULL);
	tex = malloc(sizeof(*tex));
	if (!tex)
		return (NULL);
	*tex = (t_xpm_tex){};
	split = ft_split_count(xpm[0], " ", &s_count);
	if (!split)
		return (free_xpm_tex(&tex));
		
	if (s_count != 4)
	{
		ft_free_charmat_null(&split, free);
		return (free_xpm_tex(&tex));
	}
	tex->width = ft_atoi(split[0]);
	tex->height = ft_atoi(split[1]);
	color_count = ft_atoi(split[2]);
	id_len = ft_atoi(split[3]);
	ft_free_charmat_null(&split, free);
	if (tex->width <= 0 || tex->height <= 0 || color_count <= 0 || id_len <= 0)
		return (free_xpm_tex(&tex));
	tex->pixels = malloc(sizeof(*tex->pixels) * tex->width * tex->height);
	if (!tex->pixels)
		return (free_xpm_tex(&tex));
	id_color = ft_calloc(color_count, sizeof(*id_color));
	if (!id_color)
		return (free_xpm_tex(&tex));


	//get array of id and colors
	int i;
	int	j;

	i = 0;
	while (i < color_count)
	{
		if (!xpm[1 + i])
			return (free_xpm_tex(&tex));		
		id_color[i].id = malloc(sizeof(char) * (id_len + 1));
		if (!id_color[i].id)
		{
			free_xpm_pair(&id_color, color_count);
			return (free_xpm_tex(&tex));
		}
		j = -1;
		while (++j < id_len)
			id_color[i].id[j] = xpm[1 + i][j];
		id_color[i].id[j] = '\0';
		while (xpm[1 + i][j] != '#')
			j++;
		if (!xpm[1 + i][j])
		{
			free_xpm_pair(&id_color, color_count);
			return (free_xpm_tex(&tex));
		}
		id_color[i].color = ft_atoi_base(&xpm[1 + i][j + 1], "0123456789ABCDEF");
		i++;
	}
	if (xpm_pair_has_dups(id_color, color_count, id_len))
	{
		free_xpm_pair(&id_color, color_count);
		return (free_xpm_tex(&tex));
	}

	print_xpm_pair(id_color, color_count);

	//translate image into pixel array
	int offset = 1 + color_count;
	int row = 0;
	int col;
	//row + col * tex->height

	while (row < tex->height)
	{
		if (!xpm[row + offset] || ! xpm[row + offset][0])
		{
			free_xpm_pair(&id_color, color_count);
			return (free_xpm_tex(&tex));
		}
		col = 0;
		while (col < tex->width)
		{
			
			if (!xpm[row + offset][col * id_len])
			{
				free_xpm_pair(&id_color, color_count);
				return (free_xpm_tex(&tex));
			}
			tex->pixels[row + col * tex->height] = color_at_target(id_color, color_count, &xpm[row + offset][col * id_len], id_len);
			//printf("at index %d, color is %d\n", index, tex->pixels[index]);
			if (tex->pixels[row + col * tex->height] == -1)
			{
				free_xpm_pair(&id_color, color_count);
				return (free_xpm_tex(&tex));
			}
			//printf(" rgb %d ", tex->pixels[index]);
			tex->pixels[row + col * tex->height] = rgb_to_rgba(tex->pixels[row + col * tex->height]);
			//printf(" rgb   A   %d ", tex->pixels[index]);
			col++;
		}
		row++;
	}
	i = tex->width;
	tex->width = tex->height;
	tex->height = i;
	//free_xpm_pair(&id_color, color_count);
	//print_tex(tex);
	return (tex);
}

void	xpm_tex_transpose(t_xpm_tex *tex)
{
	int	*new_pixels;
	int	row;
	int	col;

	new_pixels = malloc(sizeof(*new_pixels) * tex->width * tex->height);
	// unprotected


	row = 0;
	while (row < tex->height)
	{
		col = 0;
		while( col < tex->width)
		{
			new_pixels[row + col * tex->height] = tex->pixels[col + row * tex->width];
			col++;
		}
		row++;
	}
	free(tex->pixels);
	tex->pixels = new_pixels;
	row = tex->width;
	tex->width = tex->height;
	tex->height = row;
}