/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:37:46 by marvin            #+#    #+#             */
/*   Updated: 2024/01/22 10:37:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


static int	list_to_map(t_parsing *parsing)
{
	int			i;
	t_gnl_len	*gnl;

	parsing->map = malloc(sizeof(*(parsing->map)) * parsing->map_height * parsing->map_width);
	if (!parsing->map)
		return (perror_msg_int("malloc", 0));
	//printf("map height %d ength %d\n", parsing->map_height, parsing->map_width);
	i = 0;
	while (parsing->list->tail)
	{
		gnl = (t_gnl_len *)parsing->list->tail->data;
		//printf("length %d %s\n", gnl->len, gnl->line);
		ft_memcpy(&parsing->map[i * parsing->map_width], gnl->line, gnl->len);
		ft_memset(&parsing->map[i * parsing->map_width + gnl->len], ' ', parsing->map_width - gnl->len);
		vdmlist_del_tail(parsing->list, free_gnl_len);
		i++;
	}
	vdmlist_destroy(&parsing->list, free_gnl_len);
	return (1);
}

static int	is_only_spaces(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

static int trim_end_space_check_chars(t_parsing *parsing, t_gnl_len *gnl, char *charset)
{	
	int		len;
	char	*str;
	int		i;

	len = gnl->len;
	str = gnl->line;
	//printf("trimming line %s\n", str);
	//printf("line ends on a new line? %d, len %d,", (str[len - 1] == '\n'), len);
	len -= (str[len - 1] == '\n');
	//printf("now %d,", len);
	gnl->len = len;
	while (len && str[len - 1] == ' ')
		len--;
	if (!len)
		return (0);
	gnl->len = len;
	//printf("after spaces %d\n", len);
	parsing->map_width += (len - parsing->map_width) * (len > parsing->map_width);
	while (len)
	{
		i = 0;
		while (charset[i] && str[len - 1] != charset[i])
		{
			//printf("char '%c', str[%d] = '%c'\n", charset[i], len, str[len - 1]);
			i++;
		}
			
		if (!charset[i] || (i >= 2 && i <= 5 && parsing->found_player))
		{
			//printf("failed at line: '%s'\n", str);
			return (0);
		}
		if (i >= 2 && i <= 5)
			parsing->found_player = true;
		len--;
	}
	return (1);
}


static int	get_map_dimensions(t_parsing *parsing)
{
	t_vdmnode	*node;
	t_vdmnode	*save;

	node = parsing->list->head;
	while (node && is_only_spaces(((t_gnl_len *)(node->data))->line))
	{
		save = node;
		vdmlist_del_node(parsing->list, node, free_gnl_len);
		node = save->next;
	}
	if (!node)
		return (0);
	while (node && trim_end_space_check_chars(parsing, (t_gnl_len *)(node->data), VALID_MAP_CHARS))
		node = node->next;
	//printf("helllo?\n");
	while (node && is_only_spaces(((t_gnl_len *)(node->data))->line))
	{
		
		save = node;
		vdmlist_del_node(parsing->list, node, free_gnl_len);
		node = save->next;
		//printf("loop, is there next? %d\n", node != NULL);
		//if (node)
			//printf("next line is '%s'\n", (((t_gnl_len *)(node->data))->line));
	}
	//printf("brahbrah\n");
	if (node)
		return (0);
	parsing->map_height = parsing->list->len;
	//printf("heyhey?\n");
	return (1);
}

static int	get_texture_index(char *cmp)
{
	if (!ft_strncmp(cmp, "NO", 3))
		return (NO_TEX);
	if (!ft_strncmp(cmp, "SO", 3))
		return (SO_TEX);
	if (!ft_strncmp(cmp, "WE", 3))
		return (WE_TEX);
	if (!ft_strncmp(cmp, "EA", 3))
		return (EA_TEX);
	if (!ft_strncmp(cmp, "F", 2))
		return (F_TEX);
	if (!ft_strncmp(cmp, "C", 2))
		return (C_TEX);	
	if (!ft_strncmp(cmp, "MEDI", 5))
		return (MEDI_TEX);	
	if (!ft_strncmp(cmp, "AMMO", 5))
		return (AMMO_TEX);	
	if (!ft_strncmp(cmp, "ENEMY", 6))
		return (ENEMY_TEX);
	if (!ft_strncmp(cmp, "BULLET", 7))
		return (BULLET_TEX);
	if (!ft_strncmp(cmp, "GUN", 4))
		return (GUN_TEX);
	if (!ft_strncmp(cmp, "EXIT", 4))
		return (EXIT_TEX);	
	return (-1);
}

static int	separate_textures(t_parsing *parsing)
{
	int		nbr_tex;
	int		index_tex;
	char	**split;
	int		split_count;
	
	if (parsing->list->len <= NUM_TEX)
		return (0);
	nbr_tex = 0;
	while (nbr_tex < NUM_TEX)
	{
		if (!parsing->list->head)
			return (0);
		split = ft_split_count(((t_gnl_len *)(parsing->list->head->data))->line, "\t\v\n\r ", &split_count);
		if (!split)
			return (perror_msg_int("malloc", 0));
		if (!split_count)
			ft_free_charmat_null(&split, free);
		else 
		{
			if (split_count != 2)
				return ((size_t)ft_free_charmat_null(&split, free));
			index_tex = get_texture_index(split[0]);
			if (index_tex == -1 || parsing->tex_data[index_tex].path)
			{
				ft_free_charmat_null(&split, free);
				return(0);
			}
			
			
			parsing->tex_data[index_tex].path = split[1];
			split[1] = NULL;
			ft_free_charmat_null(&split, free);
			nbr_tex++;
		}
		vdmlist_del_head(parsing->list, free_gnl_len);
	}
	return (1);
}



static int file_to_list(t_parsing *parsing)
{
	parsing->file_len = ft_strlen(parsing->file);
	if (parsing->file_len < 4 || ft_strncmp(&parsing->file[parsing->file_len - 4], ".cub", 4))
		return (error_msg_int("cub3d: file format is invalid", STDERR_FILENO, 0));
	parsing->fd = open(parsing->file, O_RDONLY);
	if (parsing->fd == -1)
		return (perror_msg_int("open", 0));
	parsing->list = vdmlist_new();
	if (!parsing->list)
		return (0);
	while (1)
	{
		parsing->gnl = get_next_line_len(parsing->fd);
		if (!parsing->gnl)
		{
			close(parsing->fd);
			return (0);
		}
		if (parsing->gnl->line)
			vdmlist_in_tail(parsing->list, parsing->gnl);
		else
		{
			free_gnl_len(parsing->gnl);
			break ;
		}
	}
	close(parsing->fd);
	return (1);
}

void		dump_parsing_to_map(t_map *map, t_parsing *parsing)
{
	int i;
	*map = (t_map){};
	map->map = parsing->map;
	map->height = parsing->map_height;
	map->width = parsing->map_width;
	i = 0;
	while (i < NUM_TEX)
	{
		map->tex_data[i] = parsing->tex_data[i];
		i++;
	}
	map->len = map->width * map->height;	
}

int	map_parsing(t_map *map, char *av_file)
{
	t_parsing	parsing;

	parsing = (t_parsing){};
	parsing.file = av_file;
	if (file_to_list(&parsing))
	{
		
		if (!separate_textures(&parsing))
			return (error_msg_int("cub3d: bad input textures\n", 2, 0));
		if (!get_map_dimensions(&parsing))
			return (error_msg_int("cub3d: bad map characters\n", 2, 0));
		if (!list_to_map(&parsing))
			return (0);
		if (!analise_textures(&parsing))
			return (0);
		vdmlist_destroy(&parsing.list, free_gnl_len);
		print_tex_data(&parsing);
		printf("map dimensions: %dx%d\n", parsing.map_height, parsing.map_width);
		
	}

	dump_parsing_to_map(map, &parsing);
	print_map(map);

	return (1);
}


int		map_row(t_map *map, int index)
{
	return (index / map->width);
}	

int		map_col(t_map *map, int index)
{
	return (index % map->width);
}


void	free_map(t_map *map)
{
	int	i;

	free(map->map);
	i = 0;
	while (i < NUM_TEX)
	{
		if (map->tex_data[i].path)
			free(map->tex_data[i].path);
		i++;
	}
}
