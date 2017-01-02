/*
 * This file contains definitions for
 * operations and procedures regarding
 * the universal hash function data
 * structure.
 *
 * @author: Endri Kastrati
 * @date:   30/12/2016
 * 
 */



/*
 * Including the standard input-output library,
 * the standard utilities library,standard assertion
 * library,standard time library and the uhash.h
 * header file that contains datatype definitions
 * and function prototyping for the universal hash
 * function data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "uhash.h"






/*
 * @COMPLEXITY: O(sqrt(n))
 *
 * The static function is_prime() takes only
 * one argument as a parameter,namely an unsigned
 * integer value and checks whether it constitutes
 * a prime number or not.If the given number is a
 * prime it returns one,otherwise it returns zero.
 *
 * @param:  uint   n
 * @return: int
 *
 */

static int is_prime(uint n)
{
    uint divisor;
    uint isprime=1;
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
 * @param:  uint    n
 * @return: uint
 *
 */

static uint next_prime(uint n)
{
    uint step;
    assert(n!=0);
    step=n+1;

    while (is_prime(step)==0)
    {
        step++;
    }

    return step;
}





/*
 * @COMPLEXITY: O(k), where k is the given number.
 *
 * The function hashfn_create(),takes two arguments
 * as parameters.The first argument is an unsigned
 * integer that represents the size of a table.The
 * second argument is an unsigned integer as well
 * and represents the total number of random prime 
 * indices to be selected from the table.This function 
 * instantiates the universal hash function data 
 * structure by allocating memory for it and it's 
 * components.
 *
 * @param:  uint            ts
 * @param:  uint            k
 * @return: hashfn_t        *
 *
 */

hashfn_t *hashfn_create(uint ts,uint k)
{
    int i;
    time_t seed;
    hashfn_t *h=NULL;
    assert(ts!=0 && k>=0);
    srand((unsigned )time(&seed));
    h=(hashfn_t *)malloc(sizeof(*h));
    assert(h!=NULL);
    h->kvalue=k; h->tabsize=ts;
    h->values=(uint *)malloc(k*sizeof(uint ));
    assert(h->values!=NULL);

    for (i=0;i<k;i++)
    {
        h->values[i]=next_prime(ts+rand()%ts);
    }

    return h;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function hashfn_getValues(),takes
 * a universal hash function data structure
 * as a parameter and returns it's values
 * component that contains the randomly
 * selected prime indices.
 *
 * @param:  hashfn_t    *h
 * @return: uint        *
 *
 */

uint *hashfn_getValues(hashfn_t *h)
{
    assert(h!=NULL);
    return h->values;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function hashfn_getTableSize(),takes
 * a universal hash function data structure
 * as an argument and returns the table
 * size that has been assigned to it.
 *
 * @param:  hashfn_t    *h
 * @return: uint        
 *
 */

uint hashfn_getTableSize(hashfn_t *h)
{
    assert(h!=NULL);
    return h->tabsize;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function hashfn_getK(),takes 
 * a universal hash function data
 * structure as an argument and
 * returns the k value that has
 * been assigned to it.
 *
 * @param:  hashfn_t    *h
 * @return: uint
 *
 */

uint hashfn_getK(hashfn_t *h)
{
    assert(h!=NULL);
    return h->kvalue;
}





/*
 * @COMPLEXITY: O(k)
 *
 * The function hashfn_print(),takes
 * a universal hash function data
 * structure as an argument and prints
 * it's components in a user-friendly
 * format.
 *
 * @param:  hashfn_t    *h
 * @return: void
 *
 */

void hashfn_print(hashfn_t *h)
{
    int i;
    assert(h!=NULL);
    printf("table_size=%u, k=%u, values=[ ",
        h->tabsize,h->kvalue);

    for (i=0;i<h->kvalue;i++)
    {
        printf("%u, ",h->values[i]);
    }

    printf("\b\b ]\n");
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function hashfn_free(),takes 
 * a universal hash function data
 * structure as an argument and
 * deallocates memory for it and
 * it's components.
 *
 * @param:  hashfn_t    *h
 * @return: void
 *
 */

void hashfn_free(hashfn_t *h)
{
    assert(h!=NULL);
    h->kvalue=0;
    h->tabsize=0;
    free(h->values);
    h->values=NULL;
    free(h); h=NULL;
    return;
}
