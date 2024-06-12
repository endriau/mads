#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include <mads/data_structures/array.h>

static int integers_comparator(const void *i, const void *j)
{
    const long long int *ii = (long long int *)&i;
    const long long int *jj = (long long int *)&j;

    if (*ii > *jj) { return 1.0; }
    if (*ii < *jj) { return -1.0; }
    return 0.0;
}

static int reals_comparator(const void *x, const void *y)
{
    const double *xx = (double *)&x;
    const double *yy = (double *)&y;

    if (*xx > *yy) { return 1.0; }
    if (*xx < *yy) { return -1.0; }
    return 0.0;
}

static void reals_printer(const void *x)
{
    const double *xx = (double *)&x;
    printf("%lf", *xx);
}

static void integers_printer(const void *x)
{
    const long long int *xx = (long long int *)&x;
    printf("%lld", *xx);
}

static void mads_array_create_test(void **state)
{
    mads_array_t *integers_array = NULL;
    mads_array_t *reals_array = NULL;

    integers_array = mads_array_create(integers_comparator, integers_printer, NULL);
    assert_true(integers_array != NULL);

    reals_array = mads_array_create(reals_comparator, reals_printer, NULL);
    assert_true(reals_array != NULL);

    for (long long int i = 0; i < 10; i++)
    {
        double d = i;
        mads_array_append(integers_array, *(void **)&i);
        mads_array_append(reals_array, *(void **)&d);
    }

    while (!mads_array_is_empty(integers_array))
    {
        mads_array_remove_at(integers_array, 0);
        mads_array_remove_at(reals_array, 0);
        mads_array_print(integers_array);
        mads_array_print(reals_array);
    }

    mads_array_free(integers_array);
    mads_array_free(reals_array);
}

static void mads_array_free_test(void **state)
{
    // TODO: Test array_t destructor.
}


int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(mads_array_create_test),
        cmocka_unit_test(mads_array_free_test)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}