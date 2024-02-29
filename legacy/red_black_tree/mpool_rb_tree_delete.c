/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:35:50 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 20:35:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "red_black_tree_mpool.h"

/*

https://epaperpress.com/sortsearch/txt/rbtr.txt

*/


void rbtree_mpool_delete(t_rb_mpool_tree **tree)
{
    free((*tree)->all_nodes);
    ft_free_set_null(tree);
}
