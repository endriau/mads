/*
 * This file contains data definitions
 * and function prototypings for the
 * array data structure.
 *
 * @author: Endri Kastrati
 * @date:   21/05/2017
 *
 */



/*
 * Using include guards to check if
 * the array.h header file has been
 * included at least once.If it hasn't
 * the compiler copy-pastes everything
 * into the file that is including it.
 * If the file on the other hand has 
 * been included the compiler skips 
 * the contents entirely.
 *
 */

#ifndef ARRAY_H
#define ARRAY_H






/*
 * Defining an alias for thelong long int native type.
 * Also defining three new data types of function pointers
 * called ArrayCompareFn,ArrayPrintFn and ArrayDestroyFn.
 * These function pointers enable polymorphism by specyfing
 * an interface for the comparison,printing and memory deallocation 
 * functions.These functions have to be written by the user 
 * and meet the following criteria.
 *
 */

typedef long long int   llint;

typedef int     (*ArrayCompareFn)(const void *,const void *);
typedef void    (*ArrayPrintFn)(const void *);
typedef void    (*ArrayDestroyFn)(void *);




/*
 * Defining a new array data structure.This array
 * implementation contains as fields an array of
 * void pointers,the current index within the array
 * and the total size allocated for the array.It also
 * has three function pointers as fields that represent
 * the comparison,print and destroy functions respectively.
 *
 */

typedef struct 
{
    void                **A;
    llint               n;
    llint               size;
    ArrayCompareFn      cmp;
    ArrayPrintFn        print;
    ArrayDestroyFn      destroy;
} array_t;




/*
 * Function prototyping of procedures regarding
 * the array data structure such as create,insert,
 * set,size,free etc..
 *
 */

array_t     *array_create(ArrayCompareFn cmp,ArrayPrintFn print,ArrayDestroyFn destroy);
void        array_insert(array_t *arr,void *data);
void        array_insertAt(array_t *arr,llint index,void *data);
void        array_remove(array_t *arr,llint index);
void        array_set(array_t *arr,llint index,void *data);
void        *array_get(array_t *arr,llint index);
llint       array_hasElem(array_t *arr,void *item);
llint       array_size(array_t *arr);
int         array_isEmpty(array_t *arr);
void        array_clear(array_t *arr);
void        array_print(array_t *arr);
void        array_free(array_t *arr);





/*
 * Once everything has been copy-pasted by the
 * compiler and the macro ARRAY_H has been defined
 * the array.h header file will not be included more
 * than once.
 *
 */

#endif
