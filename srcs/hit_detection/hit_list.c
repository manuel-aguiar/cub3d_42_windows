/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:11:55 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/02/24 10:07:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_detection.h"

void	hitlist_in_head(t_hitlist *list, t_hitnode *insert)
{
	if (list->head)
	{
		if (insert->sprite == list->head->sprite)
			return ;
		insert->next = list->head;
	}
	list->head = insert;
	++(list->len);
}
