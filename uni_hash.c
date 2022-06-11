//
// Created by p0int3r on 6/12/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "algorithms/random.h"
#include "uni_hash.h"



static int uni_hash_is_prime(lluint n)
{
    int isprime=1;
    lluint divisor;
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


static lluint uni_hash_next_prime(lluint n)
{
    lluint step;
    assert(n!=0);
    step=n+1;

    while (uni_hash_is_prime(step) == 0)
    {
        step++;
    }

    return step;
}


uni_hash_t *uni_hash_create(lluint ts, lluint k)
{
    lluint i;
    uni_hash_t *h=NULL;
    assert(ts!=0 && k!=0);
    h=(uni_hash_t *)malloc(sizeof(*h));
    assert(h!=NULL);
    h->kvalue=k; h->tabsize=ts;
    h->values=(lluint *)malloc(k*sizeof(lluint ));
    assert(h->values!=NULL);

    for (i=0;i<k;i++)
    {
        h->values[i]= uni_hash_next_prime(ts + genrand64_int64() % ts);
    }

    return h;
}


lluint *uni_hash_get_values(uni_hash_t *h)
{
    assert(h!=NULL);
    return h->values;
}



lluint uni_hash_get_table_size(uni_hash_t *h)
{
    assert(h!=NULL);
    return h->tabsize;
}


lluint uni_hash_get_k(uni_hash_t *h)
{
    assert(h!=NULL);
    return h->kvalue;
}



void uni_hash_print(uni_hash_t *h)
{
    lluint i;
    assert(h!=NULL);
    printf("table_size=%llu, k=%llu, values=[ ",
           h->tabsize,h->kvalue);

    for (i=0;i<h->kvalue;i++)
    {
        printf("%llu, ",h->values[i]);
    }

    printf("\b\b ]");
}


void uni_hash_free(uni_hash_t *h)
{
    assert(h!=NULL);
    h->kvalue=0;
    h->tabsize=0;
    free(h->values);
    h->values=NULL;
    free(h); h=NULL;
}
