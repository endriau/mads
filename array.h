//
// Created by p0int3r on 6/12/21.
//

#ifndef TINYLIB_ARRAY_H
#define TINYLIB_ARRAY_H


typedef long long int llint;

typedef int (*array_compare_fn)(const void *, const void *);
typedef void (*array_print_fn)(const void *);
typedef void (*array_destroy_fn)(void *);


typedef struct
{
    void **A;
    llint n;
    llint size;
    array_compare_fn cmp;
    array_print_fn print;
    array_destroy_fn destroy;
} array_t;


array_t     *array_create(array_compare_fn cmp, array_print_fn print, array_destroy_fn destroy);
void        array_insert(array_t *arr,void *data);
void        array_insert_at(array_t *arr, llint index, void *data);
void        array_remove(array_t *arr,llint index);
void        array_set(array_t *arr,llint index,void *data);
void        *array_get(array_t *arr,llint index);
llint       array_has_element(array_t *arr, void *item);
llint       array_size(array_t *arr);
int         array_is_empty(array_t *arr);
void        array_clear(array_t *arr);
void        array_print(array_t *arr);
void        array_free(array_t *arr);


#endif //TINYLIB_ARRAY_H
