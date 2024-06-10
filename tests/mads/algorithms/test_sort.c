// ReSharper disable CppUnusedIncludeDirective
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include <mads/algorithms/sort.h>

static void test_mads_bubble_sort(void **state)
{
    // TODO: write unit tests for bubble sort algorithm.
}


int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_mads_bubble_sort),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}