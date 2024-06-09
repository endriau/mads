//
// Created by p0int3r on 6/12/21.
//

#ifndef MADS_DATA_STRUCTURES_STACK_H
#define MADS_DATA_STRUCTURES_STACK_H


typedef int (*stack_compare_fn)(const void *, const void *);
typedef void (*stack_print_fn)(const void *);
typedef void (*stack_destroy_fn)(void *);


typedef struct
{
    void **A;
    long long int n;
    long long int size;
    stack_compare_fn cmp;
    stack_print_fn print;
    stack_destroy_fn destroy;
} stack_t;


stack_t *stack_create(stack_compare_fn cmp, stack_print_fn print, stack_destroy_fn destroy);
void stack_push(stack_t *s, void *item);
void *stack_pop(stack_t *s);
void stack_print(const stack_t *s);
void stack_free(stack_t *s);
int stack_is_empty(const stack_t *s);
int stack_has_elem(const stack_t *s, const void *item);


#endif //MADS_DATA_STRUCTURES_STACK_H
