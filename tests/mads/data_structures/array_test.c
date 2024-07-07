// ReSharper disable CppDFAMemoryLeak
// ReSharper disable CppDFANullDereference

#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <cmocka.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include <mads/algorithms/random.h>
#include <mads/data_structures/array.h>


// static char *generate_random_string(void)
// {
//     char *random_string = NULL;
//     const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//     const size_t string_length = mads_genrand64_int64() % 10;
//
//     random_string = (char *)malloc(sizeof(char) * (string_length + 1));
//     assert(random_string != NULL);
//
//     for (size_t i = 0; i < string_length; i++)
//     {
//         random_string[i] = characters[mads_genrand64_int64() %(sizeof(characters) - 1)];
//     }
//
//     random_string[string_length] = '\0';
//     return random_string;
// }

static int strings_comparator(const void *s, const void *l)
{
    const char *ss = (char *)s;
    const char *ll = (char *)l;
    return strcmp(ss, ll);
}

static void strings_printer(const void *s)
{
    const char *ss = (char *)s;
    printf("%s", ss);
}

static void strings_destructor(void *s)
{
    char *ss = (char *)s;
    free(ss);
    ss = NULL;
}

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
    mads_array_t *strings_array = NULL;
    // char *random_string = NULL;

    integers_array = mads_array_create(integers_comparator, integers_printer, NULL);
    assert_true(integers_array != NULL);
    assert_ptr_equal(integers_array->comparator, integers_comparator);
    assert_ptr_equal(integers_array->printer, integers_printer);
    assert_ptr_equal(integers_array->destructor, NULL);
    assert_int_equal(integers_array->msize, 16);
    assert_int_equal(integers_array->index, -1);

    reals_array = mads_array_create(reals_comparator, reals_printer, NULL);
    assert_true(reals_array != NULL);
    assert_ptr_equal(reals_array->comparator, reals_comparator);
    assert_ptr_equal(reals_array->printer, reals_printer);
    assert_ptr_equal(reals_array->destructor, NULL);
    assert_int_equal(reals_array->msize, 16);
    assert_int_equal(reals_array->index, -1);

    strings_array = mads_array_create(strings_comparator, strings_printer, strings_destructor);
    assert_true(strings_array != NULL);
    assert_ptr_equal(strings_array->comparator, strings_comparator);
    assert_ptr_equal(strings_array->printer, strings_printer);
    assert_ptr_equal(strings_array->destructor, strings_destructor);
    assert_int_equal(strings_array->msize, 16);
    assert_int_equal(strings_array->index, -1);

    mads_array_free(&integers_array);
    mads_array_free(&reals_array);
    mads_array_free(&strings_array);
}


static void mads_array_free_test(void **state)
{
    mads_array_t *integers_array = NULL;
    mads_array_t *reals_array = NULL;
    mads_array_t *strings_array = NULL;

    integers_array = mads_array_create(integers_comparator, integers_printer, NULL);
    reals_array = mads_array_create(reals_comparator, reals_printer, NULL);
    strings_array = mads_array_create(strings_comparator, strings_printer, strings_destructor);

    mads_array_free(&integers_array);
    mads_array_free(&reals_array);
    mads_array_free(&strings_array);

    assert_null(integers_array);
    assert_null(reals_array);
    assert_null(strings_array);
}


int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(mads_array_create_test),
        cmocka_unit_test(mads_array_free_test)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
