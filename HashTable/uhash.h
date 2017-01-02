/*
 * This file contains data type definitions
 * and function prototyping regarding the
 * universal hash function data structure.
 *
 * @author: Endri Kastrati
 * @date:   30/12/2016
 *
 */



/*
 * Using include guards to check if the
 * uhash.h header file has been included
 * at least once.If it hasn't the compiler
 * copy-pastes everything into the file 
 * that is including it.If the file on the
 * other hand has been included the compiler
 * skips the contents entirely.
 * 
 */

#ifndef UHASH_H
#define UHASH_H





/*
 * Defining an alias for the unsigned integer
 * native type and a new data structure that
 * represents a universal hash function that 
 * satisfies the universal hashing properties.
 * This data structure has as components the 
 * value k, where k represents the total prime 
 * numbers chosen randomly from the range 
 * (0,tabsize-1),an array that contains 
 * those numbers and the total size of the 
 * current table.
 *
 */

typedef unsigned int    uint;

typedef struct
{
    uint    kvalue;
    uint    *values;
    uint    tabsize;
} hashfn_t;




/*
 * Function prototyping of procedures regarding
 * the universal hash function data structure
 * such as create,get,free, etc..
 *
 */

hashfn_t    *hashfn_create(uint ts,uint k);
uint        *hashfn_getValues(hashfn_t *h);
uint        hashfn_getTableSize(hashfn_t *h);
uint        hashfn_getK(hashfn_t *h);
void        hashfn_print(hashfn_t *h);
void        hashfn_free(hashfn_t *h);





/*
 * Once everything has been copy-pasted by
 * the compiler and the macro UHASH_H has
 * been defined, the uhash.h header file
 * will not be included more than once.
 * 
 */

#endif
