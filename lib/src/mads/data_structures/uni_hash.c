#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/algorithms/random.h>
#include <mads/data_structures/uni_hash.h>


static int uni_hash_is_prime(const unsigned long long int n)
{
    int isprime = 1;
    if (n < 2) { return 0; }

    for (unsigned long long int divisor = 2; divisor * divisor <= n; divisor++)
    {
        if (n % divisor == 0)
        {
            isprime = 0;
            break;
        }
    }

    return isprime;
}


static unsigned long long int uni_hash_next_prime(const unsigned long long int n)
{
    assert(n != 0);
    unsigned long long int step = n + 1;

    while (uni_hash_is_prime(step) == 0)
    {
        step++;
    }

    return step;
}


mads_uni_hash_t *mads_uni_hash_create(const unsigned long long int ts, const unsigned long long int k)
{
    mads_uni_hash_t *h = NULL;
    assert(ts != 0 && k != 0);
    h = (mads_uni_hash_t *)malloc(sizeof(*h));
    assert(h != NULL);
    h->kvalue = k;
    h->tabsize = ts;
    h->values = (unsigned long long int *)malloc(k * sizeof(unsigned long long int));
    assert(h->values != NULL);

    for (unsigned long long int i = 0; i < k; i++)
    {
        h->values[i] = uni_hash_next_prime(ts + mads_genrand64_int64() % ts);
    }

    return h;
}


unsigned long long int *mads_uni_hash_get_values(const mads_uni_hash_t *h)
{
    assert(h != NULL);
    return h->values;
}


unsigned long long int mads_uni_hash_get_table_size(const mads_uni_hash_t *h)
{
    assert(h != NULL);
    return h->tabsize;
}


unsigned long long int mads_uni_hash_get_k(const mads_uni_hash_t *h)
{
    assert(h != NULL);
    return h->kvalue;
}


void mads_uni_hash_print(const mads_uni_hash_t *h)
{
    assert(h != NULL);
    printf("table_size=%llu, k=%llu, values=[ ",
        h->tabsize, h->kvalue);

    for (unsigned long long int i = 0; i < h->kvalue; i++)
    {
        printf("%llu, ", h->values[i]);
    }

    printf("\b\b ]");
}


void mads_uni_hash_free(mads_uni_hash_t *h)
{
    assert(h != NULL);
    h->kvalue = 0;
    h->tabsize = 0;
    free(h->values);
    h->values = NULL;
    free(h);
    h = NULL;
}
