/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:11:15 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 17:11:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_MPOOL_H

# define RED_BLACK_TREE_MPOOL_H

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include "ft_string.h"
# include "ft_memfunc.h"
# include "error_handling.h"

typedef enum
{ 
	RB_MPOOL_BLACK, 
	RB_MPOOL_RED,
}	e_rb_mpool_color;


# define MAX_KEY_LEN 12

/* can use memory pool as linkedlist to guarantee locality*/


typedef struct s_rb_mpool_node
{
    char	key[MAX_KEY_LEN + 1];
    int		rgb;                // user data
	e_rb_mpool_color rb_color;            // node color (BLACK, RED)
    int me;
    int left;       // left child
    int right;      // right child
    int parent;     // parent

}	t_rb_mpool_node;

typedef struct s_rb_mpool_tree
{
    int         root;   // root of red-black tree
    int         sentinel;
    int (*compare)(char *a, char *b);    // compare keys
    int         size;
    int         used;
    t_rb_mpool_node   *all_nodes;
}	t_rb_mpool_tree;

t_rb_mpool_tree	*rbtree_mpool_new(int size, int (*comp)(char *, char *));
void 		rbtree_mpool_delete(t_rb_mpool_tree **tree);
int			rbtree_mpool_insert(t_rb_mpool_tree *tree, char *key, int color);
int			rbtree_mpool_find(t_rb_mpool_tree *tree, char *key, int *place_val);

#endif