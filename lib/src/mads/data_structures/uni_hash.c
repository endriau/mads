// ReSharper disable CppDFANullDereference


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/algorithms/random.h>
#include <mads/data_structures/uni_hash.h>


// Checks if the given number n is a prime number
static int uni_hash_is_prime(const unsigned long long int n)
{
    int isprime = 1; // Initially assume n is prime

    if (n < 2) { return 0; } // Any number less than 2 is not a prime

    // Check for factors from 2 up to the square root of n
    for (unsigned long long int divisor = 2; divisor * divisor <= n; divisor++)
    {
        if (n % divisor == 0) // If n is divisible by any divisor, it is not a prime
        {
            isprime = 0;
            break;
        }
    }

    return isprime; // Return whether n is prime
}

// Finds the next prime number greater than the given number n
static unsigned long long int uni_hash_next_prime(const unsigned long long int n)
{
    assert(n != 0); // Ensure n is not zero

    unsigned long long int step = n + 1; // Initialize the step to be n+1

    // Increment step until a prime number is found
    while (uni_hash_is_prime(step) == 0)
    {
        step++;
    }

    return step; // Return the next prime number
}

// Creates a new uniform hash with the given table size and k value
mads_uni_hash_t *mads_uni_hash_create(const unsigned long long int ts, const unsigned long long int k)
{
    mads_uni_hash_t *h = NULL;
    assert(ts != 0 && k != 0); // Ensure both ts and k are not zero

    h = (mads_uni_hash_t *)malloc(sizeof(mads_uni_hash_t)); // Allocate memory for the hash structure
    assert(h != NULL); // Ensure allocation was successful

    h->kvalue = k; // Set the k value
    h->tabsize = ts; // Set the table size

    h->values = (unsigned long long int *)malloc(k * sizeof(unsigned long long int)); // Allocate memory for the values array
    assert(h->values != NULL); // Ensure allocation was successful

    // Populate the values array with prime numbers
    for (unsigned long long int i = 0; i < k; i++)
    {
        h->values[i] = uni_hash_next_prime(ts + mads_genrand64_int64() % ts);
    }

    return h; // Return the newly created hash structure
}

// Retrieves the values array from the given hash structure
unsigned long long int *mads_uni_hash_get_values(const mads_uni_hash_t *h)
{
    assert(h != NULL); // Ensure the hash structure is not NULL
    return h->values; // Return the values array
}

// Retrieves the table size from the given hash structure
unsigned long long int mads_uni_hash_get_table_size(const mads_uni_hash_t *h)
{
    assert(h != NULL); // Ensure the hash structure is not NULL
    return h->tabsize; // Return the table size
}

// Retrieves the k value from the given hash structure
unsigned long long int mads_uni_hash_get_k(const mads_uni_hash_t *h)
{
    assert(h != NULL); // Ensure the hash structure is not NULL
    return h->kvalue; // Return the k value
}

// Prints the details of the given hash structure
void mads_uni_hash_print(const mads_uni_hash_t *h)
{
    assert(h != NULL); // Ensure the hash structure is not NULL
    printf("table_size=%llu, k=%llu, values=[ ", h->tabsize, h->kvalue); // Print table size and k value

    // Print each value in the values array
    for (unsigned long long int i = 0; i < h->kvalue; i++)
    {
        printf("%llu, ", h->values[i]);
    }

    printf("\b\b ]"); // Remove the last comma and space
}

// Frees the memory allocated for the given hash structure
void mads_uni_hash_free(mads_uni_hash_t *h)
{
    assert(h != NULL); // Ensure the hash structure is not NULL

    h->kvalue = 0; // Reset the k value
    h->tabsize = 0; // Reset the table size

    free(h->values); // Free the memory allocated for the values array
    h->values = NULL; // Set values to NULL

    free(h); // Free the memory allocated for the hash structure
    h = NULL; // Set the pointer to NULL
}