//
// Created by p0int3r on 6/12/21.
//



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"



array_t *array_create(array_compare_fn cmp, array_print_fn print, array_destroy_fn destroy)
{
    array_t *new_array=NULL;
    llint initial_size=20;
    assert(cmp!=NULL && print!=NULL);
    new_array=(array_t *)malloc(sizeof(*new_array));
    assert(new_array!=NULL);
    new_array->A=(void **)malloc(initial_size*sizeof(void *));
    assert(new_array->A!=NULL);
    new_array->size=initial_size;
    new_array->n=-1;
    new_array->cmp=cmp;
    new_array->print=print;
    new_array->destroy=destroy;
    return new_array;
}


void array_insert(array_t *arr,void *data)
{
    assert(arr!=NULL);
    array_insert_at(arr, arr->n + 1, data);
}


void array_insert_at(array_t *arr, llint index, void *data)
{
    assert(arr!=NULL);
    assert(index>=0 && index<=arr->n+1);
    llint double_size,i;

    if (arr->n+1==arr->size)
    {
        double_size=2*arr->size;
        arr->A=(void **)realloc(arr->A,double_size*sizeof(void *));
        assert(arr->A!=NULL);
        arr->size=double_size;
    }

    arr->n++;
    for (i=arr->n;i>index;i--) { arr->A[i]=arr->A[i-1]; }
    arr->A[index]=data;
}


void array_remove(array_t *arr,llint index)
{
    llint i;
    assert(arr!=NULL);
    assert(index>=0 && index<=arr->n);

    if (arr->destroy!=NULL)
    {
        arr->destroy(arr->A[index]);
        arr->A[index]=NULL;
    }

    for (i=index;i<arr->n;i++) { arr->A[i]=arr->A[i+1]; }
    arr->n--;
}


void array_set(array_t *arr,llint index,void *data)
{
    assert(arr!=NULL);
    assert(index>=0 && index<=arr->n);
    if (arr->destroy!=NULL) { arr->destroy(arr->A[index]); }
    arr->A[index]=data;
}


void *array_get(array_t *arr,llint index)
{
    assert(arr!=NULL);
    assert(index>=0 && index<=arr->n);
    return arr->A[index];
}


llint array_has_element(array_t *arr, void *item)
{
    llint i; int result;
    assert(arr!=NULL);

    for (i=0;i<=arr->n;i++)
    {
        result=arr->cmp(arr->A[i],item);
        if (result==0) { return i; }
    }

    return -1;
}


llint array_size(array_t *arr)
{
    assert(arr!=NULL);
    return (arr->n+1);
}


int array_is_empty(array_t *arr)
{
    assert(arr!=NULL);
    return (arr->n==-1 ? 1 : 0);
}


void array_clear(array_t *arr)
{
    llint i;
    assert(arr!=NULL);

    if (arr->destroy!=NULL)
    {
        for (i=0;i<=arr->n;i++)
        {
            arr->destroy(arr->A[i]);
            arr->A[i]=NULL;
        }
    }

    arr->n=-1;
}


void array_print(array_t *arr)
{
    llint i;
    assert(arr!=NULL);

    if (array_is_empty(arr))
    {
        printf("[ ]\n");
        return;
    }

    printf("[ ");
    for (i=0;i<=arr->n;i++)
    {
        arr->print(arr->A[i]);
        printf(", ");
    }
    printf("\b\b ]\n");
}


void array_free(array_t *arr)
{
    llint i;
    assert(arr!=NULL);

    if (arr->destroy!=NULL)
    {
        for (i=0;i<=arr->n;i++)
        {
            arr->destroy(arr->A[i]);
            arr->A[i]=NULL;
        }
    }

    free(arr->A);
    arr->A=NULL;
    free(arr);
    arr=NULL;
}
