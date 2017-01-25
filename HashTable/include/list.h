/*
 * This file contains data definitions and 
 * function prototypings for the doubly linked
 * list data structure.
 *
 * @author: Endri Kastrati
 * @date:   20/11/2015
 *
 */




/*
 * Using include guards to check if the
 * list.h header file has been included
 * at least once.If it hasns't the compiler
 * copy-pastes everything into the file that
 * is including it.If the file on the other
 * hand has been included the compiler
 * skips the contents entirely.
 *
 */

#ifndef LIST_H
#define LIST_H





/*
 * Defining three new data types of function pointers
 * called ListCompareFn,ListPrintFn and ListDestroyFn.
 * These function pointers enable polymorphism by specifying
 * an interface for the comparison,printing and memory deallocation
 * functions.These functions have to be written by the user
 * and meet the following criteria.
 *
 */

typedef int     (*ListCompareFn)(const void *,const void *);
typedef void    (*ListPrintFn)(const void *);
typedef void    (*ListDestroyFn)(void *);



/*
 * Defining aliases for the unsigned long long  integer
 * native type,and the node structure, which represents 
 * the abstract concept of a node in a doubly linked
 * list.The llnode_t structure is a recursive data type that
 * can have as fields other llnode_t structs.
 *
 */


typedef unsigned long long int      lluint;
typedef struct llnode               llnode_t;

struct llnode
{
    void        *data;
    llnode_t    *next;
    llnode_t    *previous;
};



/*
 * This is the C implementation of the doubly linked
 * list data structure.This enhanced version contains
 * as fields size,which represents the number of elements in
 * the list, head and foot which point to the beginning and
 * end of the list and three function pointers cmp,print,destroy
 * to enable polymorphism.
 *
 */

typedef struct
{
    lluint              size;
    llnode_t            *head;
    llnode_t            *foot;
    ListCompareFn       cmp;
    ListPrintFn         print;
    ListDestroyFn       destroy;
} list_t;





/*
 * Function prototyping of procedures regarding 
 * the doubly linked list data structure such as
 * push,append,insert,remove,free etc..
 *
 */

list_t      *list_create(ListCompareFn cmp,ListPrintFn print,ListDestroyFn destroy);
void        list_push(list_t *list,void *data);
void        list_append(list_t *list,void *data);
void        list_insertAt(list_t *list,void *data,lluint position);
void        *list_getHead(list_t *list);
void        *list_getFoot(list_t *list);
void        *list_getAt(list_t *list,lluint position);
void        list_removeHead(list_t *list);
void        list_removeFoot(list_t *list);
void        list_removeAt(list_t *list,lluint position);
void        list_print(list_t *list);
void        list_free(list_t *list);
lluint      list_getSize(list_t *list);
int         list_isEmpty(list_t *list);
int         list_hasElem(list_t *list,void *item);





/*
 * Once everything has been copy-pasted by
 * the compiler and the macro LIST_H has
 * been defined, the list.h header file 
 * will not be included more than once.
 *
 */

#endif
