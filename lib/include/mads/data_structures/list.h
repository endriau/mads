//
// Created by p0int3r on 6/12/21.
//

#ifndef MADS_DATA_STRUCTURES_LIST_H
#define MADS_DATA_STRUCTURES_LIST_H


typedef int (*list_compare_fn)(const void *, const void *);
typedef void (*list_print_fn)(const void *);
typedef void (*list_destroy_fn)(void *);

typedef unsigned long long int lluint;
typedef struct llnode llnode_t;

struct llnode
{
    void *data;
    llnode_t *next;
    llnode_t *previous;
};


typedef struct
{
    lluint size;
    llnode_t *head;
    llnode_t *foot;
    list_compare_fn cmp;
    list_print_fn print;
    list_destroy_fn destroy;
} list_t;


list_t *list_create(list_compare_fn cmp, list_print_fn print, list_destroy_fn destroy);
void list_push(list_t *list, void *data);
void list_append(list_t *list, void *data);
void list_insert_at(list_t *list, void *data, lluint position);
void *list_get_head(const list_t *list);
void *list_get_foot(const list_t *list);
void *list_get_at(const list_t *list, lluint position);
void list_remove_head(list_t *list);
void list_remove_foot(list_t *list);
void list_remove_at(list_t *list, lluint position);
void list_print(const list_t *list);
void list_free(list_t *list);
lluint list_get_size(const list_t *list);
int list_is_empty(const list_t *list);
int list_has_elem(const list_t *list, const void *item);


#endif //MADS_DATA_STRUCTURES_LIST_H
