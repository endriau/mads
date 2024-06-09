// ReSharper disable CppDFANullDereference


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <mads/data_structures/avl_tree.h>


#define	MADS_AVL_TREE_ALLOWED_IMBALANCE 1
#define MADS_AVL_TREE_HEIGHT(node) (node==NULL ? -1 : node->height)
#define MADS_AVL_TREE_MAX(a,b) (a > b ? a : b)


mads_avl_tree_t *mads_avl_tree_create(const mads_avl_tree_compare_fn cmp, const mads_avl_tree_print_fn print, const mads_avl_tree_destroy_fn destroy)
{
    mads_avl_tree_t *new_tree = NULL;
    assert(cmp != NULL && print != NULL);
    new_tree = (mads_avl_tree_t *)malloc(sizeof(*new_tree));
    assert(new_tree != NULL);
    new_tree->root = NULL;
    new_tree->cmp = cmp;
    new_tree->print = print;
    new_tree->destroy = destroy;
    return new_tree;
}


static mads_avl_node_t *avl_tree_rotate_with_left_child(mads_avl_node_t *node)
{
    mads_avl_node_t *rotate_node = NULL;
    rotate_node = node->left;
    node->left = rotate_node->right;
    rotate_node->right = node;
    node->height = MADS_AVL_TREE_MAX(MADS_AVL_TREE_HEIGHT(node->left), MADS_AVL_TREE_HEIGHT(node->right)) + 1;
    rotate_node->height = MADS_AVL_TREE_MAX(MADS_AVL_TREE_HEIGHT(rotate_node->left), node->height) + 1;
    return rotate_node;
}


static mads_avl_node_t *avl_tree_rotate_with_right_child(mads_avl_node_t *node)
{
    mads_avl_node_t *rotate_node = NULL;
    rotate_node = node->right;
    node->right = rotate_node->left;
    rotate_node->left = node;
    node->height = MADS_AVL_TREE_MAX(MADS_AVL_TREE_HEIGHT(node->left), MADS_AVL_TREE_HEIGHT(node->right)) + 1;
    rotate_node->height = MADS_AVL_TREE_MAX(MADS_AVL_TREE_HEIGHT(rotate_node->right), node->height) + 1;
    return rotate_node;
}


static mads_avl_node_t *avl_tree_double_with_left_child(mads_avl_node_t *node)
{
    node->left = avl_tree_rotate_with_right_child(node->left);
    return avl_tree_rotate_with_left_child(node);
}


static mads_avl_node_t *avl_tree_double_with_right_child(mads_avl_node_t *node)
{
    node->right = avl_tree_rotate_with_left_child(node->right);
    return avl_tree_rotate_with_right_child(node);
}


static mads_avl_node_t *avl_tree_balance(mads_avl_node_t *node)
{
    if (node == NULL)
    {
        return node;
    }

    if (MADS_AVL_TREE_HEIGHT(node->left) - MADS_AVL_TREE_HEIGHT(node->right) > MADS_AVL_TREE_ALLOWED_IMBALANCE)
    {
        if (MADS_AVL_TREE_HEIGHT(node->left->left) >= MADS_AVL_TREE_HEIGHT(node->left->right))
        {
            node = avl_tree_rotate_with_left_child(node);
        }
        else
        {
            node = avl_tree_double_with_left_child(node);
        }
    }
    else if (MADS_AVL_TREE_HEIGHT(node->right) - MADS_AVL_TREE_HEIGHT(node->left) > MADS_AVL_TREE_ALLOWED_IMBALANCE)
    {
        if (MADS_AVL_TREE_HEIGHT(node->right->right) >= MADS_AVL_TREE_HEIGHT(node->right->left))
        {
            node = avl_tree_rotate_with_right_child(node);
        }
        else
        {
            node = avl_tree_double_with_right_child(node);
        }
    }
    else {}

    node->height = MADS_AVL_TREE_MAX(MADS_AVL_TREE_HEIGHT(node->left), MADS_AVL_TREE_HEIGHT(node->right)) + 1;
    return node;
}


static mads_avl_node_t *avl_tree_recursive_insert(mads_avl_node_t *node, const mads_avl_tree_compare_fn cmp, void *data)
{
    mads_avl_node_t *new_node = NULL;
    assert(cmp != NULL);

    if (node == NULL)
    {
        new_node = (mads_avl_node_t *)malloc(sizeof(*new_node));
        assert(new_node != NULL);
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 0;
        return new_node;
    }

    const int compare = cmp(node->data, data);

    if (compare > 0)
    {
        node->left = avl_tree_recursive_insert(node->left, cmp, data);
    }
    else if (compare < 0)
    {
        node->right = avl_tree_recursive_insert(node->right, cmp, data);
    }
    else {}
    return avl_tree_balance(node);
}


void mads_avl_tree_insert(mads_avl_tree_t *t, void *data)
{
    assert(t != NULL);
    t->root = avl_tree_recursive_insert(t->root, t->cmp, data);
}


static mads_avl_node_t *avl_tree_recursive_search(mads_avl_node_t *node, const mads_avl_tree_compare_fn cmp, void *item)
{
    assert(cmp != NULL);
    if (node == NULL) { return node; }
    const int compare = cmp(node->data, item);

    if (compare > 0)
    {
        return avl_tree_recursive_search(node->left, cmp, item);
    }

    if (compare < 0)
    {
        return avl_tree_recursive_search(node->right, cmp, item);
    }

    return node;
}


int mads_avl_tree_search(const mads_avl_tree_t *t, void *item)
{
    const mads_avl_node_t *query_node = NULL;
    assert(t != NULL);
    query_node = avl_tree_recursive_search(t->root, t->cmp, item);
    return (query_node != NULL ? 1 : 0);
}


void *mads_avl_tree_get_elem(const mads_avl_tree_t *t, void *item)
{
    const mads_avl_node_t *query_node = NULL;
    assert(t != NULL);
    query_node = avl_tree_recursive_search(t->root, t->cmp, item);
    return (query_node != NULL ? query_node->data : NULL);
}


void *mads_avl_tree_get_root(const mads_avl_tree_t *t)
{
    assert(t != NULL);
    return (t->root != NULL ? t->root->data : NULL);
}


static mads_avl_node_t *avl_tree_find_min(mads_avl_node_t *node)
{
    if (node == NULL)
    {
        return node;
    }

    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}


static mads_avl_node_t *avl_tree_recursive_remove(mads_avl_node_t *node, const mads_avl_tree_compare_fn cmp, const mads_avl_tree_destroy_fn destroy, void *item)
{
    assert(cmp != NULL);
    if (node == NULL) { return node; }
    const int compare = cmp(node->data, item);

    if (compare > 0)
    {
        node->left = avl_tree_recursive_remove(node->left, cmp, destroy, item);
    }
    else if (compare < 0)
    {
        node->right = avl_tree_recursive_remove(node->right, cmp, destroy, item);
    }
    else
    {
        if (node->right == NULL && node->left == NULL)
        {
            if (destroy != NULL)
            {
                destroy(node->data);
                node->data = NULL;
            }

            free(node);
            node = NULL;
        }
        else if (node->right != NULL && node->left == NULL)
        {
            if (destroy != NULL)
            {
                destroy(node->data);
                node->data = NULL;
            }

            mads_avl_node_t *old_node = NULL;
            old_node = node;
            node = node->right;
            free(old_node);
            old_node = NULL;
        }
        else if (node->left != NULL && node->right == NULL)
        {
            if (destroy != NULL)
            {
                destroy(node->data);
                node->data = NULL;
            }

            mads_avl_node_t *old_node = NULL;
            old_node = node;
            node = node->left;
            free(old_node);
            old_node = NULL;
        }
        else
        {
            mads_avl_node_t *min_node = NULL;
            min_node = avl_tree_find_min(node->right);
            void *temp_data = NULL;
            temp_data = node->data;
            node->data = min_node->data;
            min_node->data = temp_data;
            node->right = avl_tree_recursive_remove(node->right, cmp, destroy, temp_data);
        }
    }

    return avl_tree_balance(node);
}


void mads_avl_tree_remove(mads_avl_tree_t *t, void *item)
{
    assert(t != NULL);
    if (mads_avl_tree_is_empty(t)) { return; }
    t->root = avl_tree_recursive_remove(t->root, t->cmp, t->destroy, item);
}


void mads_avl_tree_remove_root(mads_avl_tree_t *t)
{
    assert(t != NULL);
    mads_avl_tree_remove(t, t->root->data);
}


int mads_avl_tree_is_empty(const mads_avl_tree_t *t)
{
    assert(t != NULL);
    return (t->root == NULL ? 1 : 0);
}


int mads_avl_tree_get_height(const mads_avl_tree_t *t)
{
    assert(t != NULL);
    return (t->root == NULL ? -1 : t->root->height);
}


static void avl_tree_recursive_print(const mads_avl_node_t *node, const mads_avl_tree_print_fn print, const int depth)
{
    assert(print != NULL);
    if (node == NULL) { return; }
    avl_tree_recursive_print(node->right, print, depth + 1);
    for (int i = 0; i < depth; i++) { printf("	"); }
    print(node->data);
    printf("\n");
    avl_tree_recursive_print(node->left, print, depth + 1);
}


void mads_avl_tree_print(const mads_avl_tree_t *t)
{
    assert(t != NULL);
    printf("----------AVL TREE----------\n");
    printf("Height = %d\n", mads_avl_tree_get_height(t));
    avl_tree_recursive_print(t->root, t->print, 0);
    printf("-------------END-------------\n");
}

void mads_avl_tree_free(mads_avl_tree_t *t)
{
    assert(t != NULL);
    while (!mads_avl_tree_is_empty(t)) { mads_avl_tree_remove_root(t); }
    t->cmp = NULL;
    t->print = NULL;
    t->destroy = NULL;
    free(t);
    t = NULL;
}
