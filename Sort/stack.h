/*
 * This header file contains function prototyping
 * and data definitions for a polymorphic stack
 * data structure.
 *
 * @author: Endri Kastrati
 * @date:   24/10/2015
 *
 */




/*
 * Using include guards to check if the
 * stack.h header file has been included
 * at least once.If it hasn't, the compiler
 * copy-pastes everything into the file that
 * is including it.If the file on the other
 * hand has been included the compiler
 * skips the contents entirely.
 *
 */

#ifndef STACK_H
#define STACK_H





/*
 * Defining three new datatypes of function pointers called
 * StackCompareFn,StackPrintFn and StackDestroyFn.These function
 * pointers enable polymorphism by specifying an interface for
 * the comparison,printing and memory deallocation functions.
 * These functions have to be written by the user and meet
 * the following criteria.
 */

typedef int     (*StackCompareFn)(const void *,const void *);
typedef void    (*StackPrintFn)(const void *);
typedef void    (*StackDestroyFn)(void *);




/*
 * Defining a new stack data structure.This stack implementation
 * contains as fields an array of void pointers,the current index
 * within the array and the total size allocated for the array.
 * It also has three function pointers as fields that represent
 * the comparison,print and destroy functions respectively.
 *
 */

typedef struct
{
    void                **A;
    int                 n;
    int                 size;
    StackCompareFn      cmp;
    StackPrintFn        print;
    StackDestroyFn      destroy;
} stack_t;





/*
 * Function prototyping of procedures regarding the
 * stack data structure such as instantiation,
 * push,pop,print etc..
 *
 */

stack_t     *stack_create(StackCompareFn cmp,StackPrintFn print,StackDestroyFn destroy);
void        stack_push(stack_t *s,void *item);
void        *stack_pop(stack_t *s);
void        stack_print(stack_t *s);
void        stack_free(stack_t *s);
int         stack_isEmpty(stack_t *s);
int         stack_hasElem(stack_t *s,void *item);




/*
 * Once everything has been copy-pasted by
 * the compiler and the macro STACK_H has
 * been defined, the stack.h header file 
 * will not be included more than once.
 *
 */

#endif
