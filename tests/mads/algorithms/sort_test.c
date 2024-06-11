// ReSharper disable CppUnusedIncludeDirective
// ReSharper disable CppDFANullDereference
// ReSharper disable CppDFAMemoryLeak
// ReSharper disable CppDeclaratorNeverUsed
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmocka.h>
#include <string.h>

#include <mads/algorithms/random.h>
#include <mads/algorithms/sort.h>


static char *generate_random_string()
{
    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t string_length = mads_genrand64_int64() % 100;

    char *random_string = malloc(sizeof(char) * (string_length + 1));
    assert(random_string != NULL);

    mads_init_genrand64(time(NULL));

    for (size_t i = 0; i < string_length; i++)
    {
        random_string[i] = characters[mads_genrand64_int64() %(sizeof(characters) - 1)];
    }

    random_string[string_length] = '\0';
    return random_string;
}

static int strings_comparator(const void *s, const void *l)
{
    const char *ss = (char *)s;
    const char *ll = (char *)l;
    return strcmp(ss, ll);
}

static int reals_comparator(const void *x, const void *y)
{
    const double *xx = (double *)&x;
    const double *yy = (double *)&y;

    if (*xx > *yy) { return 1.0; }
    if (*xx < *yy) { return -1.0; }
    return 0.0;
}

static int integers_comparator(const void *i, const void *j)
{
    const long long int *ii = (long long int *)&i;
    const long long int *jj = (long long int *)&j;

    if (*ii > *jj) { return 1.0; }
    if (*ii < *jj) { return -1.0; }
    return 0.0;
}


static void mads_insertion_sort_test(void **state)
{
    // Array size, you can modify to test with larger arrays.
    const size_t array_size = 10;

    // Allocating an array of integers, each memory block of size 8 bytes.
    long long int *integers_block = malloc(sizeof(long long int) * array_size);

    // Make sure memory was allocated successfully.
    assert_true(integers_block != NULL);

    // Initialize random generator with seed.
    mads_init_genrand64(time(NULL));

    // Iterate over the integers array and populate it
    // with randomly generated integers.
    for (int i = 0; i < array_size; i++)
    {
        const long long int random_integer = mads_genrand64_int64() % 1000;
        integers_block[i] = random_integer;
    }


    // Make sure the array is not sorted.
    assert_false(mads_is_sorted((void **)integers_block, array_size, integers_comparator));

    // Sort using Insertion Sort algorithm.
    mads_insertion_sort((void **)integers_block, array_size, integers_comparator);

    // Check to see if the array is correctly sorted after calling insertion sort.
    assert_true(mads_is_sorted((void **)integers_block, array_size, integers_comparator));

    // free memory for integers array.
    free(integers_block);
}


static void mads_quick_sort_test(void **state)
{
    // Array size, you can modify to test with larger arrays.
    const size_t array_size = 100;

    // Allocating two arrays of doubles.
    double *reals_rblock = malloc(sizeof(double) * array_size);
    double *reals_iblock = malloc(sizeof(double) * array_size);

    // Make sure memory was allocated successfully.
    assert_true(reals_rblock != NULL);
    assert_true(reals_iblock != NULL);

    // initialize random generator with seed.
    mads_init_genrand64(time(NULL));

    // Iterate over the doubles arrays and populate them
    // with randomly generated doubles.
    for (int i = 0; i < array_size; i++)
    {
        const double random_real = mads_genrand64_real3();
        reals_rblock[i] = random_real;
        reals_iblock[i] = random_real;
    }

    // Make sure the arrays are not sorted.
    assert_false(mads_is_sorted((void **)reals_rblock, array_size, reals_comparator));
    assert_false(mads_is_sorted((void **)reals_iblock, array_size, reals_comparator));

    // Sort first array using recursive quick sort.
    mads_quick_sort((void **)reals_rblock, array_size, reals_comparator, MADS_SORT_RECURSIVE);

    // Sort second array using iterative quick sort.
    mads_quick_sort((void **)reals_iblock, array_size, reals_comparator, MADS_SORT_ITERATIVE);

    // Check to see if the arrays are correctly sorted after calling quick sort.
    assert_true(mads_is_sorted((void **)reals_rblock, array_size, reals_comparator));
    assert_true(mads_is_sorted((void **)reals_iblock, array_size, reals_comparator));

    // Check if each element of the first array matches with the seocnd.
    for (int i = 0; i < array_size; i++)
    {
        assert_float_equal(reals_rblock[i], reals_iblock[i], 1e-5);
    }

    // Free memory for the arrays.
    free(reals_rblock);
    free(reals_iblock);
}


static void mads_merge_sort_test(void **state)
{
    // Array size, you can modify to test with larger arrays.
    const size_t array_size = 10;

    // Allocating two arrays of strings.
    void **strings_iblock = malloc(sizeof(void *) * array_size);
    void **strings_rblock = malloc(sizeof(void *) * array_size);

    // Make sure memory was allocate successfully.
    assert_true(strings_iblock != NULL);
    assert_true(strings_rblock != NULL);

    // Iterate over the strings array and populate them
    // with randomly generated strings.
    for (int  i = 0; i < array_size; i++)
    {
        char *random_string = generate_random_string();
        strings_iblock[i] = (void *)random_string;
        strings_rblock[i] = (void *)random_string;
    }

    // Make sure the arrays are not sorted.
    assert_false(mads_is_sorted(strings_iblock, array_size, strings_comparator));
    assert_false(mads_is_sorted(strings_rblock, array_size, strings_comparator));

    // Sort first string array using iterative merge sort.
    mads_merge_sort(strings_iblock, array_size, strings_comparator, MADS_SORT_ITERATIVE);

    // Sort second string array using recursive merge sort.
    mads_merge_sort(strings_rblock, array_size, strings_comparator, MADS_SORT_RECURSIVE);

    // Check to see if the arrays are correctly sorted after calling merge sort.
    assert_true(mads_is_sorted(strings_iblock, array_size, strings_comparator));
    assert_true(mads_is_sorted(strings_rblock, array_size, strings_comparator));

    // Check if each element of the first array matches with the second.
    for (int i = 0; i < array_size; i++)
    {
        assert_string_equal((const char *)strings_iblock[i], (const char *)strings_rblock[i]);

        // Need only free from one array, given that the other one has
        // a reference of the string and not a copy.
        free(strings_iblock[i]);
    }

    // Free memory for the arrays.
    free(strings_iblock);
    free(strings_rblock);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(mads_insertion_sort_test),
        cmocka_unit_test(mads_quick_sort_test),
        cmocka_unit_test(mads_merge_sort_test)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
