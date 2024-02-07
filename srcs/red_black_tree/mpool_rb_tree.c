/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:24:30 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 20:24:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "red_black_tree_mpool.h"

/*

https://epaperpress.com/sortsearch/txt/rbtr.txt
*/

t_rb_mpool_tree *rbtree_mpool_new(int size, int(*comp)(char *a, char *b))
{
    t_rb_mpool_tree *tree;
    
	tree = malloc(sizeof(*tree));
	if (!tree)
		return (perror_msg_ptr("malloc", NULL));
    tree->all_nodes = malloc(sizeof(*tree->all_nodes) * (size + 1));
    if (!tree->all_nodes)
    {
        free(tree);
        return (NULL);
    }
    tree->size = size;
    tree->used = 1;
    tree->compare = comp;
    tree->root = 0;
    tree->sentinel = 0;
    tree->all_nodes[0].left = 0;
    tree->all_nodes[0].right = 0;
    tree->all_nodes[0].parent = 0;
    tree->all_nodes[0].rb_color = RB_MPOOL_BLACK;
    tree->all_nodes[0].key[0] = '\0';
    tree->all_nodes[0].rgb = 0;
    return (tree);
}

static void rotateLeft(t_rb_mpool_tree *tree, int new) {

    // rotate node new to left

    int cur;
    
    cur = tree->all_nodes[new].right;
    tree->all_nodes[new].right = tree->all_nodes[cur].left;
    if (tree->all_nodes[cur].left != tree->sentinel)
        tree->all_nodes[tree->all_nodes[cur].left].parent = new;

    // establish cur->parent link
    if (tree->all_nodes[cur].me != tree->sentinel) 
        tree->all_nodes[cur].parent = tree->all_nodes[new].parent;
    if (tree->all_nodes[new].parent)
    {
        if (new == tree->all_nodes[tree->all_nodes[new].parent].left)
            tree->all_nodes[tree->all_nodes[new].parent].left = cur;
        else
            tree->all_nodes[tree->all_nodes[new].parent].right = cur;
    }
    else
        tree->root = cur;

    // link new and cur
    tree->all_nodes[cur].left = new;
    if (new != tree->sentinel)
        tree->all_nodes[new].parent = cur;
}

static void rotateRight(t_rb_mpool_tree *tree, int new) {

    // rotate node new to right

    int cur;
    
    cur = tree->all_nodes[new].left;

    // establish new->left link
    tree->all_nodes[new].left = tree->all_nodes[cur].right;
    if (tree->all_nodes[cur].right != tree->sentinel)
        tree->all_nodes[tree->all_nodes[cur].right].parent = new;

    // establish cur->parent link
    if (cur != tree->sentinel)
        tree->all_nodes[cur].parent = tree->all_nodes[new].parent;
    if (tree->all_nodes[new].parent)
    {
        if (new == tree->all_nodes[tree->all_nodes[new].parent].right)
            tree->all_nodes[tree->all_nodes[new].parent].right = cur;
        else
            tree->all_nodes[tree->all_nodes[new].parent].left = cur;
    }
    else
        tree->root = cur;

    // link new and cur
    tree->all_nodes[cur].right = new;
    if (new != tree->sentinel)
        tree->all_nodes[new].parent = cur;
}

static void insertFixup(t_rb_mpool_tree *tree, int new) {

    // maintain RB_MPOOL_RED-black tree balance after inserting node x

    // check RB_MPOOL_RED-black properties

    int cur;    

    while (new != tree->root && tree->all_nodes[tree->all_nodes[new].parent].rb_color == RB_MPOOL_RED) {
        // we have a violation
        if (tree->all_nodes[new].parent == tree->all_nodes[tree->all_nodes[tree->all_nodes[new].parent].parent].left) {
            cur = tree->all_nodes[tree->all_nodes[tree->all_nodes[new].parent].parent].right;
            if (tree->all_nodes[cur].rb_color == RB_MPOOL_RED) {

                // uncle is RB_MPOOL_RED
                tree->all_nodes[tree->all_nodes[new].parent].rb_color = RB_MPOOL_BLACK;
                tree->all_nodes[cur].rb_color = RB_MPOOL_BLACK;
                tree->all_nodes[tree->all_nodes[tree->all_nodes[new].parent].parent].rb_color = RB_MPOOL_RED;
                new = tree->all_nodes[tree->all_nodes[new].parent].parent;
            } else {

                // uncle is RB_MPOOL_BLACK
                if (new == tree->all_nodes[tree->all_nodes[new].parent].right) {
                    // make new a left child
                    new = tree->all_nodes[new].parent;
                    rotateLeft(tree, new);
                }

                // recolor and rotate
                tree->all_nodes[tree->all_nodes[new].parent].rb_color = RB_MPOOL_BLACK;
                tree->all_nodes[tree->all_nodes[tree->all_nodes[new].parent].parent].rb_color = RB_MPOOL_RED;
                rotateRight(tree, tree->all_nodes[tree->all_nodes[new].parent].parent);
            }
        } else {

            // mirror image of above code
            cur = tree->all_nodes[tree->all_nodes[tree->all_nodes[new].parent].parent].left;
            if (tree->all_nodes[cur].rb_color == RB_MPOOL_RED) {

                // uncle is RB_MPOOL_RED
                tree->all_nodes[tree->all_nodes[new].parent].rb_color = RB_MPOOL_BLACK;
                tree->all_nodes[cur].rb_color = RB_MPOOL_BLACK;
                tree->all_nodes[tree->all_nodes[tree->all_nodes[new].parent].parent].rb_color = RB_MPOOL_RED;
                new = tree->all_nodes[tree->all_nodes[new].parent].parent;
            } else {

                // uncle is RB_MPOOL_BLACK
                if (new == tree->all_nodes[tree->all_nodes[new].parent].left) {
                    new = tree->all_nodes[new].parent;
                    rotateRight(tree, new);
                }
                tree->all_nodes[tree->all_nodes[new].parent].rb_color = RB_MPOOL_BLACK;
                tree->all_nodes[tree->all_nodes[tree->all_nodes[new].parent].parent].rb_color = RB_MPOOL_RED;
                rotateLeft(tree, tree->all_nodes[tree->all_nodes[new].parent].parent);
            }
        }
    }
    tree->all_nodes[tree->root].rb_color = RB_MPOOL_BLACK;
}

int rbtree_mpool_insert(t_rb_mpool_tree *tree, char *key, int color)
{

    int cur;
    int parent;
    int new;
    int comp;

    // allocate node for data and insert in tree

    // find future parent
    cur = tree->root;
    parent = 0;
    while (cur != tree->sentinel)
    {
        comp = tree->compare(key, tree->all_nodes[cur].key);
        if (comp == 0)
            return (error_msg_int("RB, duplicate key", STDERR_FILENO, 0));
        parent = cur;
        if (comp < 0)
            cur = tree->all_nodes[cur].left;
        else
            cur = tree->all_nodes[cur].right;
    }

    // setup new node
    new = tree->used;
    tree->all_nodes[new].me = tree->used++;
    tree->all_nodes[new].parent = parent;
    tree->all_nodes[new].left = tree->sentinel;
    tree->all_nodes[new].right = tree->sentinel;
    tree->all_nodes[new].rb_color = RB_MPOOL_RED;
    ft_strlcpy(tree->all_nodes[new].key, key, sizeof(tree->all_nodes[new].key));
    tree->all_nodes[new].rgb = color;

    // insert node in tree
    if(parent)
    {
        if(tree->compare(key, tree->all_nodes[parent].key) < 0)
            tree->all_nodes[parent].left = new;
        else
            tree->all_nodes[parent].right = new;
    }
    else
        tree->root = new;
    insertFixup(tree, new);
    return (1);
}


int rbtree_mpool_find(t_rb_mpool_tree *tree, char *key, int *place_val)
{
    int         cur;
    int         comp;

    cur = tree->root;
    while(cur != tree->sentinel)
    {
        comp = tree->compare(key, tree->all_nodes[cur].key);
        if (!comp)
        {
            *place_val = tree->all_nodes[cur].rgb;
            return (1);
        }
        if (comp < 0)
            cur = tree->all_nodes[cur].left;
        else
            cur = tree->all_nodes[cur].right;
    }
    return (0);
}