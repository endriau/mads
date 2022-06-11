//
// Created by p0int3r on 6/12/21.
//



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"



array_t *array_create(array_comparator_fn comparator, array_printer_fn printer, array_destructor_fn destructor)
{
    array_t *new_array = NULL;
    long long int initial_msize = 16;
    assert(comparator != NULL && printer != NULL);
    new_array = (array_t *)malloc(sizeof(*new_array));
    assert(new_array != NULL);
    new_array->mblocks = (void **)malloc(initial_msize * sizeof(void *));
    assert(new_array->mblocks != NULL);
    new_array->msize = initial_msize;
    new_array->index = -1;
    new_array->comparator = comparator;
    new_array->printer = printer;
    new_array->destructor = destructor;
    return new_array;
}


void array_append(array_t *array, void *data)
{
    assert(array != NULL);
    array_insert_at(array, array->index + 1, data);
}


void array_prepend(array_t *array, void *data)
{
    assert(array != NULL);
    array_insert_at(array, 0, data);
}


void array_insert_at(array_t *array, long long int index, void *data)
{
    assert(array != NULL);
    assert(index >= 0 && index <= array->index + 1);
    long long int double_msize, i;

    if (array->index + 1 == array->msize)
    {
        double_msize = 2 * array->msize;
        array->mblocks = (void **)realloc(array->mblocks, double_msize * sizeof(void *));
        assert(array->mblocks != NULL);
        array->msize = double_msize;
    }

    array->index++;
    for (i = array->index; i > index; i--) { array->mblocks[i] = array->mblocks[i - 1]; }
    array->mblocks[index] = data;
}


void array_remove_at(array_t *array, long long int index)
{
    long long int i;
    assert(array != NULL);
    assert(index >= 0 && index <= array->index);

    if (array->destructor != NULL)
    {
        array->destructor(array->mblocks[index]);
        array->mblocks[index] = NULL;
    }

    for (i=index; i < array->index; i++) { array->mblocks[i] = array->mblocks[i + 1]; }
    array->index--;
}


void array_set_at(array_t *array, long long int index, void *data)
{
    assert(array != NULL);
    assert(index >= 0 && index <= array->index);
    if (array->destructor != NULL) { array->destructor(array->mblocks[index]); }
    array->mblocks[index] = data;
}


void *array_get_at(array_t *array, long long int index)
{
    assert(array != NULL);
    assert(index >= 0 && index <= array->index);
    return array->mblocks[index];
}


long long int array_has_element(array_t *array, void *item)
{
    long long int i; int result;
    assert(array != NULL);

    for (i = 0; i <= array->index; i++)
    {
        result = array->comparator(array->mblocks[i], item);
        if (result == 0) { return i; }
    }

    return -1;
}


long long int array_size(array_t *array)
{
    assert(array != NULL);
    return (array->index + 1);
}


int array_is_empty(array_t *array)
{
    assert(array != NULL);
    return (array->index == -1 ? 1 : 0);
}


void array_clear(array_t *array)
{
    long long int i;
    assert(array != NULL);

    if (array->destructor != NULL)
    {
        for (i = 0; i <= array->index; i++)
        {
            array->destructor(array->mblocks[i]);
            array->mblocks[i] = NULL;
        }
    }

    array->index = -1;
}


void array_print(array_t *array)
{
    long long int i;
    assert(array != NULL);

    if (array_is_empty(array))
    {
        printf("[ ]\n");
        return;
    }

    printf("[ ");
    for (i = 0; i <= array->index; i++)
    {
        array->printer(array->mblocks[i]);
        printf(", ");
    }
    printf("\b\b ]\n");
}


void array_free(array_t *array)
{
    long long int i;
    assert(array != NULL);

    if (array->destructor != NULL)
    {
        for (i = 0; i <= array->index; i++)
        {
            array->destructor(array->mblocks[i]);
            array->mblocks[i] = NULL;
        }
    }

    free(array->mblocks);
    array->mblocks = NULL;
    free(array);
    array = NULL;
}
