// ReSharper disable CppDFANullDereference
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/data_structures/stack.h>


stack_t *stack_create(const stack_compare_fn cmp, const stack_print_fn print, const stack_destroy_fn destroy)
{
    assert(cmp!=NULL && print!=NULL);
    const long long int initial_size = 20;
    stack_t *stack = NULL;
    stack = (stack_t *)malloc(sizeof(*stack));
    assert(stack!=NULL);
    stack->A = (void **)malloc(initial_size * sizeof(void *));
    assert(stack->A!=NULL);
    stack->n = -1;
    stack->size = initial_size;
    stack->cmp = cmp;
    stack->print = print;
    stack->destroy = destroy;
    return stack;
}


void stack_push(stack_t *s, void *item)
{
    assert(s!=NULL);

    if (s->n + 1 == s->size)
    {
        const long long int double_size = 2 * s->size;
        s->A = (void **)realloc(s->A, double_size * sizeof(void *));
        assert(s->A!=NULL);
        s->size = double_size;
    }

    s->n++;
    s->A[s->n] = item;
}


void *stack_pop(stack_t *s)
{
    void *old = NULL;
    assert(s!=NULL);

    if (stack_is_empty(s) == 1)
    {
        return NULL;
    }

    old = s->A[s->n];
    s->A[s->n] = NULL;
    s->n--;
    return old;
}


void stack_print(const stack_t *s)
{
    assert(s!=NULL);
    printf("------------STACK------------\n");
    for (long long int i = s->n; i >= 0; i--)
    {
        s->print(s->A[i]);
        printf("\n");
    }

    printf("--------END OF STACK --------\n");
}


void stack_free(stack_t *s)
{
    assert(s!=NULL);

    if (s->destroy != NULL)
    {
        for (long long int i = 0; i <= s->n; i++)
        {
            s->destroy(s->A[i]);
            s->A[i] = NULL;
        }
    }

    free(s->A);
    s->A = NULL;
    free(s);
    s = NULL;
}


int stack_is_empty(const stack_t *s)
{
    assert(s!=NULL);
    return (s->n == -1 ? 1 : 0);
}


int stack_has_elem(const stack_t *s, const void *item)
{
    assert(s!=NULL);

    for (long long int i = 0; i <= s->n; i++)
    {
        if (s->cmp(s->A[i], item) == 0)
        {
            return 1;
        }
    }

    return 0;
}
