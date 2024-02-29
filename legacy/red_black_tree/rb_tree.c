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

#include "red_black_tree.h"

/*

https://epaperpress.com/sortsearch/txt/rbtr.txt
*/

t_rb_tree *rbtree_new(int(*treeCompare)(char *a, char *b))
{
    t_rb_tree *tree;
    
	tree = malloc(sizeof(*tree));
	if (!tree)
		return (perror_msg_ptr("malloc", NULL));
    tree->compare = treeCompare;
    tree->root = &tree->sentinel;
    tree->sentinel.left = &tree->sentinel;
    tree->sentinel.right = &tree->sentinel;
    tree->sentinel.parent = NULL;
    tree->sentinel.rb_color = RB_BLACK;
    tree->sentinel.key[0] = '\0';
    tree->sentinel.rgb = 0;
    return (tree);
}

static void rotateLeft(t_rb_tree *tree, t_rb_node *x) {

    // rotate node x to left

    t_rb_node *y;
    
    y = x->right;
    x->right = y->left;
    if (y->left != &tree->sentinel)
        y->left->parent = x;

    // establish y->parent link
    if (y != &tree->sentinel) 
        y->parent = x->parent;
    if (x->parent)
    {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    else
        tree->root = y;

    // link x and y
    y->left = x;
    if (x != &tree->sentinel)
        x->parent = y;
}

static void rotateRight(t_rb_tree *tree, t_rb_node *x) {

    // rotate node x to right

    t_rb_node *y;
    
    y = x->left;

    // establish x->left link
    x->left = y->right;
    if (y->right != &tree->sentinel)
        y->right->parent = x;

    // establish y->parent link
    if (y != &tree->sentinel)
        y->parent = x->parent;
    if (x->parent)
    {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    }
    else
        tree->root = y;

    // link x and y
    y->right = x;
    if (x != &tree->sentinel)
        x->parent = y;
}

static void insertFixup(t_rb_tree *tree, t_rb_node *x) {

    // maintain RB_RED-black tree balance after inserting node x

    // check RB_RED-black properties

    t_rb_node *y;    

    while (x != tree->root && x->parent->rb_color == RB_RED) {
        // we have a violation
        if (x->parent == x->parent->parent->left) {
            y = x->parent->parent->right;
            if (y->rb_color == RB_RED) {

                // uncle is RB_RED
                x->parent->rb_color = RB_BLACK;
                y->rb_color = RB_BLACK;
                x->parent->parent->rb_color = RB_RED;
                x = x->parent->parent;
            } else {

                // uncle is RB_BLACK
                if (x == x->parent->right) {
                    // make x a left child
                    x = x->parent;
                    rotateLeft(tree, x);
                }

                // recolor and rotate
                x->parent->rb_color = RB_BLACK;
                x->parent->parent->rb_color = RB_RED;
                rotateRight(tree, x->parent->parent);
            }
        } else {

            // mirror image of above code
            y = x->parent->parent->left;
            if (y->rb_color == RB_RED) {

                // uncle is RB_RED
                x->parent->rb_color = RB_BLACK;
                y->rb_color = RB_BLACK;
                x->parent->parent->rb_color = RB_RED;
                x = x->parent->parent;
            } else {

                // uncle is RB_BLACK
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(tree, x);
                }
                x->parent->rb_color = RB_BLACK;
                x->parent->parent->rb_color = RB_RED;
                rotateLeft(tree, x->parent->parent);
            }
        }
    }
    tree->root->rb_color = RB_BLACK;
}

int rbtree_insert(t_rb_tree *tree, char *key, int color)
{

    t_rb_node *current;
    t_rb_node *parent;
    t_rb_node *new;

    // allocate node for data and insert in tree

    // find future parent
    current = tree->root;
    parent = 0;
    while (current != &tree->sentinel)
    {
        int rc = tree->compare(key, current->key);
        if (rc == 0)
            return (error_msg_int("RB, duplicate key", STDERR_FILENO, 0));
        parent = current;
        if (rc < 0)
            current = current->left;
        else
            current = current->right;
    }

    // setup new node
    new = malloc (sizeof(*new));
    if (!new)
        return (perror_msg_int("malloc", 0));
    new->parent = parent;
    new->left = &tree->sentinel;
    new->right = &tree->sentinel;
    new->rb_color = RB_RED;
    ft_strlcpy(new->key, key, sizeof(new->key));
    new->rgb = color;

    // insert node in tree
    if(parent)
    {
        if(tree->compare(key, parent->key) < 0)
            parent->left = new;
        else
            parent->right = new;
    }
    else
        tree->root = new;
    insertFixup(tree, new);
    return (1);
}

/*

void deleteFixup(t_rb_tree *tree, t_rb_node *x) {

    // maintain RB_RED-black tree balance after deleting node x

    t_rb_node *w;

    while (x != tree->root && x->rb_color == RB_BLACK)
    {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->rb_color == RB_RED) {
                w->rb_color = RB_BLACK;
                x->parent->rb_color = RB_RED;
                rotateLeft (tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->rb_color == RB_BLACK && w->right->rb_color == RB_BLACK) {
                w->rb_color = RB_RED;
                x = x->parent;
            } else {
                if (w->right->rb_color == RB_BLACK)
                {
                    w->left->rb_color = RB_BLACK;
                    w->rb_color = RB_RED;
                    rotateRight (tree, w);
                    w = x->parent->right;
                }
                w->rb_color = x->parent->rb_color;
                x->parent->rb_color = RB_BLACK;
                w->right->rb_color = RB_BLACK;
                rotateLeft (tree, x->parent);
                x = tree->root;
            }
        } else
        {
            w = x->parent->left;
            if (w->rb_color == RB_RED) {
                w->rb_color = RB_BLACK;
                x->parent->rb_color = RB_RED;
                rotateRight (tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->rb_color == RB_BLACK && w->left->rb_color == RB_BLACK) {
                w->rb_color = RB_RED;
                x = x->parent;
            } else
            {
                if (w->left->rb_color == RB_BLACK)
                {
                    w->right->rb_color = RB_BLACK;
                    w->rb_color = RB_RED;
                    rotateLeft (tree, w);
                    w = x->parent->left;
                }
                w->rb_color = x->parent->rb_color;
                x->parent->rb_color = RB_BLACK;
                w->left->rb_color = RB_BLACK;
                rotateRight (tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->rb_color = RB_BLACK;
}

*/

int rbtree_find(t_rb_tree *tree, char *key, int *place_val)
{
    t_rb_node   *current;
    int         comp;

    current = tree->root;
    while(current != &tree->sentinel)
    {
        comp = tree->compare(key, current->key);
        if (!comp)
        {
            *place_val = current->rgb;
            return (1);
        }
        if (comp < 0)
            current = current->left;
        else
            current = current->right;
    }
    return (0);
}