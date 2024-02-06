/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_hashtable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:22:49 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 09:22:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "xpm_parser.h"


static int	rgb_to_rgba(int rgb)
{
	return ((rgb << 8) | 0xFF);
}

static int	ft_strcmp(void *s1, void *s2)
{
	int i;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;

	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
		i++;
	return (str1[i] - str2[i]);
}

static void	*free_xpm_tex(t_xpm_tex **tex)
{
	if (((*tex)->pixels))
		free((*tex)->pixels);
	ft_free_set_null(tex);
	return (NULL);
}

static int	hash_countchars(void *str)
{
	char	*here;
	int		res;

	here = (char *)str;
	res = 0;
	while (*here)
		res += *here++;
	return (res);
}

t_xpm_tex	*xpm_to_tex_hashtable(char *xpm[])
{
	t_xpm_tex	*tex;
	t_hashtable	*table;
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
	table = hashtable_init(color_count, hash_countchars, ft_strcmp);
	
	
	
	char 	*id;
	int		color;

	//printf("hashtable done\n");

	//get array of id and colors
	int i;
	int	j;

	i = 0;
	while (i < color_count)
	{
		//printf("loop\n");
		if (!xpm[1 + i])
			return (free_xpm_tex(&tex));		
		id = malloc(sizeof(char) * (id_len + 1));
		if (!id)
		{
			hashtable_destroy(&table, free, NULL);
			return (free_xpm_tex(&tex));
		}
		j = -1;
		while (++j < id_len)
			id[j] = xpm[1 + i][j];
		id[j] = '\0';
		while (xpm[1 + i][j] != '#')
			j++;
		if (!xpm[1 + i][j])
		{
			free(id);
			hashtable_destroy(&table, free, NULL);
			return (free_xpm_tex(&tex));
		}
		color = ft_atoi_base(&xpm[1 + i][j + 1], "0123456789ABCDEF");
		//printf("attempting to insert\n");
		if (!hashtable_insert(table, id, (void *)color))
		{
			printf("duplicates\n");
			free(id);
			hashtable_destroy(&table, free, NULL);
			return (free_xpm_tex(&tex));
		}
		//printf("inserted successfully\n");
		i++;
	}
	//printf("hey?\n");
	//translate image into pixel array
	int index;
	index = 0;
	i = 1 + color_count;
	id = malloc(sizeof(*id) * (id_len + 1));
	while (i < 1 + color_count + tex->height)
	{
		if (!xpm[i] || ! xpm[i][0])
		{
			free(id);
			hashtable_destroy(&table, free, NULL);
			return (free_xpm_tex(&tex));
		}
		j = 0;
		while (j < tex->width * id_len)
		{
			if (!xpm[i][j])
			{
				free(id);
				hashtable_destroy(&table, free, NULL);
				return (free_xpm_tex(&tex));
			}
			ft_strlcpy(id, &xpm[i][j], id_len + 1);
			
			if (!hashtable_return_value(table, id, &tex->pixels[index]))
			{
				printf("symbol unavailable, symbol is: [%s]\n", id);
				free(id);
				hashtable_destroy(&table, free, NULL);
				return (free_xpm_tex(&tex));
			}
			//tex->pixels[index] = (int)receive;
			//printf(" rgb %d ", tex->pixels[index]);
			tex->pixels[index] = rgb_to_rgba(tex->pixels[index]);
			//printf(" rgb   A   %d ", tex->pixels[index]);
			index++;
			j += id_len;
		}
		i++;
	}
	free(id);
	hashtable_destroy(&table, free, NULL);
	//free_xpm_pair(&id_color, color_count);
	//print_tex(tex);
	return (tex);
}
