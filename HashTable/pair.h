/*
 * This file contains data type definitions
 * and function prototypings regarding the
 * pair data structure that represents a
 * cue/value tuple.
 *
 * @author: Endri Kastrati
 * @date:   30/12/2016
 * 
 */




/*
 * Using include guards to check if the
 * pair.h header file has been included
 * at least once.If it hasn't the compiler
 * copy-pastes everything into the file 
 * that is including it.If the file on the
 * other hand has been included the compiler
 * skips the contents entirely.
 * 
 */

#ifndef PAIR_H
#define PAIR_H





/*
 * Defining three new data types of function pointers
 * called KeyCompareFn,KeyPrintFn and KeyDestroyFn.
 * These functions enable polymorphism by specifying
 * an interface for the comparison,printing and memory
 * deallocation function.These functions have to be
 * written by the user and meet the following criteria.
 * These function signatures will be used for the cue_t
 * data structure, that represents the key component of
 * a pair data structure.
 *
 */

typedef int     (*KeyCompareFn)(const void *,const void *);
typedef void    (*KeyPrintFn)(const void *);
typedef void    (*KeyDestroyFn)(void *);




/*
 * Defining three new datat types of of function pointers
 * called ValueCompareFn,ValuePrintFn and ValueDestroyFn.
 * These functions enable polymorphism by specifying an
 * interface for the comparison,printing and memory 
 * deallocation function.These functions have to be
 * written by the user and mee the following criteria.
 * These function signatures will be used for the value_t
 * data structure, that represents the value component 
 * associated with a key in a pair data structure.
 *
 */

typedef int     (*ValueCompareFn)(const void *,const void *);
typedef void    (*ValuePrintFn)(const void *);
typedef void    (*ValueDestroyFn)(void *);





/*
 * Defining a new data structure called cue_t.
 * This datatype represents the key component
 * in a pair data structure.It has as fileds a 
 * pointer  to some key, and three function 
 * pointers cmp,print and destroy that enable 
 * polymorphism (The name cue is a synonym for key).
 *
 */

typedef struct 
{
    void            *cue;
    KeyCompareFn    cmp;
    KeyPrintFn      print;
    KeyDestroyFn    destroy;
} cue_t;





/*
 * Defining a new data structure called value_t.
 * This datatype represents the value component
 * associated with a key in the pair data structure.
 * It has as fields a void pointer to some value,
 * and three function pointers cmp,print and destroy
 * that enable polymorphism.
 *
 */

typedef struct 
{   
    void                *value;
    ValueCompareFn      cmp; 
    ValuePrintFn        print;
    ValueDestroyFn      destroy;
} value_t;





/*
 * Defining a new data structure called pair_t.
 * This datatype represents the abstract concept
 * of a pair,meaning an object that has a key and
 * a value which is associated with that key.It has
 * as fields the data structures defined above,namely
 * cue_t and value_t.
 *
 */

typedef struct 
{
    cue_t       *k;
    value_t     *v;
} pair_t;





/*
 * Function prototypings of procedures 
 * regarding the cue data structure such
 * as create,get,print, etc..
 *
 */

cue_t           *cue_create(void *cue,KeyCompareFn cmp,KeyPrintFn print,KeyDestroyFn destroy);
void            *cue_get(cue_t *k);
int             cue_compareTo(cue_t *k,void *data);
void            cue_print(cue_t *k);
void            cue_free(cue_t *k);



/*
 * Function prototypings of procedures
 * regarding the value data structure
 * such as create,get,print, etc..
 *
 */

value_t         *value_create(void *value,ValueCompareFn cmp,ValuePrintFn print,ValueDestroyFn destroy);
void            *value_get(value_t *v);
int             value_compareTo(value_t *v,void *data);
void            value_print(value_t *v);
void            value_free(value_t *v);




/*
 * Function prototypings of procedures
 * regarding the pair data structure
 * such as create,getCue,getValue etc..
 * 
 */

pair_t          *pair_create(cue_t *k,value_t *v);
cue_t           *pair_getCue(pair_t *p);
value_t         *pair_getValue(pair_t *p);
void            pair_changeCue(pair_t *p,cue_t *new_k);
void            pair_changeValue(pair_t *p,value_t *new_v);
void            pair_print(pair_t *p);
void            pair_free(pair_t *p);





/*
 * Once everything has been copy-pasted by
 * the compiler and the macro PAIR_H has
 * been defined, the pair.h header file 
 * will not be included more than once.
 *
 */

#endif
