/*
 * This file contains definitions for
 * operations and procedures regarding
 * the cue,value and pair data structures.
 * 
 * @author: Endri Kastrati
 * @date:   30/12/2016
 * 
 */




/*
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertions library and the
 * header file pair.h that contains datatype
 * definitions and function prototypings for
 * the cue,value and pair data structures.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pair.h"




////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////////////////
//
//
//      DEFINITION OF THE CUE DATA STRUCTURE
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////


/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function cue_create(),takes four arguments,
 * namely a pointer to some data and three function
 * pointers.It creates a new cue_t data structure by
 * allocating memory for it and it's components and
 * instantiates it's components to the default values.
 * The print and cmp components are mandatory and cannot
 * be null.The users have to create their own cmp,print
 * and destroy (optional) functions.Failure to do so will
 * result in program termination due to invalide assertions.
 * 
 * @param:  void            *cue
 * @param:  KeyCompareFn    cmp
 * @param:  KeyPrintFn      print
 * @param:  KeyDestroyFn    destroy
 * @return: cue_t           *
 * 
 */

cue_t *cue_create(void *cue,KeyCompareFn cmp,KeyPrintFn print,KeyDestroyFn destroy)
{
    cue_t *new_cue=NULL;
    assert(cue!=NULL && cmp!=NULL && print!=NULL);
    new_cue=(cue_t *)malloc(sizeof(*new_cue));
    assert(new_cue!=NULL);
    new_cue->cue=cue;
    new_cue->cmp=cmp;
    new_cue->print=print;
    new_cue->destroy=destroy;
    return new_cue;
}




/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function cue_get(),takes a cue_t
 * data structure as an argument and 
 * returns it's cue component.
 * 
 * @param:  cue_t       *k
 * @return: void        *
 * 
 */

void *cue_get(cue_t *k)
{
    assert(k!=NULL);
    return k->cue;
}



/* 
 * @COMPLEXITY: Theta(1) best cases, O(F(n))
 *              for worst cases where F(n)
 *              is some type of mathematical 
 *              function depending on the
 *              datatype.
 * 
 * The function cue_compareTo(),takes two
 * arguments,namely a cue_t data structure
 * and a pointer to some data and compares
 * the value of the cue with the given data.
 * 
 * @param:  cue_t               *k
 * @param:  const void          *data
 * @return: int
 * 
 */

int cue_compareTo(cue_t *k,const void *data)
{
    int result;
    assert(k!=NULL && data!=NULL);
    result=k->cmp(k->cue,data);
    return result;
}



/* 
 * @COMPLEXITY: Theta(1) best cases, O(F(n))
 *              for worst cases where F(n)
 *              is some type of mathematical 
 *              function depending on the
 *              datatype.
 * 
 * The function cue_print() takes as an argument
 * a cue_t data structure and prints it's cue value.
 * 
 * @param:  cue_t       *k
 * @return: void
 * 
 */

void cue_print(cue_t *k)
{
    assert(k!=NULL);
    k->print(k->cue);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function cue_free(),takes as an argument
 * a cue_t data structure and deallocates memory
 * for it and it's components.
 * 
 * @param:  cue_t       *k
 * @return: void
 * 
 */

void cue_free(cue_t *k)
{
    assert(k!=NULL);
    if (k->destroy!=NULL) { k->destroy(k->cue); }
    k->cmp=NULL;
    k->print=NULL;
    k->destroy=NULL;
    free(k); k=NULL;
    return;
}


////////////////////////////////////////////////////////////////////////////////////////








////////////////////////////////////////////////////////////////////////////////////////
//
//
//      DEFINITION OF THE VALUE DATA STRUCTURE
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////



/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function value_create(),takes four arguments,
 * namely a pointer to some data and three function
 * pointers.It creates a new value_t data structure by
 * allocating memory for it and it's components and
 * instantiates it's components to the default values.
 * The print and cmp components are mandatory and cannot
 * be null.The users have to create their own cmp,print
 * and destroy (optional) functions.Failure to do so will
 * result in program termination due to invalide assertions.
 * 
 * @param:  void            *value
 * @param:  KeyCompareFn    cmp
 * @param:  KeyPrintFn      print
 * @param:  KeyDestroyFn    destroy
 * @return: value_t         *
 * 
 */

value_t *value_create(void *value,ValueCompareFn cmp,ValuePrintFn print,ValueDestroyFn destroy)
{
    value_t *new_value=NULL;
    assert(value!=NULL && cmp!=NULL && print!=NULL);
    new_value=(value_t *)malloc(sizeof(*new_value));
    assert(new_value!=NULL);
    new_value->value=value;
    new_value->cmp=cmp;
    new_value->print=print;
    new_value->destroy=destroy;
    return new_value;
}



/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function value_get(),takes a value_t
 * data structure as an argument and returns
 * it's value component.
 * 
 * @param:  value_t     *v
 * @return: void        *
 * 
 */

void *value_get(value_t *v)
{
    assert(v!=NULL);
    return v->value;
}




/* 
 * @COMPLEXITY: Theta(1) best cases, O(F(n))
 *              for worst cases where F(n)
 *              is some type of mathematical 
 *              function depending on the
 *              datatype.
 * 
 * The function value_compareTo(),takes two
 * arguments,namely a value_t data structure
 * and a pointer to some data and compares
 * the value field of the value_t with the 
 * given data.
 * 
 * @param:  value_t             *v
 * @param:  const void          *data
 * @return: int
 * 
 */

int value_compareTo(value_t *v,const void *data)
{
    int result;
    assert(v!=NULL && data!=NULL);
    result=v->cmp(v->value,data);
    return result;
}



/* 
 * @COMPLEXITY: Theta(1) best cases, O(F(n))
 *              for worst cases where F(n)
 *              is some type of mathematical 
 *              function depending on the
 *              datatype.
 * 
 * The function value_print() takes as an argument
 * a value_t data structure and prints it's value
 * component.
 * 
 * @param:  value_t     *v
 * @return: void
 * 
 */

void value_print(value_t *v)
{
    assert(v!=NULL);
    v->print(v->value);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function value_free(),takes as an argument
 * a value_t data structure and deallocates memory
 * for it and it's components.
 * 
 * @param:  value_t     *v
 * @return: void
 * 
 */

void value_free(value_t *v)
{
    assert(v!=NULL);
    if (v->destroy!=NULL) { v->destroy(v->value); }
    v->cmp=NULL;
    v->print=NULL;
    v->destroy=NULL;
    free(v); v=NULL;
    return;
}


////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////
//
//
//      DEFINITION OF THE PAIR DATA STRUCTURE
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////




/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function pair_create() takes two
 * arguments.The first argument is a cue_t
 * data structure.The second argument is a
 * value_t data structure associated with
 * the given cue_t data structure.This function
 * creates a new pair datatype by allocating
 * memory for it and it's components and
 * instantiating them to the given parameters.
 * 
 * @param:  cue_t       *k
 * @param:  value_t     *v
 * @return: pair_t      *
 * 
 */

pair_t  *pair_create(cue_t *k,value_t *v)
{
    pair_t *new_pair=NULL;
    assert(k!=NULL);
    new_pair=(pair_t *)malloc(sizeof(*new_pair));
    assert(new_pair!=NULL);
    new_pair->k=k;
    new_pair->v=v;
    return new_pair;
}



/* 
 * @COMPLEXITY: Theta(1)
 * 
 * The function pair_getCue(),takes a pair_t
 * data structure as an argument and returns
 * the cue_t component of the pair datatype.
 * 
 * @param:  pair_t      *p
 * @return: cue_t       *
 *  
 */

cue_t *pair_getCue(pair_t *p)
{
    assert(p!=NULL);
    return p->k;
}



/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function pair_getValue() takes a pair_t
 * data structure as an argument and returns the
 * value_t component of the pair datatype.
 *
 */

value_t *pair_getValue(pair_t *p)
{
    assert(p!=NULL);
    return p->v;
}




/* 
 * @COMPLEXITY: Theta(1)
 * 
 * The function pair_changeCue() takes two
 * arguments as parameters,namely a pair_t
 * datatype and a new cue_t datatype and
 * replaces the old one with the given one.
 * 
 * @param:  pair_t      *p
 * @param:  cue_t       *new_k
 * @return: void
 * 
 */

void pair_changeCue(pair_t *p,cue_t *new_k)
{
    cue_t *old_cue=NULL;
    assert(p!=NULL);
    old_cue=pair_getCue(p);
    cue_free(old_cue);
    p->k=new_k;
    return;
}   




/*
 * @COMPLEXITY: Theta(1)
 * 
 * The function pair_changeValue() takes two
 * arguments as parameters,namely a pair_t
 * datatype and a new value_t datatype and
 * replaces the old one with the given one.
 * 
 * @param:  pair_t      *p
 * @param:  value_t     *new_v
 * @return: void
 * 
 */

void pair_changeValue(pair_t *p,value_t *new_v)
{
    value_t *old_value=NULL;
    assert(p!=NULL);
    old_value=pair_getValue(p);
    value_free(old_value);
    p->v=new_v;
    return;
}



/*
 * @COMPLEXITY: Theta(1) best cases, O(F(n))
 *              for worst cases where F(n)
 *              is some type of mathematical 
 *              function depending on the
 *              datatype.
 * 
 * The function pair_print() takes a pair_t
 * data structure as an argument and prints
 * both the cue_t and value_t components in
 * a user-friendly format.
 * 
 * @param:  pair_t      *p
 * @return: void
 * 
 */

void pair_print(pair_t *p)
{
    cue_t *temp_cue=NULL;
    value_t *temp_value=NULL;
    temp_cue=pair_getCue(p);
    temp_value=pair_getValue(p);
    assert(p!=NULL);
    printf("{ ");
    cue_print(temp_cue);
    printf(" : ");
    value_print(temp_value);
    printf(" }");
    return;
}



/* 
 * @COMPLEXITY: Theta(1)
 * 
 * The function pair_free() takes a pair_t
 * data structure as an argument and deallocates
 * memory for it and it's components.
 * 
 * @param:  pair_t      *p
 * @return: void
 * 
 */

void pair_free(pair_t *p)
{
    assert(p!=NULL);
    cue_free(pair_getCue(p));
    value_free(pair_getValue(p));
    free(p); p=NULL;
    return;
}


////////////////////////////////////////////////////////////////////////////////////////
