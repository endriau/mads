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
#include <mads/data_structures/hash_table.h>


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

static unsigned long long int hash_string(const mads_uni_hash_t *uni_hash, const void *data)
{
    unsigned long long int max_k;
    unsigned long long int tab_size;
    unsigned long long int k = 0;
    unsigned long long int hval = 0;
    const char *string_key = (char *)data;

    tab_size = mads_uni_hash_get_table_size(uni_hash);
    max_k = mads_uni_hash_get_k(uni_hash);

    for (unsigned long long int i = 0; string_key[i] != '\0'; i++)
    {
        hval += string_key[i] * uni_hash->values[k]; k++;
        if (k == max_k) { k = 0; }
    }

    return hval % tab_size;
}

static void mads_hash_table_test_create(void **state)
{
    mads_init_genrand64(time(NULL));

    mads_hash_table_t *hash_table = NULL;
    hash_table = mads_hash_table_create(hash_string, MADS_HASH_TABLE_CHAIN_LIST);

    for (int i = 0; i < 10000; i++)
    {
        char *name_string = generate_random_string();
        unsigned long long int age = mads_genrand64_int64() % 100;

        if (!mads_hash_table_lookup(hash_table, (void *)name_string))
        {
            mads_cue_t *name_cue = mads_cue_create(name_string, strings_comparator, strings_printer, strings_destructor);
            mads_value_t *age_value = mads_value_create(*(void **)&age, integers_comparator, integers_printer, NULL);
            mads_pair_t *name_age_pair = mads_pair_create(name_cue, age_value);

            mads_hash_table_insert(hash_table, name_age_pair);
        }
        else
        {
            mads_hash_table_change_value(hash_table, (void *)name_string, *(void **)&age);
            free(name_string);
        }
    }

    mads_hash_table_print(hash_table);
    mads_hash_table_free(hash_table);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(mads_hash_table_test_create),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
