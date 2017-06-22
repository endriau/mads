/*
 * This file contains the definitions of
 * procedures regarding the array data
 * structure.
 *
 * @author: Endri Kastrati
 * @date:   21/05/2017
 *
 */





/*
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertions library and the
 * header file array.h which contains data
 * type definitions and function prototypings
 * for the array data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function array_create() takes three function
 * pointers as arguments.It instantiates an array_t
 * data structure by allocating memory for it and it's
 * components.Once memory has been allocated the fields
 * are instantiated and the arguments are assigned to
 * the coresponding components of the array.The print
 * and cmp components are mandatory and cannot be null.
 * The destroy component on the other hand can be null.
 * The users have to create their own cmp,print and
 * destroy (optional) functions.Failure to do so, will
 * result in program termination due to invalid assertions.
 *  
 * @param:  ArrayCompareFn      cmp
 * @param:  ArrayPrintFn        print
 * @param:  ArrayDestroyFn      destroy
 * @return: array_t             *
 *
 */

array_t *array_create(ArrayCompareFn cmp,ArrayPrintFn print,ArrayDestroyFn destroy)
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





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function array_insert() takes two arguments as
 * parameters.The first one is an array_t data structure
 * and the second one a pointer to some data.It appends
 * the given element at the end of the array component.
 * This function invokes the array_insertAt() function.
 *
 * @param:  array_t     *arr
 * @param:  void        *data
 * @return: void
 *
 */

void array_insert(array_t *arr,void *data)
{
    assert(arr!=NULL);
    array_insertAt(arr,arr->n+1,data);
    return;
}






/*
 * @COMPLEXITY: Best case O(1), worst case O(n)
 *
 * The function array_insertAt() takes three arguments
 * as parameters.The first argument is an array_t data
 * structure,the second is an index in the array and
 * the third a pointer to some data.It inserts the given
 * data into the specified position in the array.Failure 
 * to provide an index within the range of the array will
 * result in program termination due to invalid assertions.
 *
 * @param:  array_t     *arr
 * @param:  llint       index
 * @param:  void        *data
 * @return: void
 *
 */

void array_insertAt(array_t *arr,llint index,void *data)
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
    arr->A[index]=data; return;
}






/*
 * @COMPLEXITY: Best case O(1), worst case O(n)
 *
 * The function array_remove() takes two arguments as
 * parameters.The first argument is an array_t data 
 * structure and the second an index in the array.It
 * removes the element at the specified position in the
 * array.Failure to provide an index within the range of 
 * the array will result in program termination due to 
 * invalid assertions.
 *
 * @param:  array_t     *arr
 * @param:  llint       index
 * @return: void
 *
 */

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
    arr->n--; return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function array_set() takes three arguments as
 * parameters.The first argument is an array_t data
 * structure,the second an index in the array and the
 * third a pointer to some data.It overwrites the element
 * at the specified position withiin the array with the
 * given new data.Failure to provide an index within the
 * range of the array will result in program termination
 * due to invalid assertions.
 *
 * @param:  array_t     *arr
 * @param:  llint       index
 * @param:  void        *data
 * @return: void
 *
 */

void array_set(array_t *arr,llint index,void *data)
{
    assert(arr!=NULL);
    assert(index>=0 && index<=arr->n);
    if (arr->destroy!=NULL) { arr->destroy(arr->A[index]); }
    arr->A[index]=data; return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function array_get() takes two arguments as parameters.
 * The first argument is an array_t data structure and the
 * second an index in the array.It returns the element at
 * the specified position within the array.Failure to provide
 * an index within the range of the array will result in program
 * termination due to invalid assertions.
 *
 * @param:  array_t     *arr
 * @param:  llint       index
 * @return: void        *
 *
 */

void *array_get(array_t *arr,llint index)
{
    assert(arr!=NULL);
    assert(index>=0 && index<=arr->n);
    return arr->A[index];
}






/*
 * @COMPLEXITY: O(n)
 *
 * The function array_hasElem() takes two arguments as
 * parameters.The first argument is an array_t data
 * structure and the second a pointer to some data.
 * It searches for the given data within the array.
 * If the element exists it returns the index of the
 * element within the array.On the other hand,if the
 * element does not exist it returns minus one.
 *
 * @param:  array_t     *arr
 * @param:  void        *item
 * @return: llint
 *
 */

llint array_hasElem(array_t *arr,void *item)
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





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function array_size() takes only one argument
 * as parameter,namely an array_t data structure
 * and returns the current size of the given array.
 *
 * @param:  array_t     *arr
 * @return: llint
 *
 */

llint array_size(array_t *arr)
{
    assert(arr!=NULL);
    return (arr->n+1);
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function array_isEmpty() takes only one argument
 * as parameter,namely an array_t data structure and
 * checks whether the given array is empty or not.If
 * the array is empty it returns one otherwise if the
 * array is not empty it returns zero.
 *
 * @param:  array_t     *arr
 * @return: int
 *
 */

int array_isEmpty(array_t *arr)
{
    assert(arr!=NULL);
    return (arr->n==-1 ? 1 : 0);
}





/*
 * @COMPLEXITY: Best case O(1), worst case O(n)
 *
 * The function array_clear() takes only one argument
 * as parameter,namely and array_t data structure and
 * removes all the elements in the array.If the destroy
 * component of the array has been set to null then all
 * we have to do is just set the array component n to 
 * negative one.If on the other hand the destroy has been
 * set then we have to iterate through the entire array 
 * and deallocate each element before setting the n
 * component to negative one.
 *
 * @param:  array_t     *arr
 * @return: void
 *
 */

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
    return;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function array_print() takes only one argument as
 * parameter,namely an array_t data structure and prints
 * the elements of the given array in a user friendly format.
 *
 * @param:  array_t     *arr
 * @return: void
 *
 */

void array_print(array_t *arr)
{
    llint i;
    assert(arr!=NULL);
    
    if (array_isEmpty(arr))
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
    return;
}






/*
 * @COMPLEXITY: Best case O(1), worst case O(n)
 *
 * The function array_free() takes only one argument
 * as parameter,namely an array_t data structure and
 * deallocates memory for it and it's components.
 *
 * @param:  array_t     *arr
 * @return: void
 *
 */

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
    return;
}
