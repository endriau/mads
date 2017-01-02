/*
 * The following file contains definition of
 * procedures and operations regarding the
 * hash table data structure using seperate
 * chaining technique.
 *  
 * @author: Endri Kastrati
 * @date:   1/01/2017
 *
 */





/*
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertions library,the 
 * tree.h and list.h header files that
 * contain datatype definitions for the
 * linked list and avl tree data structures.
 * Finally lost include,the header file 
 * hashtable.h that contains datatype
 * definitions for the hash table dataype.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "list.h"
#include "hashtable.h"




////////////////////////////////////////////////////////////////////////////////////



/*
 * @COMPLEXITY: Theta(1) best case,worst case O(F(n))
 *              where F(n) is some type of mathematical
 *              function that represents the asymptotic
 *              complexity of the given datatype.
 *              
 * The static function compare_pairs(),takes two pair
 * data structures as arguments and compares their
 * cue values.Depending on the method that the cues
 * are compared this function returns the appropriate
 * result value.
 * 
 * @param:  const void      *p1
 * @param:  const void      *p2
 * @return: int
 * 
 */

static int compare_pairs(const void *p1,const void *p2)
{
    pair_t *pp1=NULL,*pp2=NULL;
    cue_t *c1=NULL,*c2=NULL;
    pp1=(pair_t *)p1;
    pp2=(pair_t *)p2;
    c1=pair_getCue(pp1);
    c2=pair_getCue(pp2);
    return cue_compareTo(c1,cue_get(c2));
}




/*
 * @COMPLEXITY: Theta(1) best case,worst case O(F(n))
 *              where F(n) is some type of mathematical
 *              function that represents the asymptotic
 *              complexity of the given datatype.
 *
 * The static function print_pair() takes a pair
 * data structure as an argument and prints it's
 * components in a user-friendly format.
 * 
 * @param:  const void  *p
 * @return: void
 * 
 */

static void print_pair(const void *p)
{
    pair_t *pair=NULL;
    pair=(pair_t *)p;
    pair_print(pair);
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function deallocate_pair(),takes
 * a pair data structure as an argument and 
 * deallocates memory for it and it's components.
 * 
 * @param:  void    *p
 * @return: void
 * 
 */

static void deallocate_pair(void *p)
{
    pair_t *pair=NULL;
    pair=(pair_t *)p;
    pair_free(pair);
    pair=NULL;
    return;
}


//////////////////////////////////////////////////////////////////////////////////// 







/*
 * @COMPLEXITY: O(m), where m is the initial hash table size.
 * 
 * 
 * The function table_create(),takes two arguments as
 * parameters.The first argument is a function pointer
 * that represents the type of hashing.The second one
 * is a macro constant that specifies what kind of
 * seperate chaining buckets to used (list or tree).
 * This function instantiates a new table_t datatype
 * and allocates memory for it and it's components
 * and sets them to their corresponding default values.
 * 
 * @param:  TableHashFn     hash
 * @param:  int             chain_type
 * @return: table_t         *
 * 
 * 
 */

table_t *table_create(TableHashFn hash,int chain_type)
{
    int i;
    table_t *new_table=NULL;
    assert(hash!=NULL);
    assert(chain_type==CHAIN_LIST || chain_type==CHAIN_TREE);
    new_table=(table_t *)malloc(sizeof(*new_table));
    assert(new_table!=NULL);
    new_table->A=(void **)malloc(INITIAL_SIZE*sizeof(void *));
    assert(new_table->A!=NULL);
    new_table->type=chain_type;

    for (i=0;i<INITIAL_SIZE;i++)
    {
        if (new_table->type==CHAIN_LIST)
        {
            new_table->A[i]=list_create(compare_pairs,print_pair,deallocate_pair);
        }
        else if (new_table->type==CHAIN_TREE)
        {
            new_table->A[i]=tree_create(compare_pairs,print_pair,deallocate_pair);
        }
        else {}
    }

    new_table->n=0;
    new_table->size=INITIAL_SIZE;
    new_table->lf=(new_table->n)/(new_table->size);
    new_table->hfunc=hashfn_create(INITIAL_SIZE,20);
    new_table->hash=hash;
    return new_table;
}





/* 
 * @COMPLEXITY:
 * 
 * The function table_insert(),takes two arguments
 * as parameters,namely a hash table data structure
 * and a pair data structure.This function firstly
 * checks if the key of the given pair exists in
 * the table.If the key does not exist it is inserted
 * into the table.If the key on the other hand exists
 * nothing happens.
 * 
 * @param:  table_t     *t
 * @param:  pair_t      *p
 * @return: void
 *  
 */

void table_insert(table_t *t,pair_t *p)
{
    uint position;
    cue_t *temp_cue=NULL;
    void *cue_data=NULL;
    assert(t!=NULL && p!=NULL);
    temp_cue=pair_getCue(p);
    cue_data=cue_get(temp_cue);
    if (table_lookup(t,cue_data)==1) { return; }
    position=t->hash(t->hfunc,cue_data);

    if (t->type==CHAIN_LIST)
    {
        list_push(t->A[position],p);
        t->n=t->n+1;
    }
    else if (t->type==CHAIN_TREE)
    {
        tree_insert(t->A[position],p);
        t->n=t->n+1;
    }
    else {}
    return;
}




/*
 * @COMPLEXITY:
 * 
 * The function table_lookup(),takes two
 * arguments as parameters.The first argument
 * is a hash table data structure and the
 * second one an address to some key.This
 * function searches through the table for
 * the given key value.If the key exists
 * in the table it returns one.Otherwise,
 * if the key does not exist in the table
 * it returns zero.
 * 
 * @param:  table_t     *t
 * @param:  void        *key
 * @return: int
 * 
 */

int table_lookup(table_t *t,void *key)
{
    int chain_query; uint position;
    pair_t temp_pair; cue_t temp_cue;
    assert(t!=NULL && key!=NULL);
    position=t->hash(t->hfunc,key);
    temp_cue.cue=key;
    temp_pair.k=&temp_cue;

    if (t->type==CHAIN_LIST)
    {
        chain_query=list_hasElem(t->A[position],&temp_pair);
        return (chain_query>-1 ? 1 : 0);
    }
    else if (t->type==CHAIN_TREE)
    {
        chain_query=tree_search(t->A[position],&temp_pair);
        return chain_query;
    }
    else
    {
        return 0;
    }
}






/* 
 * @COMPLEXITY:
 * 
 * The function table_remove(),takes two
 * arguments as parameters.The first argument
 * is a hash table data structure and the
 * second one is an address to some key.This
 * function searches the table for the given
 * key.If the key is found,it is removed
 * from the hash table including it's value.
 * If the key does not exist,nothing happesn.
 * 
 * @param:  table_t     *t
 * @param:  void        *key
 * @return: void
 * 
 */

void table_remove(table_t *t,void *key)
{
    pair_t temp_pair; cue_t temp_cue;
    uint position,chain_pos;
    assert(t!=NULL && key!=NULL);
    position=t->hash(t->hfunc,key);
    if (table_lookup(t,key)==0) { return; }
    temp_cue.cue=key;
    temp_pair.k=&temp_cue;

    if (t->type==CHAIN_LIST)
    {
        chain_pos=list_hasElem(t->A[position],&temp_pair);
        list_removeAt(t->A[position],chain_pos);
        t->n=t->n-1;
    }
    else if (t->type==CHAIN_TREE)
    {
        tree_remove(t->A[position],&temp_pair);
        t->n=t->n-1;
    }
    else {}
    return;
}




/* 
 * @COMPLEXITY:
 * 
 * The function table_getValue(),takes two
 * arguments as parameters.The first argument
 * is a hash table data structure and the second
 * one is an address to some key.This function
 * searches for the given key and returns the
 * value associated with it in the table.If the
 * key does not exist in the table nothing happens
 * and the function returns the value of NULL.
 * 
 * @param:  table_t     *t
 * @param:  void        *key
 * @return: void        *      
 *  
 */

void *table_getValue(table_t *t,void *key)
{
    cue_t temp_cue; pair_t temp_pair;
    uint position,chain_query;
    pair_t *returned_pair=NULL;
    value_t *returned_value=NULL;
    assert(t!=NULL && key!=NULL);
    if (table_lookup(t,key)==0) { return NULL; }
    position=t->hash(t->hfunc,key);
    temp_cue.cue=key;
    temp_pair.k=&temp_cue;

    if (t->type==CHAIN_LIST)
    {
        chain_query=list_hasElem(t->A[position],&temp_pair);
        returned_pair=list_getAt(t->A[position],chain_query);
        returned_value=pair_getValue(returned_pair);
        return value_get(returned_value);
    }
    else if (t->type==CHAIN_TREE)
    {
        returned_pair=tree_getElem(t->A[position],&temp_pair);
        returned_value=pair_getValue(returned_pair);
        return value_get(returned_value);
    }
    else
    {
        return NULL;
    }
}


/* 
 * @COMPLEXITY: 
 * 
 * The function table_changeValue(),takes three
 * arguments as parameters.The first argument
 * is a hash table data structure,the second
 * is an address to a key and the third is
 * the new value to be associated with the
 * given key.This function changes the value
 * of the given key.If the key does not exist
 * nothing happens.
 * 
 * @param:  table_t     *t
 * @param:  void        *key
 * @param:  void        *value
 * 
 */

void table_changeValue(table_t *t,void *key,void *value)
{
    uint position,chain_query;
    pair_t *returned_pair=NULL;
    cue_t temp_cue; pair_t temp_pair;
    value_t *old_value=NULL,*new_value=NULL;
    assert(t!=NULL && key!=NULL);
    if (table_lookup(t,key)==0) { return; }
    position=t->hash(t->hfunc,key);
    temp_cue.cue=key;
    temp_pair.k=&temp_cue;


    if (t->type==CHAIN_LIST)
    {
        chain_query=list_hasElem(t->A[position],&temp_pair);
        returned_pair=list_getAt(t->A[position],chain_query);
        old_value=pair_getValue(returned_pair);
        new_value=value_create(value,old_value->cmp,
                old_value->print,old_value->destroy);
        pair_changeValue(returned_pair,new_value);
        return;
    }
    else if (t->type==CHAIN_TREE)
    {
        returned_pair=tree_getElem(t->A[position],&temp_pair);
        old_value=pair_getValue(returned_pair);
        new_value=value_create(value,old_value->cmp,
                old_value->print,old_value->destroy);
        pair_changeValue(returned_pair,new_value);
        return;
    }
    else {}
    return;
}





/* 
 * @COMPLEXITY: O(m*n) where m is the size of
 *              table and n is the size of the
 *              bucket with the maximum depth.
 * 
 * The function table_print(),takes a hash table
 * data structure as an argument and prints the
 * elements of the table in a user-friendly format.
 * 
 * @param:  table_t     *t
 * @return: void
 * 
 */

void table_print(table_t *t)
{
    int i;
    assert(t!=NULL);

    for (i=0;i<t->size;i++)
    {
        printf("index %d:",i);

        if (t->type==CHAIN_LIST)
        {
            list_print(t->A[i]);
        }
        else if (t->type==CHAIN_TREE)
        {
            tree_print(t->A[i]);
        }
        else {}
    }

    return;
}




/* 
 * @COMLEXITY: O(m) where m is the size of table.
 * 
 * The function table_free(),takes a hash table
 * data structure as an argument and deallocates
 * memory for it and it's components.In the cases
 * where the chain type is an avl tree, the trees
 * at every bucket are reassigned a new comparison
 * function before memory deallocation.Once all buckets
 * have been freed,the memory of the table and it's fields
 * is also deallocated.
 * 
 * @param:  table_t     *t
 * @return: void
 * 
 */

void table_free(table_t *t)
{
    int i;
    tree_t *temp_tree=NULL;
    assert(t!=NULL);

    for (i=0;i<t->size;i++)
    {
        if (t->type==CHAIN_LIST)
        {
            list_free(t->A[i]);
        }
        else if (t->type==CHAIN_TREE)
        {
            temp_tree=t->A[i];
            temp_tree->cmp=compare_pairs;
            tree_free(temp_tree);
        }
        else {}
    }

    free(t->A); t->A=NULL;
    hashfn_free(t->hfunc);
    t->hfunc=NULL;
    free(t); t=NULL;
    return;
}



////////////////////////////////////////////////////////////////////////////////////