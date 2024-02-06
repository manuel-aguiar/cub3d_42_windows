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

#ifndef RED_BLACK_TREE_H

# define RED_BLACK_TREE_H

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include "ft_string.h"
# include "ft_memfunc.h"
# include "error_handling.h"

typedef enum
{ 
	RB_BLACK, 
	RB_RED,
}	e_rb_color;


# define MAX_KEY_LEN 12

/* can use memory pool as linkedlist to guarantee locality*/


typedef struct s_rb_node
{
    
    char	key[MAX_KEY_LEN + 1];
    int		rgb;                // user data
	e_rb_color rb_color;            // node color (BLACK, RED)
    struct s_rb_node *left;       // left child
    struct s_rb_node *right;      // right child
    struct s_rb_node *parent;     // parent

}	t_rb_node;

typedef struct s_rb_tree
{
    t_rb_node *root;   // root of red-black tree
    t_rb_node sentinel;
    int (*compare)(char *a, char *b);    // compare keys
}	t_rb_tree;

t_rb_tree	*rbtree_new(int (*comp)(char *, char *));
void 		rbtree_delete(t_rb_tree **tree);
int			rbtree_insert(t_rb_tree *tree, char *key, int color);
int			rbtree_find(t_rb_tree *tree, char *key, int *place_val);

#endif