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
 * Defining aliases for the unsigned integer native
 * type,and the node structure, which represents the
 * abstract concept of a node in a doubly linked
 * list.The node_t structure is a recursive data type that
 * can have as fields other node_t structs.
 *
 */


typedef unsigned int    uint;
typedef struct node     node_t;

struct node
{
    void      *data;
    node_t    *next;
    node_t    *previous;
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
    uint                size;
    node_t              *head;
    node_t              *foot;
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
void        list_insertAt(list_t *list,void *data,uint position);
void        *list_getHead(list_t *list);
void        *list_getFoot(list_t *list);
void        *list_getAt(list_t *list,uint position);
void        list_removeHead(list_t *list);
void        list_removeFoot(list_t *list);
void        list_removeAt(list_t *list,uint position);
void        list_print(list_t *list);
void        list_free(list_t *list);
int         list_isEmpty(list_t *list);
int         list_hasElem(list_t *list,void *item);

