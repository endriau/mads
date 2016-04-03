/*
 * This file contains data type definitions
 * and function prototypings for procedures
 * regarding the binary heap data structure.
 *
 * @author: Endri Kastrati
 * @date:   8/01/2016
 *
 */




/*
 * Using include guards to check if the
 * heap.h header file has been included
 * at least once.If it hasns't the compiler
 * copy-pastes everything into the file that
 * is including it.If the file on the other
 * hand has been included the compiler
 * skips the contents entirely.
 *
 */

#ifndef HEAP_H
#define HEAP_H





/*
 * Defining two macro constants
 * that represent the two types
 * of heaps, min-heap and max-heap.
 *
 */

#define MAX_HEAP    1
#define MIN_HEAP    2





/*
 * Defining an alias for the unsigned integer native type.
 * Defining three new data types of function pointers called
 * HeapCompareFn,HeapPrintFn,HeapDestroyFn.These functions
 * enable polymorphism by specifying an interface for the
 * comparison,printing and memory deallocation function.
 * These functions have to be written by the user and
 * meet the following criteria.
 * 
 */

typedef unsigned int    uint;

typedef int     (*HeapCompareFn)(const void *,const void *);
typedef void    (*HeapPrintFn)(const void *);
typedef void    (*HeapDestroyFn)(void *);




/*
 * This is the C implementation of the binary heap
 * data structure.This enhanced version contains as
 * components an array of pointers A,the number of 
 * elements within the array n,the total size allocated
 * for the array,the type of heap and three function
 * pointers cmp,print,destroy to enable polymorphism.
 *
 */

typedef struct
{
    void                **A;
    uint                n;
    uint                size;
    int                 type;
    HeapCompareFn       cmp;
    HeapPrintFn         print;
    HeapDestroyFn       destroy;
} heap_t;




/*
 * Function prototypings of procedures regarding the
 * binary heap data structure such as create,insert,removeRoot,
 * changeKey etc..
 *
 */

heap_t      *heap_create(int type,HeapCompareFn cmp,HeapPrintFn print,HeapDestroyFn destroy);
void        heap_insert(heap_t *h,void *data);
void        heap_build(heap_t *h,void **Array,int n);
int         heap_find(heap_t *h,void *item);
void        *heap_getRoot(heap_t *h);
void        heap_removeRoot(heap_t *h);
void        heap_changeKey(heap_t *h,int position,void *item);
int         heap_isEmpty(heap_t *h);
void        heap_print(heap_t *h);
void        heap_free(heap_t *h);




/*
 * Once everything has been copy-pasted by
 * the compiler and the macro HEAP_H 
 * has been defined, the heap.h header
 * file  will not be included more than once.
 *
 */

#endif