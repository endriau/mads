//
// Created by p0int3r on 6/12/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl_tree.h"


#define	ALLOWED_IMBALANCE 1
#define HEIGHT(node) (node==NULL ? -1 : node->height)
#define MAX(a,b) (a > b ? a : b)


avl_tree_t *avl_tree_create(avl_tree_compare_fn cmp, avl_tree_print_fn print, avl_tree_destroy_fn destroy)
{
    avl_tree_t *new_tree=NULL;
    assert(cmp!=NULL && print!=NULL);
    new_tree=(avl_tree_t *)malloc(sizeof(*new_tree));
    assert(new_tree!=NULL);
    new_tree->root=NULL;
    new_tree->cmp=cmp;
    new_tree->print=print;
    new_tree->destroy=destroy;
    return new_tree;
}


static avl_node_t *avl_tree_rotate_with_left_child(avl_node_t *node)
{
    avl_node_t *rotate_node=NULL;
    rotate_node=node->left;
    node->left=rotate_node->right;
    rotate_node->right=node;
    node->height=MAX(HEIGHT(node->left),HEIGHT(node->right))+1;
    rotate_node->height=MAX(HEIGHT(rotate_node->left),node->height)+1;
    return rotate_node;
}


static avl_node_t *avl_tree_rotate_with_right_child(avl_node_t *node)
{
    avl_node_t *rotate_node=NULL;
    rotate_node=node->right;
    node->right=rotate_node->left;
    rotate_node->left=node;
    node->height=MAX(HEIGHT(node->left),HEIGHT(node->right))+1;
    rotate_node->height=MAX(HEIGHT(rotate_node->right),node->height)+1;
    return rotate_node;
}



static avl_node_t *avl_tree_double_with_left_child(avl_node_t *node)
{
    node->left= avl_tree_rotate_with_right_child(node->left);
    return avl_tree_rotate_with_left_child(node);
}


static avl_node_t *avl_tree_double_with_right_child(avl_node_t *node)
{
    node->right= avl_tree_rotate_with_left_child(node->right);
    return avl_tree_rotate_with_right_child(node);
}


static avl_node_t *avl_tree_balance(avl_node_t *node)
{
    if (node==NULL)
    {
        return node;
    }

    if (HEIGHT(node->left)-HEIGHT(node->right)>ALLOWED_IMBALANCE)
    {
        if (HEIGHT(node->left->left)>=HEIGHT(node->left->right))
        {
            node= avl_tree_rotate_with_left_child(node);
        }
        else
        {
            node= avl_tree_double_with_left_child(node);
        }
    }
    else if (HEIGHT(node->right)-HEIGHT(node->left)>ALLOWED_IMBALANCE)
    {
        if (HEIGHT(node->right->right)>=HEIGHT(node->right->left))
        {
            node= avl_tree_rotate_with_right_child(node);
        }
        else
        {
            node= avl_tree_double_with_right_child(node);
        }
    }
    else {}

    node->height=MAX(HEIGHT(node->left),HEIGHT(node->right))+1;
    return node;
}



static avl_node_t *avl_tree_recursive_insert(avl_node_t *node, avl_tree_compare_fn cmp, void *data)
{
    int compare=0;
    avl_node_t *new_node=NULL;
    assert(cmp!=NULL);

    if (node==NULL)
    {
        new_node=(avl_node_t *)malloc(sizeof(*new_node));
        assert(new_node!=NULL);
        new_node->data=data;
        new_node->left=NULL;
        new_node->right=NULL;
        new_node->height=0;
        return new_node;
    }

    compare=cmp(node->data,data);

    if (compare>0)
    {
        node->left= avl_tree_recursive_insert(node->left, cmp, data);
    }
    else if (compare<0)
    {
        node->right= avl_tree_recursive_insert(node->right, cmp, data);
    }
    else {}
    return avl_tree_balance(node);
}


void avl_tree_insert(avl_tree_t *t, void *data)
{
    assert(t!=NULL);
    t->root= avl_tree_recursive_insert(t->root, t->cmp, data);
}


static avl_node_t *avl_tree_recursive_search(avl_node_t *node, avl_tree_compare_fn cmp, void *item)
{
    int compare=0;
    assert(cmp!=NULL);
    if (node==NULL) { return node; }
    compare=cmp(node->data,item);

    if (compare>0)
    {
        return avl_tree_recursive_search(node->left, cmp, item);
    }
    else if (compare<0)
    {
        return avl_tree_recursive_search(node->right, cmp, item);
    }
    else
    {
        return node;
    }
}


int avl_tree_search(avl_tree_t *t, void *item)
{
    avl_node_t *query_node=NULL;
    assert(t!=NULL);
    query_node= avl_tree_recursive_search(t->root, t->cmp, item);
    return (query_node!=NULL ? 1 : 0);
}


void *avl_tree_get_elem(avl_tree_t *t, void *item)
{
    avl_node_t *query_node=NULL;
    assert(t!=NULL);
    query_node= avl_tree_recursive_search(t->root, t->cmp, item);
    return (query_node!=NULL ? query_node->data : NULL);
}


void *avl_tree_get_root(avl_tree_t *t)
{
    assert(t!=NULL);
    return (t->root!=NULL ? t->root->data : NULL);
}


static avl_node_t *avl_tree_find_min(avl_node_t *node)
{
    if (node==NULL)
    {
        return node;
    }

    while (node->left!=NULL)
    {
        node=node->left;
    }

    return node;
}


static avl_node_t *avl_tree_recursive_remove(avl_node_t *node, avl_tree_compare_fn cmp, avl_tree_destroy_fn destroy, void *item)
{
    int compare=0;
    assert(cmp!=NULL);
    if (node==NULL) { return node; }
    compare=cmp(node->data,item);

    if (compare>0)
    {
        node->left= avl_tree_recursive_remove(node->left, cmp, destroy, item);
    }
    else if (compare<0)
    {
        node->right= avl_tree_recursive_remove(node->right, cmp, destroy, item);
    }
    else
    {
        if (node->right==NULL && node->left==NULL)
        {
            if (destroy!=NULL)
            {
                destroy(node->data);
                node->data=NULL;
            }

            free(node);
            node=NULL;
        }
        else if (node->right!=NULL && node->left==NULL)
        {
            if (destroy!=NULL)
            {
                destroy(node->data);
                node->data=NULL;
            }

            avl_node_t *old_node=NULL;
            old_node=node;
            node=node->right;
            free(old_node);
            old_node=NULL;
        }
        else if (node->left!=NULL && node->right==NULL)
        {
            if (destroy!=NULL)
            {
                destroy(node->data);
                node->data=NULL;
            }

            avl_node_t *old_node=NULL;
            old_node=node;
            node=node->left;
            free(old_node);
            old_node=NULL;

        }
        else
        {
            avl_node_t *min_node=NULL;
            min_node= avl_tree_find_min(node->right);
            void *temp_data=NULL;
            temp_data=node->data;
            node->data=min_node->data;
            min_node->data=temp_data;
            node->right= avl_tree_recursive_remove(node->right, cmp, destroy, temp_data);

        }
    }

    return avl_tree_balance(node);
}


void avl_tree_remove(avl_tree_t *t, void *item)
{
    assert(t!=NULL);
    if (avl_tree_is_empty(t)) { return; }
    t->root= avl_tree_recursive_remove(t->root, t->cmp, t->destroy, item);
}


void avl_tree_remove_root(avl_tree_t *t)
{
    assert(t!=NULL);
    avl_tree_remove(t, t->root->data);
}


int avl_tree_is_empty(avl_tree_t *t)
{
    assert(t!=NULL);
    return (t->root==NULL ? 1 : 0);
}


int avl_tree_get_height(avl_tree_t *t)
{
    assert(t!=NULL);
    return (t->root==NULL ? -1 : t->root->height);
}



static void avl_tree_recursive_print(avl_node_t *node, avl_tree_print_fn print, int depth)
{
    int i;
    assert(print!=NULL);
    if (node==NULL) { return; }
    avl_tree_recursive_print(node->right, print, depth + 1);
    for (i=0;i<depth;i++) { printf("	"); }
    print(node->data);
    printf("\n");
    avl_tree_recursive_print(node->left, print, depth + 1);
}


void avl_tree_print(avl_tree_t *t)
{
    assert(t!=NULL);
    printf("----------AVL TREE----------\n");
    printf("Height = %d\n", avl_tree_get_height(t));
    avl_tree_recursive_print(t->root, t->print, 0);
    printf("-------------END-------------\n");
}

void avl_tree_free(avl_tree_t *t)
{
    assert(t!=NULL);
    while (!avl_tree_is_empty(t)) { avl_tree_remove_root(t); }
    t->cmp=NULL;
    t->print=NULL;
    t->destroy=NULL;
    free(t);
    t=NULL;
}
