#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include <mads/algorithms/sort.h>

static void test_sort_create(void **state)
{
    assert_int_equal(2, 2);
}


int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_sort_create),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}