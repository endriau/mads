/*
 * This file contains  definitions for
 * operations and procedures regarding the 
 * stack data structure.
 *
 * @author: Endri Kastrati
 * @date:   24/10/2015
 *
 */




/*
 * Including the standard input-output library,
 * the standard general utilities library,
 * the standard assertion library and the
 * header file stack.h containing datatype
 * definitions and function prototypings.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"






/*
 * @COMPLEXITY: Theta(1)
 *
 * The function stack_create() takes three function
 * pointers as arguments.It instantiates a stack_t 
 * data structure by allocating memory for it and it's
 * components.Once memory has been allocated the fields
 * are instantiated and the arguments are assigned to
 * the coresponding components of the stack.The print
 * and cmp components are mandatory and cannot be null
 * The destroy component on the other hand can be null.
 * The users have to create their own cmp,print and destroy ( optional )
 * functions.Failure to do so,will result in program termination due
 * to invalid assertions.
 *
 * @param:  StackCompareFn  cmp
 * @param:  StackPrintFn    print
 * @param:  StackDestroyFn  destroy
 * @return: stack_t         *
 *
 */

stack_t *stack_create(StackCompareFn cmp,StackPrintFn print,StackDestroyFn destroy)
{
    assert(cmp!=NULL && print!=NULL);
    long long int initial_size=20;
    stack_t *stack=NULL;
    stack=(stack_t *)malloc(sizeof(*stack));
    assert(stack!=NULL);
    stack->A=(void **)malloc(initial_size*sizeof(void *));
    assert(stack->A!=NULL);
    stack->n=-1;
    stack->size=initial_size;
    stack->cmp=cmp;
    stack->print=print;
    stack->destroy=destroy;
    return stack;
}





/*
 * @COMPLEXITY: Theta(1), since memory is geometrically increasing.
 *
 * The function stack_push() takes as arguments a stack_t
 * data structure and a void pointer to some element.The
 * element is pushed into the stack.If there is not enough
 * memory,the array component is reallocated memory double
 * it's previous size and afterwards the element is pushed into.
 *
 * @param:  stack_t     *s
 * @param:  void        *item
 * @return: void
 *
 */

void stack_push(stack_t *s,void *item)
{
    assert(s!=NULL);
    long long int double_size;

    if (s->n+1==s->size)
    {
        double_size=2*s->size;
        s->A=(void **)realloc(s->A,double_size*sizeof(void *));
        assert(s->A!=NULL);
        s->size=double_size;
    }

    s->n++;
    s->A[s->n]=item;
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function stack_pop() takes a stack_t
 * data structure as an argument and returns
 * a void pointer to the last element in the array
 * component of the stack, assigns null to that position
 * and decrements the index component by 1.
 *
 * @param:  stack_t     *s
 * @return: void        *
 *
 */

void *stack_pop(stack_t *s)
{
    void *old=NULL;
    assert(s!=NULL);

    if (stack_isEmpty(s)==1)
    {
        return NULL;
    }

    old=s->A[s->n];
    s->A[s->n]=NULL;
    s->n--;
    return old;
}
    





/*
 * @COMPLEXITY: O(n)
 *
 * The stack_print() function takes a stack_t
 * data structure as an argument and prints
 * all elements currently residing in the array
 * component of the stack.This function uses the
 * print function pointer that was assigned to the
 * data structure during the instantiation.The users
 * are expected to create their own printing function,
 * failure to do so will result in program termination
 * due to invalid assertions.
 *
 * @param:  stack_t     *s
 * @return: void
 *
 */

void stack_print(stack_t *s)
{
    long long int i;
    assert(s!=NULL);
    printf("------------STACK------------\n");
    for (i=s->n;i>=0;i--)
    {
        s->print(s->A[i]);
        printf("\n");
    }

    printf("--------END OF STACK --------\n");
    return;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function stack_free() deallocates
 * all the memory that was allocated for
 * the stack_t data structure during it's
 * instantiation.If the stack has been assigned
 * a destroy function then each element in the array
 * component  has to be deallocated using that function.
 * If the destroy component is set to NULL then only
 * the array component and the struct have to be 
 * deallocated.
 *
 * @param:  stack_t     *s
 * @return: void
 *
 */

void stack_free(stack_t *s)
{
    long long int i;
    assert(s!=NULL);

    if (s->destroy!=NULL)
    {
        for (i=0;i<=s->n;i++)
        {
            s->destroy(s->A[i]);
            s->A[i]=NULL;
        }
    }

    free(s->A);
    s->A=NULL;
    free(s);
    s=NULL;
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function stack_isEmpty() takes a stack_t
 * data structure as an argument and checks
 * whether the stack is empty or not. If
 * the stack is empty it returns 1, otherwise
 * it return 0.
 *
 * @param:  stack_t     *s
 * @return: int
 *
 */

int stack_isEmpty(stack_t *s)
{
    assert(s!=NULL);
    return ( s->n==-1 ? 1 : 0 );
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function stack_hasElem() takes as arguments
 * a stack_t data structure and a void pointer
 * to some data and checks whether the given element exists
 * within the stack, if so it returns 1, otherwise
 * it returns 0.
 *
 * @param:  stack_t     *s
 * @param:  void        *item
 * @return: int
 *
 */

int stack_hasElem(stack_t *s,void *item)
{
    long long int i;
    assert(s!=NULL);

    for (i=0;i<=s->n;i++)
    {
        if (s->cmp(s->A[i],item)==0)
        {
            return 1;
        }
    }

    return 0;
}
