// ReSharper disable CppDFAMemoryLeak
// ReSharper disable CppDFANullDereference
// ReSharper disable CppRedundantCastExpression
// ReSharper disable CppJoinDeclarationAndAssignment
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


static char *generate_random_string(void)
{
    char *random_string = NULL;
    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t string_length = mads_genrand64_int64() % 10;

    random_string = (char *)malloc(sizeof(char) * (string_length + 1));
    assert(random_string != NULL);

    for (size_t i = 0; i < string_length; i++)
    {
        random_string[i] = characters[mads_genrand64_int64() % (sizeof(characters) - 1)];
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

    integers_array = mads_array_create(integers_comparator, integers_printer, NULL);
    assert_non_null(integers_array);
    assert_ptr_equal(integers_array->comparator, integers_comparator);
    assert_ptr_equal(integers_array->printer, integers_printer);
    assert_null(integers_array->destructor);
    assert_int_equal(integers_array->msize, 16);
    assert_int_equal(integers_array->index, -1);

    reals_array = mads_array_create(reals_comparator, reals_printer, NULL);
    assert_non_null(reals_array);
    assert_ptr_equal(reals_array->comparator, reals_comparator);
    assert_ptr_equal(reals_array->printer, reals_printer);
    assert_null(reals_array->destructor);
    assert_int_equal(reals_array->msize, 16);
    assert_int_equal(reals_array->index, -1);

    strings_array = mads_array_create(strings_comparator, strings_printer, strings_destructor);
    assert_non_null(strings_array);
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

static void mads_array_operations_test(void **state)
{
    mads_array_t *integers_array = NULL;
    mads_array_t *reals_array = NULL;
    mads_array_t *strings_array = NULL;
    char *random_string = NULL;
    void *temp_data = NULL;
    long long int last_index;

    integers_array = mads_array_create(integers_comparator, integers_printer, NULL);
    reals_array = mads_array_create(reals_comparator, reals_printer, NULL);
    strings_array = mads_array_create(strings_comparator, strings_printer, strings_destructor);

    for (long long int i = 0; i < 10; i++)
    {
        long long int integer_number = mads_genrand64_int64() % 100;
        mads_array_append(integers_array, *(void **)&integer_number);
        last_index = mads_array_size(integers_array) - 1;
        temp_data = mads_array_get_at(integers_array, last_index);
        assert_int_equal(integer_number, *(long long int *)&temp_data);
    }

    for (long long int i = 0; i < 10; i++)
    {
        double real_number = mads_genrand64_real3();
        mads_array_prepend(reals_array, *(void **)&real_number);
        temp_data = mads_array_get_at(reals_array, 0);
        assert_float_equal(real_number, *(double *)&temp_data, 0.001);
    }

    for (long long int i = 0; i < 10; i++)
    {
        random_string = generate_random_string();
        mads_array_insert_at(strings_array, i, (void *)random_string);
        temp_data = mads_array_get_at(strings_array, i);
        assert_string_equal(random_string, (char *)temp_data);
    }

    mads_array_free(&integers_array);
    mads_array_free(&reals_array);
    mads_array_free(&strings_array);
}


int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(mads_array_create_test),
        cmocka_unit_test(mads_array_free_test),
        cmocka_unit_test(mads_array_operations_test)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
