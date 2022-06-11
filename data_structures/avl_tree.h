//
// Created by p0int3r on 6/12/21.
//

#ifndef TINYLIB_AVL_TREE_H
#define TINYLIB_AVL_TREE_H



typedef int (*avl_tree_compare_fn)(const void *, const void *);
typedef void (*avl_tree_print_fn)(const void *);
typedef void (*avl_tree_destroy_fn)(void *);


typedef struct avl_node avl_node_t;

struct avl_node
{
    void *data;
    int height;
    avl_node_t *left;
    avl_node_t *right;
};

typedef struct
{
    avl_node_t *root;
    avl_tree_compare_fn cmp;
    avl_tree_print_fn print;
    avl_tree_destroy_fn destroy;
} avl_tree_t;


avl_tree_t *avl_tree_create(avl_tree_compare_fn cmp, avl_tree_print_fn print, avl_tree_destroy_fn destroy);
void avl_tree_insert(avl_tree_t *t, void *data);
int avl_tree_search(avl_tree_t *t, void *item);
void *avl_tree_get_elem(avl_tree_t *t, void *item);
void *avl_tree_get_root(avl_tree_t *t);
void avl_tree_remove(avl_tree_t *t, void *item);
void avl_tree_remove_root(avl_tree_t *t);
int avl_tree_is_empty(avl_tree_t *t);
int avl_tree_get_height(avl_tree_t *t);
void avl_tree_print(avl_tree_t *t);
void avl_tree_free(avl_tree_t *t);


#endif //TINYLIB_AVL_TREE_H
