/*
 * This file contains data type definitions
 * and function prototypings for the hash
 * table data structure.
 *
 * @author: Endri Kastrati
 * @date:   9/12/2015
 *
 */




/*
 * Using include guards to check if the
 * hashtable.h header file has been included
 * at least once.If it hasns't the compiler
 * copy-pastes everything into the file that
 * is including it.If the file on the other
 * hand has been included the compiler
 * skips the contents entirely.
 *
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H





/*
 * Defining a constant that 
 * represents the initial size
 * of the hash table.The number
 * 1097 is a prime number.Having
 * a prime number as the initial size
 * serves as well into the hashing
 * procedure of elements into the table.
 *
 */

#define INITIAL_SIZE    1097





/*
 * Defining an alias for the unsigned integer native type.
 * Defining four new data types of function pointers called
 * TableHashFn,TableCompareFn,TablePrintFn and TableDestroyFn.
 * These function pointers enable polymorphism by specifying
 * an interface for the hashing,comparison,printing and memory
 * deallocation functions.These functions have to be written
 * by the user and meet the following criteria.
 *
 */

typedef unsigned int    uint;

typedef uint    (*TableHashFn)(uint,const void *);
typedef int     (*TableCompareFn)(const void *,const void *);
typedef void    (*TablePrintFn)(const void *);
typedef void    (*TableDestroyFn)(void *);




/*
 * Defining a new data type that represents
 * the abstract concept of a pair <key,value>
 * which will be used to store the corresponding
 * key and value component of the hash table elements.
 *
 */

typedef struct
{
    void    *key;
    void    *data;
} pair_t;



/*
 * This is the C implementation of the Hash
 * Table data structure.This enhanced version
 * contains as components an array of void pointers A,
 * n which represents the total number of slots that
 * are filled,table_size which represents the maximum
 * number of buckets the table contains and three
 * function pointers hash,cmp,print,destroy to enable
 * polymorphism.
 *
 */

typedef struct
{
    void                **A;
    uint                n;
    uint                table_size;
    TableHashFn         hash;
    TableCompareFn      cmp;
    TablePrintFn        print;
    TableDestroyFn      destroy;
} htable_t;





/*
 * Function prototyping of procedures 
 * regarding the hash table data structure
 * such as insert,lookup,remove etc..
 *
 */

htable_t    *htable_create(TableHashFn hash,TableCompareFn cmp,TablePrintFn print,TableDestroyFn destroy);
void        htable_insert(htable_t *t,void *key,void *data);
void        htable_remove(htable_t *t,void *key);
int         htable_lookup(htable_t *t,void *key);
void        *htable_getValue(htable_t *t,void *key);
void        htable_print(htable_t *t);
void        htable_free(htable_t *t);




/*
 * Once everything has been copy-pasted by
 * the compiler and the macro HASHTABLE_H 
 * has been defined, the hashtable.h header
 * file  will not be included more than once.
 *
 */

#endif