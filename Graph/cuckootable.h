/*
 * This file contains data type definitions
 * and function prototyping of procedures
 * regarding the cuckoo hash table data
 * structure.
 * 
 * @param:  Endri Kastrati
 * @date:   10/01/2017
 * 
 */



/*
 * Using include guards to check if the
 * cuckootable.h header file has been included
 * at least once.If it hasn't the compiler
 * copy-pastes everything into the file 
 * that is including it.If the file on the
 * other hand has been included the compiler
 * skips the contents entirely.
 * 
 */

#ifndef CUCKOOTABLE_H
#define CUCKOOTABLE_H




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
 * Defining a macro constant called
 * INITIAL_SIZE that represents the
 * initial size of the two tables
 * that are used in the cuckoo
 * hash table data structure.
 * 
 */

#define INITIAL_CUCKOO_SIZE         53
#define MAX_LOOP_ITERATIONS         26




/*
 * Defining an alias for the unsigned long long int native
 * type.Defining a new datatype of function pointer called 
 * CuckooHashFn.This function has to take two arguments
 * as parameters.The first parameter is a pointer to a
 * hashfn_t data structure.The second one is a pointer
 * to some immutable data address.This interface enables
 * the users to create their own hashing functions as
 * long as they abide by the following function signature.
 * The users are responsible for the creation of this function.
 * 
 */

typedef unsigned long long int      lluint;

typedef lluint  (*CuckooHashFn)(hashfn_t *,const void *);




/*
 * This is the C implementation of the cuckoo
 * hash table data structure.This enhanced
 * version contains as components two arrays
 * of void pointers,the total number of elements
 * in both arrays,the size of the arrays which has
 * to be equal for both,the load factor as well as
 * two universal hashing function data structures 
 * and a function pointer that calculates the hashes.
 */

typedef struct 
{
    void                **T1;
    void                **T2;
    lluint              n;
    lluint              size;
    double              lf;
    hashfn_t            *hfunc1;
    hashfn_t            *hfunc2;
    CuckooHashFn        hash;
} cuckoo_t;



/* 
 * Function prototyping of procedures
 * regarding the cuckoo hash table
 * data structure such as create,insert,
 * lookup,remove etc..
 * 
 */

cuckoo_t        *cuckoo_create(CuckooHashFn hash);
void            cuckoo_insert(cuckoo_t *c,pair_t *p);
int             cuckoo_lookup(cuckoo_t *c,void *key);
void            cuckoo_remove(cuckoo_t *c,void *key);
void            *cuckoo_getValue(cuckoo_t *c,void *key);
void            cuckoo_changeValue(cuckoo_t *c,void *key,void *value);
void            cuckoo_print(cuckoo_t *c);
void            cuckoo_free(cuckoo_t *c);


/* 
 * Once everything has been copy-pasted by
 * the compiler and the macro CUCKOOTABLE_H
 * has been defined,the cuckootable.h header
 * file will not be included more than once.
 *  
 */

#endif
