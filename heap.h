//
// Created by p0int3r on 6/13/21.
//

#ifndef TINYLIB_HEAP_H
#define TINYLIB_HEAP_H


#define MAX_HEAP 1
#define MIN_HEAP 2

typedef unsigned long long int lluint;

typedef int (*heap_compare_fn)(const void *, const void *);
typedef void (*heap_print_fn)(const void *);
typedef void (*heap_destroy_fn)(void *);


typedef struct
{
    void **A;
    lluint n;
    lluint size;
    int type;
    heap_compare_fn cmp;
    heap_print_fn print;
    heap_destroy_fn destroy;
} heap_t;



heap_t *heap_create(int type, heap_compare_fn cmp, heap_print_fn print, heap_destroy_fn destroy);
void heap_insert(heap_t *h,void *data);
void heap_build(heap_t *h,void **Array,lluint n);
int heap_find(heap_t *h,void *item);
void *heap_get_root(heap_t *h);
void heap_remove_root(heap_t *h);
void heap_change_key(heap_t *h, lluint position, void *item);
int heap_is_empty(heap_t *h);
void heap_print(heap_t *h);
void heap_free(heap_t *h);


#endif //TINYLIB_HEAP_H
