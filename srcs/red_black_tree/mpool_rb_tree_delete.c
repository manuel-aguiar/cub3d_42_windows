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

static void rbtree_delete_recursive(t_rb_tree *tree, t_rb_node *cur_node)
{
    if (cur_node == tree->root)
        return;
    rbtree_delete_recursive(tree, cur_node->left);
    rbtree_delete_recursive(tree, cur_node->right);
    free(cur_node);
}

void rbtree_delete(t_rb_tree **tree)
{
    rbtree_delete_recursive(*tree, (*tree)->root);
    ft_free_set_null(tree);
}
