/*
 * This file contains definitions for operations
 * and procedures regarding the doubly linked
 * list data structure.
 *
 * @author: Endri Kastrati
 * @date:   20/11/2015
 *
 */





/*
 * Including the standard input-output library,
 * the standard utilities library,standard assertion
 * library and the list.h header file that contains
 * definitions and prototypings for the doubly linked list
 * data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function list_create() takes three function pointers
 * as arguments.It creates a new list_t data structure
 * by allocating memory for it and it's components and instantiates
 * it's components to the default values.The print and cmp
 * components are mandatory and cannot be null, the destroy
 * component on the other hand can be null.The users have to
 * create their own cmp,print and destroy ( optional) functions.
 * Failure to do so will result in program termination due to
 * invalid assertions.
 *
 * @param:   ListCompareFn      cmp
 * @param:   ListPrintFn        print
 * @param:   ListDestroyFn      destroy
 * @return:  list_t             *
 *
 */

list_t *list_create(ListCompareFn cmp,ListPrintFn print,ListDestroyFn destroy)
{
    list_t *list=NULL;
    assert(cmp!=NULL && print!=NULL);
    list=(list_t *)malloc(sizeof(*list));
    assert(list!=NULL);
    list->size=0;
    list->head=list->foot=NULL;
    list->cmp=cmp;
    list->print=print;
    list->destroy=destroy;
    return list;
}






/*
 * @COMPLEXITY: Theta(1)
 *
 * The function list_push() takes two arguments,
 * a list_t data structure and a pointer to some data.
 * It allocates memory for a new node, instantiates it's
 * data component to the given data and inserts the node
 * at the beginning of the list.
 *
 * @param:   list_t     *list
 * @param:   void       *data
 * @return:  void
 *
 */

void list_push(list_t *list,void *data)
{
    llnode_t *new_node=NULL;
    assert(list!=NULL);
    new_node=(llnode_t *)malloc(sizeof(*new_node));
    assert(new_node!=NULL);
    new_node->data=data;
    new_node->previous=new_node->next=NULL;

    if (list->head==NULL)
    {
        list->head=new_node;
        list->foot=new_node;
    }
    else
    {
        list->head->previous=new_node;
        new_node->next=list->head;
        list->head=new_node;
    }

    list->size++;
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The fuction list_append() takes two arguments,
 * a list_t data structure and a pointer to some data.
 * It allocates memory for a new node, instantiates it's
 * data component to the given data and inserts the node
 * at the end of the list.
 *
 * @param:   list_t     *list
 * @param:   void       *data
 * @return:  void
 *
 */

void list_append(list_t *list,void *data)
{
    llnode_t *new_node=NULL;
    assert(list!=NULL);
    new_node=(llnode_t *)malloc(sizeof(*new_node));
    assert(new_node!=NULL);
    new_node->data=data;
    new_node->next=new_node->previous=NULL;

    if (list->foot==NULL)
    {
        list->foot=new_node;
        list->head=new_node;
    }
    else
    {
        list->foot->next=new_node;
        new_node->previous=list->foot;
        list->foot=new_node;
    }

    list->size++;
    return;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function list_insertAt() takes three arguments,
 * a list_t data structure, a pointer to some data and
 * an unsigned long long int specifying a position in the list
 * from [ 0 .. list->size - 1 ].If the given position is
 * zero the list_push() function is invoked, if the position
 * equals to list->size-1 the list_append() function is invoked,
 * otherwise we allocate memory for a new node, instantiate it's
 * data component to the given data and inser that node to the
 * specified position within the list via iteration.
 *
 * @param:   list_t     *list
 * @param:   void       *data
 * @param:   lluint     position
 * @return:  void
 *
 */

void list_insertAt(list_t *list,void *data,lluint position)
{
    lluint step=0;
    llnode_t *next_node=NULL,*new_node=NULL;
    assert(list!=NULL && position<list->size);
    
    if (position==0)
    {
        list_push(list,data);
        return;
    }
    else if (position==list->size-1)
    {
        list_append(list,data);
        return;
    }
    else
    {
       new_node=(llnode_t *)malloc(sizeof(*new_node));
       assert(new_node!=NULL);
       new_node->data=data;
       new_node->next=new_node->previous=NULL;
       next_node=list->head;
        
        while (next_node!=NULL && step<position)
        {
            next_node=next_node->next;
            step++;
        }

        next_node->previous->next=new_node;
        new_node->previous=next_node->previous;
        next_node->previous=new_node;
        new_node->next=next_node;
        list->size++;
        return;
    }
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function list_getHead() takes
 * as argument a list_t data structure
 * and returns the first element in the list.
 *
 * @param:   list_t     *list
 * @return   void       *
 *
 */

void *list_getHead(list_t *list)
{
    assert(list!=NULL);
    return list->head->data;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function list_getFoot() takes
 * as argument a list_t data structure
 * and returns the last element in the list.
 *
 * @param:   list_t     *list
 * @return:  void       *
 *
 */

void *list_getFoot(list_t *list)
{
    assert(list!=NULL);
    return list->foot->data;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The function list_getAt() takes two arguments,
 * a list_t data structure and an unsigned long long
 * int specifying a position and returns the element
 * at particular position.
 *
 * @param:   list_t     *list
 * @param:   lluint     position
 * @return:  void       *
 *
 */

void *list_getAt(list_t *list,lluint position)
{
    lluint step=0;
    llnode_t *next_node=NULL;
    assert(list!=NULL && position<list->size);

    if (position==0)
    {
        return list_getHead(list);
    }
    else if (position==list->size-1)
    {
        return list_getFoot(list);
    }
    else
    {
        next_node=list->head;

        while (next_node!=NULL && step<=position)
        {
            next_node=next_node->next;
            step++;
        }

        return next_node->data;
    }
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function list_removeHead() removes the
 * first element in the list.If the list's 
 * destroy component is set to null, the 
 * data component of the llnode_t will not
 * be deallocated.
 *
 * @param:   list_t     *list
 * @return:  void
 *
 */

void list_removeHead(list_t *list)
{
    llnode_t *old_node=NULL;
    assert(list!=NULL);
    
    if (list->head!=list->foot)
    {
        list->head->next->previous=NULL;
        old_node=list->head;
        list->head=list->head->next;
        old_node->next=old_node->previous=NULL;
    }
    else
    {
        old_node=list->head;
        list->head=list->foot=NULL;
    }

    if (list->destroy!=NULL)
    {
        list->destroy(old_node->data);
        old_node->data=NULL;
    }

    free(old_node);
    old_node=NULL;
    list->size--;
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function list_removeFoot() removes the
 * last element in the list.If the list's destroy
 * component is set to null, the data component
 * of the llnode_t will not be deallocated.
 *
 * @param:   list_t     *list
 * @return:  void
 *
 */

void list_removeFoot(list_t *list)
{
    llnode_t *old_node=NULL;
    assert(list!=NULL);

    if (list->foot!=list->head)
    {
        list->foot->previous->next=NULL;
        old_node=list->foot;
        list->foot=list->foot->previous;
        old_node->next=old_node->previous=NULL;
    }
    else
    {
        old_node=list->foot;
        list->foot=list->head=NULL;
    }

    if (list->destroy!=NULL)
    {
        list->destroy(old_node->data);
        old_node->data=NULL;
    }

    free(old_node);
    old_node=NULL;
    list->size--;
    return;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function list_removeAt() takes two arguments,
 * a list_t data structure,an unsigned long long int
 * specifying a position and removes the element at
 * in that position.If the list's destroy component
 * is null,the data component of the llnode_t will not
 * be deallocated.
 *
 * @param:   list_t     *list
 * @param:   uint       position
 * @return:  void
 *
 */

void list_removeAt(list_t *list,lluint position)
{
    lluint step=0;
    llnode_t *old_node=NULL,*next_node=NULL;
    assert(list!=NULL && position<list->size);

    if (position==0)
    {
        list_removeHead(list);
        return;
    }
    else if (position==list->size-1)
    {
        list_removeFoot(list);
        return;
    }
    else
    {
        next_node=list->head;
    
        while (next_node!=NULL && step<=position)
        {
            next_node=next_node->next;
            step++;
        }

        next_node->next->previous=next_node->previous;
        next_node->previous->next=next_node->next;
        old_node=next_node;
        old_node->previous=old_node->next=NULL;

        if (list->destroy!=NULL)
        {
            list->destroy(old_node->data);
            old_node->data=NULL;
        }

        free(old_node);
        old_node=NULL;
        list->size--;
        return;
    }
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function list_print() takes a list_t
 * data structure as argument and prints all
 * of it's elements using by using the list's
 * print component,which must be written by the
 * user since the data type is not known.
 * It prints in a nicely formatted way basic
 * datatypes such as ints,strings,longs,double etc..
 * 
 * @param:   list_t     *list
 * @return:  return
 *
 */

void list_print(list_t *list)
{
    llnode_t *current_node=NULL;
    assert(list!=NULL);
    current_node=list->head;
    
    if (list_isEmpty(list)==1)
    {
        printf("[]\n");
        return;
    }

    printf("[ ");

    while (current_node!=NULL)
    {
        list->print(current_node->data);
        printf(", ");
        current_node=current_node->next;
    }
    
    printf("\b\b ]\n");
    return;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The function list_free() takes a list_t
 * data structure as argument and deallocates
 * memory for the list and it's components.
 * If the list's destroy component is set to null,
 * the data component of each llnode_t will not be 
 * deallocated.
 *
 * @param:   list_t     *list
 * @return:  void
 *
 */

void list_free(list_t *list)
{
    llnode_t *old_node=NULL,*next_node=NULL;
    assert(list!=NULL);
    next_node=list->head;

    while (next_node!=NULL)
    {
        if (list->destroy!=NULL)
        {
            list->destroy(next_node->data);
            next_node->data=NULL;
        }
        
        old_node=next_node;
        next_node=next_node->next;
        free(old_node);
        old_node=NULL;
    }

    old_node=next_node=NULL;
    free(list);
    list=NULL;
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function list_isEmpty() takes as
 * argument a list_t data structure and
 * checks whether the list is empty or not.
 * If the list is empty it returns one
 * otherwise it returns zero.
 *
 * @param:   list_t     *list
 * @return:  int
 *
 */

int list_isEmpty(list_t *list)
{
    assert(list!=NULL);
    return (list->size==0 ? 1 : 0);
}




/*
 * @COMPLEXITY: O(n)
 *
 * The function list_hasElem() takes two
 * arguments, a list_t data structure,
 * a pointer to some data and walks through
 * the entire list searching for an element
 * that matches the given item.If the item
 * is found it returns the index otherwise it
 * returns negative one.
 *
 * @param:   list_t     *list
 * @param:   void       *item
 * @return:  int
 *
 */

int list_hasElem(list_t *list,void *item)
{
    int result; lluint step=0;
    llnode_t *next_node=NULL;
    assert(list!=NULL);
    next_node=list->head;
    
    while (next_node!=NULL)
    {
        result=list->cmp(next_node->data,item);

        if (result==0)
        {
            return step;
        }

        step++;
        next_node=next_node->next;
    }

    next_node=NULL;
    return -1;
}
