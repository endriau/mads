//
// Created by p0int3r on 6/12/21.
//

#ifndef TINYLIB_LIST_H
#define TINYLIB_LIST_H


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
void list_push(list_t *list,void *data);
void list_append(list_t *list,void *data);
void list_insert_at(list_t *list, void *data, lluint position);
void *list_get_head(list_t *list);
void *list_get_foot(list_t *list);
void *list_get_at(list_t *list, lluint position);
void list_remove_head(list_t *list);
void list_remove_foot(list_t *list);
void list_remove_at(list_t *list, lluint position);
void list_print(list_t *list);
void list_free(list_t *list);
lluint list_get_size(list_t *list);
int list_is_empty(list_t *list);
int list_has_elem(list_t *list, void *item);


#endif //TINYLIB_LIST_H
