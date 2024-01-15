/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:31 by marvin            #+#    #+#             */
/*   Updated: 2024/01/11 14:43:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>

void	print_map(t_parsing *parsing)
{
	t_uint i;

	i = 0;
	while (i < parsing->map_height * parsing->map_width)
	{
		if (i % parsing->map_width == 0)
			printf("\n");
		printf("%c", parsing->map[i]);
		i++;
	}
}

int	list_to_map(t_parsing *parsing)
{
	int			i;
	t_gnl_len	*gnl;

	parsing->map = malloc(sizeof(*(parsing->map)) * parsing->map_height * parsing->map_width);
	if (!parsing->map)
		return (perror_msg_int("malloc", 0));
	i = 0;
	while (parsing->list->head)
	{
		gnl = (t_gnl_len *)parsing->list->head->data;
		ft_memcpy(&parsing->map[i * parsing->map_width], gnl->line, gnl->len);
		ft_memset(&parsing->map[i * parsing->map_width + gnl->len], ' ', parsing->map_width - gnl->len);
		vdmlist_del_head(parsing->list, free_gnl_len);
		i++;
	}
	vdmlist_destroy(&parsing->list, free_gnl_len);
	return (1);
}

int	is_only_spaces(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int trim_end_space_check_chars(t_parsing *parsing, t_gnl_len *gnl, char *charset)
{	
	t_uint		len;
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


int	get_map_dimensions(t_parsing *parsing)
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

int	get_texture_index(char *cmp)
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
	return (-1);
}

int	separate_textures(t_parsing *parsing)
{
	int		nbr_tex;
	int		index_tex;
	char	**split;
	int		split_count;
	
	if (parsing->list->len <= 7)
		return (0);
	nbr_tex = 0;
	while (nbr_tex < TOTAL_TEXTURES)
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
			if (index_tex == -1)
			{
				ft_free_charmat_null(&split, free);
				return (0);
			}
			parsing->tex_data[index_tex] = split[1];
			split[1] = NULL;
			ft_free_charmat_null(&split, free);
			nbr_tex++;
		}
		vdmlist_del_head(parsing->list, free_gnl_len);
	}
	return (1);
}



int file_to_list(t_parsing *parsing)
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

void	gnl_len_print_line(void	*str)
{
	t_gnl_len *new;

	new = (t_gnl_len *)str;
	if (new->line)
		ft_putstr(new->line);
}

void	free_parsing_contents(t_parsing *parsing)
{
	vdmlist_destroy(&parsing->list, free_gnl_len);
}

void	print_tex_data(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (i < TOTAL_TEXTURES)
		printf("%s\n", parsing->tex_data[i++]);
}

int main2(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_parsing	parsing;
	
	if (ac != 2)
		return (0 & ft_printf_fd(STDERR_FILENO, "cub3d: invalid number of arguments\n"));
	parsing = (t_parsing){};
	parsing.file = av[1];
	if (file_to_list(&parsing))
	{
		if (!separate_textures(&parsing))
			return (error_msg_int("cub3d: bad input textures\n", 2, 0));
		if (!get_map_dimensions(&parsing))
			return (error_msg_int("cub3d: bad map characters\n", 2, 0));
		if (!list_to_map(&parsing))
			return (1);
		
		print_tex_data(&parsing);
		free_parsing_contents(&parsing);
		printf("map dimensions: %dx%d\n", parsing.map_height, parsing.map_width);
		print_map(&parsing);
	}
	return (0);
}

int main(void)
{
	t_win_glfw *win;

	win = win_init_window();

	win_render(win, &win_key_press);

	win_free_glfw(win);
	return (0);
}

/*

minimap
	use xiaoulin-wu line algorithm to do antialiasing
	use liang-barsky to filter points inside and outside of the mini-map area




*/