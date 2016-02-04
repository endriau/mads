/*
 * This file contains function defintions
 * for procedures regarding the hash table
 * data structure.This hash table is implemented
 * using seperate chaining with linked lists.
 *
 * @author: Endri kastrati
 * @date:   10/12/2015
 *
 */




/*
 * Including the standard input-output library,
 * the standard utilities library,the hashtable.h
 * header file that contains the hash table data type
 * and the list.c library upon which the hash table
 * data structure depends on.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"
#include "list.h"




/*
 * @COMPLEXITY: O(sqrt(n))
 *
 * The static function is_prime() takes an integer
 * as argument and checks whether it's prime
 * or not.If so it returns one, otherwise it
 * returns zero.
 *
 * @param:   uint   n
 * @return:  int
 *
 */

static int is_prime(uint n)
{
    int divisor;

    if (n<2)
    {
        return 0;
    }

    for (divisor=2;divisor*divisor<=n;divisor++)
    {
        if (n%divisor==0)
        {
            return 0;
        }
    }

    return 1;
}





/*
 * @COMPLEXITY: O(ln(p)*sqrt(p))
 *
 * The static function next_prime() takes as argument
 * a number and calculates the next prime number.
 *
 * @param:   uint   n
 * @return:  uint
 *
 */

static uint next_prime(uint n)
{
    n=n+1;

    while (!is_prime(n))
    {
        n=n+1;
    }
    
    return n;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function htable_create() takes four function pointers
 * as arguments.It creates a new htable_t data structure
 * by allocating memory for it and it's components and instantiates
 * it's components to the default values.The hash,cmp and print
 * components are mandatory and cannot be null,the destroy component
 * on the other hand can be null.The users have to create their own
 * hash,cmp,print,destroy ( optional ) functions.Failure to do so
 * will result in program termination due to invalid assertions.
 *
 * @param:   TableHashFn        hash
 * @param:   TableCompareFn     cmp
 * @param:   TablePrintFn       print
 * @param:   TableDestroyFn     destroy
 * @return:  htable_t           *
 *
 */

htable_t *htable_create(TableHashFn hash,TableCompareFn cmp,TablePrintFn print,TableDestroyFn destroy)
{
    uint i;
    htable_t *table=NULL;
    assert(hash!=NULL && cmp!=NULL && print!=NULL);
    table=(htable_t *)malloc(sizeof(*table));
    assert(table!=NULL);
    table->A=(void **)malloc(INITIAL_SIZE*sizeof(void *));
    assert(table->A!=NULL);
    table->n=0;
    table->table_size=INITIAL_SIZE;
    table->hash=hash;
    table->cmp=cmp;
    table->print=print;
    table->destroy=destroy;

    for (i=0;i<INITIAL_SIZE;i++)
    {
        table->A[i]=list_create(table->cmp,table->print,table->destroy);
    }

    return table;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function htable_insert() takes three arguments,
 * a htable_t data structure, a pointer to a key and
 * a pointer to some data.Checks if the given key 
 * already exists in the table, if so it does nothing,
 * otherwise it inserts the new pair_t data structure
 * into the linked list at the bucket given by the hash
 * function on input key.
 *
 * @param:   htable_t   *t
 * @param:   void       *key
 * @param:   void       *data
 * @return:  void
 *
 */

void htable_insert(htable_t *t,void *key,void *data)
{
    int flag;
    uint index,previous_size,i;
    pair_t *new_pair=NULL;
    assert(t!=NULL);
    previous_size=t->table_size;

    if (t->table_size<=t->n)
    {
        t->table_size=next_prime(t->table_size*2);
        t->A=(void **)realloc(t->A,t->table_size*sizeof(void *));
        assert(t->A!=NULL);

        for (i=previous_size;i<t->table_size;i++)
        {
            t->A[i]=list_create(t->cmp,t->print,t->destroy);
        }

    }

    new_pair=(pair_t *)malloc(sizeof(*new_pair));
    assert(new_pair!=NULL);
    new_pair->key=key;
    new_pair->data=data;
    index=t->hash(t->table_size,key);
    flag=list_hasElem(t->A[index],new_pair);

    if (flag!=-1)
    {
        free(new_pair);
        new_pair=NULL;
        return;
    }
    else
    {
        list_push(t->A[index],new_pair);
        t->n++;
        return;
    }
}





/*
 * @COMPLEXITY: Theta(1) best case, O(n) worst case
 *
 * The function htable_remove() takes two arguments,
 * a htable_t data structure and a void pointer to a key,
 * Checks if the key exists in the hash table, if so
 * it removes it from the table, otherwise it does nothing.
 *
 * @param:   htable_t   *t
 * @param:   void       *key
 * @return:  void
 *
 */

void htable_remove(htable_t *t,void *key)
{
    int flag;
    uint index;
    pair_t *search_pair=NULL;
    assert(t!=NULL);
    search_pair=(pair_t *)malloc(sizeof(*search_pair));
    assert(search_pair!=NULL);
    search_pair->key=key;
    search_pair->data=NULL;
    index=t->hash(t->table_size,key);
    flag=list_hasElem(t->A[index],search_pair);
    search_pair->key=NULL;
    free(search_pair);
    search_pair=NULL;

    if (flag==-1)
    {
        return;
    }
    else
    {
        list_removeAt(t->A[index],flag);
        t->n--;
        return;
    }
}

    




/*
 * @COMPLEXITY: Theta(1) Best case, O(n) worst case
 *
 * The function htable_getValue() takes two arguments,
 * a htable_t data structure and a void pointer to a key,
 * checks if the given key exists in the hash table,if so
 * it returns it's value otherwise it returns null.
 *
 * @param:   htable_t   *t
 * @param:   void       *key
 * @return:  void       *
 *
 */

void *htable_getValue(htable_t *t,void *key)
{
    int flag;
    uint index;
    pair_t *search_pair=NULL,*return_pair=NULL;
    assert(t!=NULL);
    search_pair=(pair_t *)malloc(sizeof(*search_pair));
    assert(search_pair!=NULL);
    search_pair->key=key;
    search_pair->data=NULL;
    index=t->hash(t->table_size,key);
    flag=list_hasElem(t->A[index],search_pair);
    search_pair->key=NULL;
    free(search_pair);
    search_pair=NULL;

    if (flag==-1)
    {
        return NULL;
    }
    else
    {
        return_pair=list_getAt(t->A[index],flag);
        return return_pair->data;
    }
}





/*
 * @COMPLEXITY: Theta(1) best case, O(n) worst case
 *
 * The function htable_lookup(), takes two arguments,
 * a htable_t data structure and a void pointer to a key.
 * Searches for the given key in the linked list at the
 * bucket given by the hash function on input key.
 * If the key does not exist it returns zero,otherwise
 * it returns one.
 *
 * @param:   htable_t   *t
 * @param:   void       *key
 * @return:  int
 *
 */

int htable_lookup(htable_t *t,void *key)
{
    int flag;
    uint index;
    pair_t *search_pair=NULL;
    assert(t!=NULL);
    search_pair=(pair_t *)malloc(sizeof(*search_pair));
    assert(search_pair!=NULL);
    search_pair->key=key;
    search_pair->data=NULL;
    index=t->hash(t->table_size,key);
    flag=list_hasElem(t->A[index],search_pair);
    free(search_pair);
    search_pair=NULL;
    
    if (flag==-1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}





/*
 * @COMPLEXITY: O(m*n), where n is the number of
 * buckets and m the number of elements in the list
 * at each bucket.
 *
 * The function htable_print() takes as argument
 * a htable_t data structure and prints all of
 * the elements of the hash table as pairs <key,value>.
 *
 * @param:   htable_t   *t
 * @return:  void
 *
 */

void htable_print(htable_t *t)
{
    pair_t *pair=NULL;
    uint i,j,list_size;
    assert(t!=NULL);
    list_t *current_list=NULL;
    printf("{ "); 

    for (i=0;i<t->table_size;i++)
    {
        current_list=t->A[i];
        list_size=current_list->size;

        for (j=0;j<list_size;j++)
        {
            pair=list_getAt(current_list,j);
            current_list->print(pair);
            printf(", ");
        }
    }

    printf("\b\b }\n");
    return;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function htable_free() takes a
 * htable_t data structure as an argument
 * and deallocates all of the linked lists
 * at the buckets and then deallocates the
 * hash table and all of it's components.
 *
 * @param:   table_t    *t
 * @return:  void
 *
 */

void htable_free(htable_t *t)
{
    uint i;
    assert(t!=NULL);
    
    for (i=0;i<t->table_size;i++)
    {
        list_free(t->A[i]);
        t->A[i]=NULL;
    }

    free(t->A);
    t->A=NULL;
    free(t);
    t=NULL;
}

