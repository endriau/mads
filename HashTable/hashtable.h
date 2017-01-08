/*
 * The following file contains datatype
 * definitions and function prototyping
 * regarding the seperate chaining hash
 * table data structure.
 * 
 * @author: Endri Kastrati
 * @date:   1/01/2017
 *
 */





/*
 * Using include guards to check if the
 * hashtable.h header file has been included
 * at least once.If it hasn't the compiler
 * copy-pastes everything into the file 
 * that is including it.If the file on the
 * other hand has been included the compiler
 * skips the contents entirely.
 * 
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H




/* 
 * Including the pair.h and uhash.h
 * headers files that contain datatype
 * definitions and function prototyping
 * for the pair_t data structure and the
 * hashfn_t data structure.For more detailed
 * explanation of the datatypes consult their
 * corresponding header files.
 * 
 */

#include "pair.h"
#include "uhash.h"





/*
 * Defining three macro constants.
 * The first one,namely INITIAL_SIZE,
 * represents the initial size of the
 * hash table.The rest,namely CHAIN_LIST
 * and CHAIN_TREE represent the possible
 * types of hash table buckets,namely a
 * linked list or an avl tree.
 *
 */
#define INITIAL_SIZE    107
#define CHAIN_LIST      76
#define CHAIN_TREE      84





/*
 * Defining an alias for the unsigned long long int native
 * type.Defining a new datatype of function pointer called 
 * TableHashFn.This function has two take two arguments
 * as parameters.The first parameter is a pointer to a
 * hashfn_t data structure.The second one is a pointer
 * to some immutable data address.This interface enables
 * the users to create their own hashing functions as
 * long as they abide by the following function signature.
 * The users are responsible for the creation of this function.
 * 
 */

typedef unsigned long long int    lluint;

typedef lluint    (*TableHashFn)(hashfn_t *,const void *);





/* 
 * This is the C implementation of the hash table
 * data structure.This ehanced version contains as
 * components an array of void pointers that represents
 * the buckets in the table,the type of seperate chaining
 * being used,the total number of elements in the hash
 * table,the size of the table,the load factor as well
 * as a universal hashing function data structure and a
 * function that calculates the hash.
 * 
 */

typedef struct
{
    void                **A;
    int                 type;
    lluint              n;
    lluint              size;
    double              lf;
    hashfn_t            *hfunc;
    TableHashFn         hash;
} table_t;




/*
 * Function prototyping of procedures
 * regarding the hash table data structure
 * such as create,insert,lookup,remove etc..
 * 
 */

table_t     *table_create(TableHashFn hash,int chain_type);
void        table_insert(table_t *t,pair_t *p);
int         table_lookup(table_t *t,void *key);
void        table_remove(table_t *t,void *key);
void        *table_getValue(table_t *t,void *key);
void        table_changeValue(table_t *t,void *key,void *value);
void        table_print(table_t *t);
void        table_free(table_t *t);



/* 
 * Once everything has been copy-pasted by
 * the compiler and the macro HASHTABLE_H
 * has been defined,the hashtable.h header
 * file will not be included more than once.
 *  
 */

#endif
