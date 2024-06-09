// ReSharper disable CppDFANullDereference


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include <mads/data_structures/array.h>


mads_array_t *mads_array_create(const mads_array_comparator_fn comparator, const mads_array_printer_fn printer, const mads_array_destructor_fn destructor)
{
    mads_array_t *new_array = NULL;
    const long long int initial_msize = 16;
    assert(comparator != NULL && printer != NULL);
    new_array = (mads_array_t *)malloc(sizeof(*new_array));
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


void mads_array_append(mads_array_t *array, void *data)
{
    assert(array != NULL);
    mads_array_insert_at(array, array->index + 1, data);
}


void mads_array_prepend(mads_array_t *array, void *data)
{
    assert(array != NULL);
    mads_array_insert_at(array, 0, data);
}


void mads_array_insert_at(mads_array_t *array, const long long int index, void *data)
{
    assert(array != NULL);
    assert(index >= 0 && index <= array->index + 1);

    if (array->index + 1 == array->msize)
    {
        const long long int double_msize = 2 * array->msize;
        array->mblocks = (void **)realloc(array->mblocks, double_msize * sizeof(void *));
        assert(array->mblocks != NULL);
        array->msize = double_msize;
    }

    array->index++;
    for (long long int i = array->index; i > index; i--) { array->mblocks[i] = array->mblocks[i - 1]; }
    array->mblocks[index] = data;
}


void mads_array_remove_at(mads_array_t *array, const long long int index)
{
    assert(array != NULL);
    assert(index >= 0 && index <= array->index);

    if (array->destructor != NULL)
    {
        array->destructor(array->mblocks[index]);
        array->mblocks[index] = NULL;
    }

    for (long long int i = index; i < array->index; i++) { array->mblocks[i] = array->mblocks[i + 1]; }
    array->index--;
}


void mads_array_set_at(const mads_array_t *array, const long long int index, void *data)
{
    assert(array != NULL);
    assert(index >= 0 && index <= array->index);
    if (array->destructor != NULL) { array->destructor(array->mblocks[index]); }
    array->mblocks[index] = data;
}


void *mads_array_get_at(const mads_array_t *array, const long long int index)
{
    assert(array != NULL);
    assert(index >= 0 && index <= array->index);
    return array->mblocks[index];
}


long long int mads_array_has_element(const mads_array_t *array, const void *item)
{
    assert(array != NULL);

    for (long long int i = 0; i <= array->index; i++)
    {
        const int result = array->comparator(array->mblocks[i], item);
        if (result == 0) { return i; }
    }

    return -1;
}


long long int mads_array_size(const mads_array_t *array)
{
    assert(array != NULL);
    return (array->index + 1);
}


int mads_array_is_empty(const mads_array_t *array)
{
    assert(array != NULL);
    return (array->index == -1 ? 1 : 0);
}


void mads_array_clear(mads_array_t *array)
{
    assert(array != NULL);

    if (array->destructor != NULL)
    {
        for (long long int i = 0; i <= array->index; i++)
        {
            array->destructor(array->mblocks[i]);
            array->mblocks[i] = NULL;
        }
    }

    array->index = -1;
}


void mads_array_print(const mads_array_t *array)
{
    assert(array != NULL);

    if (mads_array_is_empty(array))
    {
        printf("[ ]\n");
        return;
    }

    printf("[ ");
    for (long long int i = 0; i <= array->index; i++)
    {
        array->printer(array->mblocks[i]);
        printf(", ");
    }
    printf("\b\b ]\n");
}


void mads_array_free(mads_array_t *array)
{
    assert(array != NULL);

    if (array->destructor != NULL)
    {
        for (long long int i = 0; i <= array->index; i++)
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
