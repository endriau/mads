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

#include <mads/algorithms/random.h>
#include <mads/algorithms/sort.h>


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

    double *reals_rblock = malloc(sizeof(double) * array_size);
    double *reals_iblock = malloc(sizeof(double) * array_size);

    assert_true(reals_rblock != NULL);
    assert_true(reals_iblock != NULL);

    mads_init_genrand64(time(NULL));

    for (int i = 0; i < array_size; i++)
    {
        const double random_real = mads_genrand64_real3();
        reals_rblock[i] = random_real;
        reals_iblock[i] = random_real;
    }

    assert_false(mads_is_sorted((void **)reals_rblock, array_size, reals_comparator));
    assert_false(mads_is_sorted((void **)reals_iblock, array_size, reals_comparator));

    mads_quick_sort((void **)reals_rblock, array_size, reals_comparator, MADS_SORT_RECURSIVE);
    mads_quick_sort((void **)reals_iblock, array_size, reals_comparator, MADS_SORT_ITERATIVE);

    assert_true(mads_is_sorted((void **)reals_rblock, array_size, reals_comparator));
    assert_true(mads_is_sorted((void **)reals_iblock, array_size, reals_comparator));

    for (int i = 0; i < array_size; i++)
    {
        assert_float_equal(reals_rblock[i], reals_iblock[i], 1e-5);
    }
}


static void mads_merge_sort_test(void **state)
{
    // TODO: write some tests for merge sort algorithm.
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
