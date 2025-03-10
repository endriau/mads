//
// Created by p0int3r on 6/12/21.
//

#ifndef MADS_DATA_STRUCTURES_AVL_TREE_H
#define MADS_DATA_STRUCTURES_AVL_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mads_export.h>

typedef int (*mads_avl_tree_comparator_fn)(const void *, const void *);
typedef void (*mads_avl_tree_printer_fn)(const void *);
typedef void (*mads_avl_tree_destructor_fn)(void *);


typedef struct mads_avl_node mads_avl_node_t;

struct mads_avl_node
{
    void *data;
    int height;
    mads_avl_node_t *left;
    mads_avl_node_t *right;
};

typedef struct
{
    mads_avl_node_t *root;
    mads_avl_tree_comparator_fn cmp;
    mads_avl_tree_printer_fn print;
    mads_avl_tree_destructor_fn destroy;
} mads_avl_tree_t;


MADS_EXPORT mads_avl_tree_t *mads_avl_tree_create(mads_avl_tree_comparator_fn comparator, mads_avl_tree_printer_fn printer, mads_avl_tree_destructor_fn destructor);
MADS_EXPORT void mads_avl_tree_insert(mads_avl_tree_t *t, void *data);
MADS_EXPORT int mads_avl_tree_search(const mads_avl_tree_t *t, void *item);
MADS_EXPORT void *mads_avl_tree_get_elem(const mads_avl_tree_t *t, void *item);
MADS_EXPORT void *mads_avl_tree_get_root(const mads_avl_tree_t *t);
MADS_EXPORT void mads_avl_tree_remove(mads_avl_tree_t *t, void *item);
MADS_EXPORT void mads_avl_tree_remove_root(mads_avl_tree_t *t);
MADS_EXPORT int mads_avl_tree_is_empty(const mads_avl_tree_t *t);
MADS_EXPORT int mads_avl_tree_get_height(const mads_avl_tree_t *t);
MADS_EXPORT void mads_avl_tree_print(const mads_avl_tree_t *t);
MADS_EXPORT void mads_avl_tree_free(mads_avl_tree_t *t);

#ifdef __cplusplus
}
#endif

#endif //MADS_DATA_STRUCTURES_AVL_TREE_H
