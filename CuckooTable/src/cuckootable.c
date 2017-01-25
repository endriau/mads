/* 
 * The following file contains definition of
 * procedures and operations regarding the
 * cuckoo hash table data structure.
 * 
 * @author: Endri Kastrati
 * @date:   10/01/2017
 * 
 */




/* 
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertions library and the
 * cuckootable.h header file that contains
 * datatype definitions and function prototyping
 * for the cuckoo hash table data structure.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cuckootable.h"



////////////////////////////////////////////////////////////////////////////


/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function cuckoo_loadFactor(),takes
 * a hash table data structure as an argument,
 * calculates the current load factor for the
 * table and returns it's value.
 *
 * @param:  cuckoo_t     *t
 * @return: double
 *
 */

static double cuckoo_loadFactor(cuckoo_t *t)
{
    double lf;
    assert(t!=NULL);
    lf=(double )(t->n)/(t->size*2);
    t->lf=lf; return lf;
}




/*
 * @COMPLEXITY: O(sqrt(n))
 *
 * The static function is_prime() takes only
 * one argument as a parameter,namely an unsigned
 * long long int value and checks whether it constitutes
 * a prime number or not.If the given number is a
 * prime it returns one,otherwise it returns zero.
 *
 * @param:  lluint  n
 * @return: int
 *
 */

static int is_prime(lluint n)
{
    lluint divisor;
    lluint isprime=1;
    if (n<2) { return 0; }

    for (divisor=2;divisor*divisor<=n;divisor++)
    {
        if (n%divisor==0)
        {
            isprime=0;
            break;
        }
    }

    return isprime;
}





/*
 * @COMPLEXITY: O(ln(n)*sqrt(n))
 *
 * The static function next_prime(),takes only
 * one argument as a parameter,namely an unsigned
 * integer value and returns the next prime number
 * after that value.This function invokes the static
 * is_prime() function to check if a value is prime
 * or not.
 *
 * @param:  lluint  n
 * @return: lluint
 *
 */

static lluint next_prime(lluint n)
{
    lluint step;
    assert(n!=0);
    step=n+1;

    while (is_prime(step)==0)
    {
        step++;
    }

    return step;
}



/* 
 * @COMPLEXITY: O(n)
 * 
 * The static function cuckoo_rehash() takes
 * as an argument a pointer to a cuckoo hash
 * table data structure and increases the
 * size of the tables and rehashes everything
 * that is already in the tables.
 * 
 * @param:  cuckoo_t    *c
 * @return: void
 * 
 */

static void cuckoo_rehash(cuckoo_t *c)
{
    pair_t *temp_pair=NULL;
    lluint double_size,i,old_size;
    void **old_T1=NULL,**old_T2=NULL;
    old_T1=c->T1; old_T2=c->T2;
    c->T1=NULL; c->T2=NULL;
    old_size=c->size;
    double_size=next_prime(c->size*2);
    c->T1=(void **)malloc(double_size*sizeof(void *));
    assert(c->T1!=NULL);
    c->T2=(void **)malloc(double_size*sizeof(void *));
    assert(c->T2!=NULL);

    for (i=0;i<double_size;i++)
    { 
        c->T1[i]=NULL; 
        c->T2[i]=NULL;
    }

    c->size=double_size; c->n=0;
    hashfn_free(c->hfunc1); c->hfunc1=NULL;
    hashfn_free(c->hfunc2); c->hfunc2=NULL;
    c->hfunc1=hashfn_create(double_size,20);
    c->hfunc2=hashfn_create(double_size,20);

    for (i=0;i<old_size;i++)
    {
        temp_pair=old_T1[i];
        old_T1[i]=NULL;

        if (temp_pair!=NULL)
        {
            cuckoo_insert(c,temp_pair);
        }

        temp_pair=old_T2[i];
        old_T2[i]=NULL;

        if (temp_pair!=NULL)
        {
            cuckoo_insert(c,temp_pair);
        }
    }

    free(old_T1); old_T1=NULL;
    free(old_T2); old_T2=NULL;
    return;
}



////////////////////////////////////////////////////////////////////////////




/* 
 * @COMPLEXITY: O(m) where m is the initial size of the tables.
 * 
 * The function cuckoo_create() takes one argument as
 * a parameter,namely a function pointer that represents
 * the type of hashing.This function instantiates a new
 * cuckoo hash table data structure and allocates memory
 * for it and it's components and sets them to their
 * default values.
 * 
 * @param:  CuckooHashFn    hash
 * @return: cuckoo_t        *
 * 
 */

cuckoo_t *cuckoo_create(CuckooHashFn hash)
{
    lluint i;
    cuckoo_t *new_table=NULL;
    assert(hash!=NULL);
    new_table=(cuckoo_t *)malloc(sizeof(*new_table));
    assert(new_table!=NULL);
    new_table->T1=(void **)malloc(INITIAL_CUCKOO_SIZE*sizeof(void *));
    assert(new_table->T1!=NULL);
    new_table->T2=(void **)malloc(INITIAL_CUCKOO_SIZE*sizeof(void *));
    new_table->n=0; new_table->size=INITIAL_CUCKOO_SIZE;

    for (i=0;i<INITIAL_CUCKOO_SIZE;i++)
    {
        new_table->T1[i]=NULL;
        new_table->T2[i]=NULL;
    }

    new_table->lf=(double )(new_table->n)/(new_table->size*2);
    new_table->hfunc1=hashfn_create(INITIAL_CUCKOO_SIZE,20);
    new_table->hfunc2=hashfn_create(INITIAL_CUCKOO_SIZE,20);
    new_table->hash=hash;
    return new_table;
}





/* 
 * @COMPLEXITY: Theta(1)
 * 
 * The function cuckoo_insert(),takes two arguments
 * as parameters.The first one,is a pointer to a
 * cuckoo hash table data structure, and the second
 * one is a pointer to a pair data structure.This
 * function checks if the given pair's key already
 * exists in the hashtable.If so nothing happens,
 * otherwise the pair is inserted into the appropriate
 * table at the corresponding position.
 * 
 * @param:  cuckoo_t    *c
 * @param:  pair_t      *p
 * @return: void
 * 
 */

void cuckoo_insert(cuckoo_t *c,pair_t *p)
{
    lluint position1,position2;
    assert(c!=NULL && p!=NULL);
    /*double load_factor;*/ int i;
    pair_t *swap_pair=NULL,*temp_pair=NULL;
    cue_t *temp_cue=NULL; void *cue_data=NULL;
    temp_cue=pair_getCue(p); cue_data=cue_get(temp_cue);
    if (cuckoo_lookup(c,cue_data)==1) { return; }
    temp_pair=p;

    for (i=0;i<MAX_LOOP_ITERATIONS;i++)
    {
        temp_cue=pair_getCue(temp_pair);
        cue_data=cue_get(temp_cue);
        position1=c->hash(c->hfunc1,cue_data);
        swap_pair=c->T1[position1];

        if (swap_pair==NULL)
        {
            c->T1[position1]=temp_pair;
            c->n++; cuckoo_loadFactor(c);
            return;
        }
        else
        {
            c->T1[position1]=temp_pair;
            temp_pair=swap_pair;
        }

        temp_cue=pair_getCue(temp_pair);
        cue_data=cue_get(temp_cue);
        position2=c->hash(c->hfunc2,cue_data);
        swap_pair=c->T2[position2];

        if (swap_pair==NULL)
        {
            c->T2[position2]=temp_pair;
            c->n++; cuckoo_loadFactor(c);
            return;
        }
        else
        {
            c->T2[position2]=temp_pair;
            temp_pair=swap_pair;
        }
    }

    cuckoo_rehash(c);
    cuckoo_insert(c,temp_pair);
    return;
}





/* 
 * @COMPLEXITY: Theta(1)
 * 
 * The function cuckoo_lookup(),takes two
 * arguments as parameters.The first argument
 * is a pointer to a cuckoo hash table data
 * structure and the second a pointer to some
 * key.This function checks whether the given
 * key already exists in one of the tables.
 * If the key exists,it returns one,otherwise
 * it returns zero.
 * 
 * @param:  cuckoo_t    *c
 * @param:  void        *key
 * @return: int
 * 
 */

int cuckoo_lookup(cuckoo_t *c,void *key)
{
    assert(c!=NULL);
    int query1,query2;
    lluint position1,position2;
    pair_t *temp_pair1=NULL,*temp_pair2=NULL;
    cue_t *temp_cue1=NULL,*temp_cue2=NULL;
    position1=c->hash(c->hfunc1,key);
    position2=c->hash(c->hfunc2,key);
    temp_pair1=c->T1[position1];
    temp_pair2=c->T2[position2];

    if (temp_pair1!=NULL)
    {
        temp_cue1=pair_getCue(temp_pair1);
        query1=cue_compareTo(temp_cue1,key);
        if (query1==0) { return 1; }
    }

    if (temp_pair2!=NULL)
    {
        temp_cue2=pair_getCue(temp_pair2);
        query2=cue_compareTo(temp_cue2,key);
        if (query2==0) { return 1; }
    }

    return 0;
}





/* 
 * @COMPLEXITY: Theta(1)
 * 
 * The function cuckoo_remove(),takes two 
 * arguments as parameters.The first one
 * is a pointer to a cuckoo hash table
 * data structure and the second a pointer
 * to some key.This function checks if the
 * given key exists in the tables.If the key
 * exists them it is removed from the tables,
 * otherwise nothing happens.
 * 
 * @param:  cuckoo_t    *c
 * @param:  void        *key
 * @return: void
 * 
 */

void cuckoo_remove(cuckoo_t *c,void *key)
{
    assert(c!=NULL);
    int query1,query2;
    lluint position1,position2;
    pair_t *temp_pair1=NULL,*temp_pair2=NULL;
    cue_t *temp_cue1=NULL,*temp_cue2=NULL;
    if (cuckoo_lookup(c,key)==0) { return; }
    position1=c->hash(c->hfunc1,key);
    position2=c->hash(c->hfunc2,key);
    temp_pair1=c->T1[position1];
    temp_pair2=c->T2[position2];

    if (temp_pair1!=NULL)
    {
        temp_cue1=pair_getCue(temp_pair1);
        query1=cue_compareTo(temp_cue1,key);

        if (query1==0)
        {
            pair_free(temp_pair1);
            temp_pair1=NULL;
            c->T1[position1]=NULL;
            c->n--; cuckoo_loadFactor(c);
            return;
        }

    }

    if (temp_pair2!=NULL)
    {
        temp_cue2=pair_getCue(temp_pair2);
        query2=cue_compareTo(temp_cue2,key);

        if (query2==0)
        {
            pair_free(temp_pair2);
            temp_pair2=NULL;
            c->T2[position2]=NULL;
            c->n--; cuckoo_loadFactor(c);
            return;
        }
    }

    return;
}





/* 
 * @COMPLEXITY: Theta(1)
 * 
 * The function cuckoo_getValue(),takes two
 * arguments as parameters.The first one is
 * a pointer to a cuckoo hash table data
 * structure and the second one is a pointer
 * to a key.This function checks if the given
 * key exists in the tables.If so it returns
 * the value component of the pair data structure
 * associated with the given key value,otherwise
 * it returns NULL.
 * 
 * @param:  cuckoo_t    *c
 * @param:  void        *key
 * @return: void        *
 * 
 */

void *cuckoo_getValue(cuckoo_t *c,void *key)
{
    assert(c!=NULL);
    int query1,query2;
    lluint position1,position2;
    pair_t *temp_pair1=NULL,*temp_pair2=NULL;
    cue_t *temp_cue1=NULL,*temp_cue2=NULL;
    if (cuckoo_lookup(c,key)==0) { return NULL; }
    position1=c->hash(c->hfunc1,key);
    position2=c->hash(c->hfunc2,key);
    temp_pair1=c->T1[position1];
    temp_pair2=c->T2[position2];

    if (temp_pair1!=NULL)
    {
        temp_cue1=pair_getCue(temp_pair1);
        query1=cue_compareTo(temp_cue1,key);
        if (query1==0) { return pair_getValue(temp_pair1); }
    }

    if (temp_pair2!=NULL)
    {
        temp_cue2=pair_getCue(temp_pair2);
        query2=cue_compareTo(temp_cue2,key);
        if (query2==0) { return pair_getValue(temp_pair2); }
    }

    return NULL;
}




/* 
 * @COMPLEXITY: Theta(1)
 * 
 * The function cuckoo_changeValue(),takes three arguments
 * as parameters.The first one is a pointer to a cuckoo
 * hash table data structure,the second one is a pointer
 * to some key value and the last one is a pointer to
 * some new value to be associated with the given key.
 * This function checks if the given key value exists.
 * If the key exists it changes the value associated
 * with it.If the key does not exist nothing happens.
 * 
 * @param:  cuckoo_t    *c
 * @param:  void        *key
 * @param:  void        *value
 * @return: void
 * 
 */

void cuckoo_changeValue(cuckoo_t *c,void *key,void *value)
{
    assert(c!=NULL);
    int query1,query2;
    lluint position1,position2;
    value_t *old_value=NULL,*new_value=NULL;
    pair_t *temp_pair1=NULL,*temp_pair2=NULL;
    cue_t *temp_cue1=NULL,*temp_cue2=NULL;
    if (cuckoo_lookup(c,key)==0) { return; }
    position1=c->hash(c->hfunc1,key);
    position2=c->hash(c->hfunc2,key);
    temp_pair1=c->T1[position1];
    temp_pair2=c->T2[position2];

    if (temp_pair1!=NULL)
    {
        temp_cue1=pair_getCue(temp_pair1);
        query1=cue_compareTo(temp_cue1,key);

        if (query1==0)
        {
            old_value=pair_getValue(temp_pair1);
            new_value=value_create(value,old_value->cmp,
                    old_value->print,old_value->destroy);
            pair_changeValue(temp_pair1,new_value);
            return;
        }        
    }


    if (temp_pair2!=NULL)
    {
        temp_cue2=pair_getCue(temp_pair2);
        query2=cue_compareTo(temp_cue2,key);

        if (query2==0)
        {
            old_value=pair_getValue(temp_pair2);
            new_value=value_create(value,old_value->cmp,
                    old_value->print,old_value->destroy);
            pair_changeValue(temp_pair2,new_value);
            return;
        }
    }

    return;
}




/* 
 * @COMPLEXITY: O(n)
 * 
 * The function cuckoo_print(),takes as an
 * argument a pointer to a cuckoo hash table
 * data structure and prints all the pairs 
 * that exist in both tables in a user-friendly
 * format.
 * 
 * @param:  cuckoo_t    *c
 * @return: void
 * 
 */

void cuckoo_print(cuckoo_t *c)
{
    lluint i;
    assert(c!=NULL);
    pair_t *temp_pair=NULL;
    printf("-------CUCKOO_HASH--------\n");
    printf("total = %lld, load factor = %.2lf\n",c->n,c->lf);
    printf("INDEX: TABLE_1, TABLE_2\n");

    for (i=0;i<c->size;i++)
    {
        printf("%lld:",i); temp_pair=c->T1[i];
        if (temp_pair!=NULL) { pair_print(temp_pair); }
        else { printf("____"); }
        printf(", "); temp_pair=c->T2[i];
        if (temp_pair!=NULL) { pair_print(temp_pair); }
        else { printf("____"); }
        printf("\n");
    }

    printf("-----------END-------------\n");
    return;
}





/* 
 * @COMPLEXITY: O(n)
 * 
 * The function cuckoo_free(),takes as an
 * argument a pointer to a cuckoo hash table
 * data structure and deallocates the memory
 * chunk associated with it and it's components,
 * including all the pair data structures that
 * exist in the two tables.
 * 
 * @param:  cuckoo_t    *c
 * @return: void
 * 
 */

void cuckoo_free(cuckoo_t *c)
{
    lluint i;
    assert(c!=NULL);

    for (i=0;i<c->size;i++)
    {
        if (c->T1[i]!=NULL)
        {
            pair_free(c->T1[i]);
            c->T1[i]=NULL;
        }

        if (c->T2[i]!=NULL)
        {
            pair_free(c->T2[i]);
            c->T2[i]=NULL;
        }
    }

    free(c->T1); c->T1=NULL;
    free(c->T2); c->T2=NULL;
    hashfn_free(c->hfunc1); c->hfunc1=NULL;
    hashfn_free(c->hfunc2); c->hfunc2=NULL;
    c->n=0; c->size=0;
    free(c); c=NULL;
    return;
}
