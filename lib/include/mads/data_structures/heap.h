//
// Created by p0int3r on 6/13/21.
//

#ifndef MADS_DATA_STRUCTURES_HEAP_H
#define MADS_DATA_STRUCTURES_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif


#define MADS_HEAP_MAX 1
#define MADS_HEAP_MIN 2

typedef int (*mads_heap_compare_fn)(const void *, const void *);
typedef void (*mads_heap_print_fn)(const void *);
typedef void (*mads_heap_destroy_fn)(void *);


typedef struct
{
    void **A;
    unsigned long long int n;
    unsigned long long int size;
    int type;
    mads_heap_compare_fn cmp;
    mads_heap_print_fn print;
    mads_heap_destroy_fn destroy;
} mads_heap_t;


mads_heap_t *mads_heap_create(int type, mads_heap_compare_fn cmp, mads_heap_print_fn print, mads_heap_destroy_fn destroy);
void mads_heap_insert(mads_heap_t *h, void *data);
void mads_heap_build(mads_heap_t *h, void **Array, unsigned long long int n);
int mads_heap_find(const mads_heap_t *h, const void *item);
void *mads_heap_get_root(const mads_heap_t *h);
void mads_heap_remove_root(mads_heap_t *h);
void mads_heap_change_key(const mads_heap_t *h, unsigned long long int position, void *item);
int mads_heap_is_empty(const mads_heap_t *h);
void mads_heap_print(mads_heap_t *h);
void mads_heap_free(mads_heap_t *h);

#ifdef __cplusplus
}
#endif

#endif //MADS_DATA_STRUCTURES_HEAP_H
