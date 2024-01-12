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
		vdmlist_in_tail(parsing->list, parsing->gnl);
		if (parsing->gnl->status == GNL_EOF)
			break ;
	}
	close(parsing->fd);
	return (1);
}

void	gnl_len_print_line(void	*str)
{
	t_gnl_len *new;

	new = (t_gnl_len *)str;
	ft_putstr(new->line);
}

void	free_parsing_contents(t_parsing *parsing)
{
	vdmlist_destroy(&parsing->list, free_gnl_len);
}

int main(int ac, char **av)
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
		vdmlist_head_print(parsing.list, gnl_len_print_line);
		free_parsing_contents(&parsing);
	}
	return (0);
}