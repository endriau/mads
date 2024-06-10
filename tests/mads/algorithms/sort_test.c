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
    // TODO: write some tests for insertion sort algorithm.
}


static void mads_quick_sort_test(void **state)
{
    // TODO: write some tests for quick sort algorithm.
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