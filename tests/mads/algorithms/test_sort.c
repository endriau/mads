// ReSharper disable CppUnusedIncludeDirective
// ReSharper disable CppDFANullDereference
// ReSharper disable CppDFAMemoryLeak
#include <assert.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mads/algorithms/sort.h>
#include <mads/algorithms/random.h>

static int compare_reals_fn(const void *x, const void *y)
{
    const double *xx = (double *)&x;
    const double *yy = (double *)&y;

    if (*xx > *yy) { return 1.0; }
    if (*xx < *yy) { return -1.0; }
    return 0.0;
}

static void test_mads_bubble_sort(void **state)
{
    long long int *mblocks = malloc(sizeof(long long int) * 10);
    assert(mblocks != NULL);

    mads_init_genrand64(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        const long long int random_value = mads_genrand64_int64() % 100;
        mblocks[i] = random_value;
    }

    mads_merge_sort((void **)mblocks, 10, compare_reals_fn, MADS_SORT_ITERATIVE);

    printf("\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%lld\n", mblocks[i]);
    }

}


int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_mads_bubble_sort),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}