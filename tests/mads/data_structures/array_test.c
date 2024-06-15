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



static char *generate_random_string(void)
{
    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t string_length = mads_genrand64_int64() % 10;

    char *random_string = malloc(sizeof(char) * (string_length + 1));
    assert(random_string != NULL);

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

static void strings_printer(const void *s)
{
    const char *ss = (char *)s;
    printf("%s", ss);
}

static void strings_destroyer(void *s)
{
    char *ss = (char *)s;
    free(ss); ss = NULL;
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
    char *random_string = NULL;

    integers_array = mads_array_create(integers_comparator, integers_printer, NULL);
    assert_true(integers_array != NULL);

    reals_array = mads_array_create(reals_comparator, reals_printer, NULL);
    assert_true(reals_array != NULL);

    strings_array = mads_array_create(strings_comparator, strings_printer, strings_destroyer);
    assert_true(strings_array != NULL);

    mads_init_genrand64(time(NULL));

    for (long long int i = 0; i < 10; i++)
    {
        double d = i;
        mads_array_append(integers_array, *(void **)&i);
        mads_array_append(reals_array, *(void **)&d);

        random_string = generate_random_string();
        mads_array_append(strings_array, random_string);
    }

    while (!mads_array_is_empty(integers_array))
    {
        mads_array_remove_at(integers_array, 0);
        mads_array_remove_at(reals_array, 0);
        mads_array_remove_at(strings_array, 0);
        // mads_array_print(integers_array);
        // mads_array_print(reals_array);
        // mads_array_print(strings_array);
    }

    mads_array_free(integers_array);
    mads_array_free(reals_array);
    mads_array_free(strings_array);
}

static void mads_array_free_test(void **state)
{
    // TODO: Test array_t destructor.
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