// ReSharper disable CppDFANullDereference
// ReSharper disable CppDFAUnusedValue


#include <stdlib.h>
#include <assert.h>

#include <mads/algorithms/random.h>
#include <mads/algorithms/sort.h>

#include <mads/data_structures/stack.h>


static int compare_indices(const void* i0, const void* i1)
{
    //NOTE:
    // Not required since we will not be looking
    // into the stack data structure as it is needed
    // only for insertions and pop outs.
    return 0;
}


static void print_index(const void* i)
{
    //NOTE:
    // Not required since we will not be printing
    // the elements of the stack data structure.
}


static void swap(void** A, const long long int i, const long long int j)
{
    void* temp = NULL;
    assert(A != NULL && i >= 0 && j >= 0);
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    temp = NULL;
}


static void partition(void** A, const long long int n, const void* pivot,
                      long long int* first_eq, long long int* first_gt, const mads_sort_compare_fn cmp)
{
    long long int next = 0, fe = 0, fg = n, outcome = 0;
    assert(A != NULL && cmp != NULL);

    while (next < fg)
    {
        outcome = cmp(A[next], pivot);

        if (outcome < 0)
        {
            swap(A, fe, next);
            fe++;
            next++;
        }
        else if (outcome > 0)
        {
            fg--;
            swap(A, fg, next);
        }
        else
        {
            next++;
        }
    }

    assert(fe >= 0 && fe < fg && fg <= n);
    *first_eq = fe;
    *first_gt = fg;
}


static void quick_sort_recursive(void** A, const long long int n, const mads_sort_compare_fn cmp)
{
    long long int first_eq, first_gt;
    if (n <= 1) { return; }
    partition(A, n, A[mads_genrand64_int63() % n], &first_eq, &first_gt, cmp);
    quick_sort_recursive(A, first_eq, cmp);
    quick_sort_recursive(A + first_gt, n - first_gt, cmp);
}


static void quick_sort_iterative(void** A, const long long int n, const mads_sort_compare_fn cmp)
{
    stack_t* stack = NULL;
    long long int first_eq, first_gt;
    long long int left = 0, right = n - 1;
    assert(A != NULL && cmp != NULL && n >= 0);
    stack = stack_create(compare_indices, print_index, NULL);
    stack_push(stack, (void*)left);
    stack_push(stack, (void*)right);

    while (!stack_is_empty(stack))
    {
        right = (long long int)stack_pop(stack);
        left = (long long int)stack_pop(stack);

        if ((right - left) > 0)
        {
            const long long int new_n = (right - left) + 1;
            const long long int random_index = left + mads_genrand64_int63() % new_n;
            partition(A + left, new_n, A[random_index],
                      &first_eq, &first_gt, cmp);

            if (first_eq > 1)
            {
                stack_push(stack, (void*)left);
                stack_push(stack, (void*)(left + first_eq - 1));
            }

            if (first_gt < new_n)
            {
                stack_push(stack, (void*)(left + first_gt));
                stack_push(stack, (void*)right);
            }
        }
    }

    stack_free(stack);
}


void mads_quick_sort(void** A, const long long int n, const mads_sort_compare_fn cmp, const int type)
{
    assert(A != NULL && n >= 0 && cmp != NULL);
    assert(type == MADS_RECURSIVE_SORT || type == MADS_ITERATIVE_SORT);
    if (type == MADS_RECURSIVE_SORT) { quick_sort_recursive(A, n, cmp); }
    if (type == MADS_ITERATIVE_SORT) { quick_sort_iterative(A, n, cmp); }
}


static void merge(void** A, void** T, const long long int mid, const long long int n, const mads_sort_compare_fn cmp)
{
    long long int i, s1 = 0, s2 = mid;
    assert(A != NULL && T != NULL && cmp != NULL);
    assert(n >= 0 && mid >= 0);

    for (i = 0; i < mid; i++)
    {
        T[i] = A[i];
    }

    i = 0;

    while (s1 < mid && s2 < n)
    {
        const long long int outcome = cmp(T[s1], A[s2]);

        if (outcome < 0)
        {
            A[i] = T[s1];
            s1++;
        }
        else
        {
            A[i] = A[s2];
            s2++;
        }

        i++;
    }

    while (s1 < mid)
    {
        A[i] = T[s1];
        i++;
        s1++;
    }
}


static void merge_sort_recursive(void** A, void** T, const long long int n, const mads_sort_compare_fn cmp)
{
    if (n <= 1) { return; }
    const long long int middle = n / 2;
    merge_sort_recursive(A, T, middle, cmp);
    merge_sort_recursive(A + middle, T, n - middle, cmp);
    merge(A, T, middle, n, cmp);
}


static void merge_sort_iterative(void** A, void** T, const long long int n, const mads_sort_compare_fn cmp)
{
    long long int left = 0, right = n - 1;
    stack_t *stack = NULL, *calls = NULL;
    const long long int type_call = 99;
    assert(A != NULL && T != NULL);
    assert(n >= 0 && cmp != NULL);
    stack = stack_create(compare_indices, print_index, NULL);
    calls = stack_create(compare_indices, print_index, NULL);
    stack_push(stack, (void*)left);
    stack_push(stack, (void*)right);
    stack_push(calls, (void*)type_call);

    while (!stack_is_empty(stack))
    {
        right = (long long int)stack_pop(stack);
        left = (long long int)stack_pop(stack);
        const long long int type = (long long int)stack_pop(calls);
        const long long int mid = (right + left) / 2;

        if (type == type_call)
        {
            if ((right - left) > 0)
            {
                const long long int type_merge = 109;
                stack_push(stack, (void*)left);
                stack_push(stack, (void*)right);
                stack_push(calls, (void*)type_merge);
                stack_push(stack, (void*)left);
                stack_push(stack, (void*)mid);
                stack_push(calls, (void*)type_call);
                stack_push(stack, (void*)(mid + 1));
                stack_push(stack, (void*)right);
                stack_push(calls, (void*)type_call);
            }
        }
        else
        {
            merge(A + left, T, mid - left + 1, right - left + 1, cmp);
        }
    }

    stack_free(stack);
    stack_free(calls);
}


void mads_merge_sort(void** A, const long long int n, const mads_sort_compare_fn cmp, const int type)
{
    void** T = NULL;
    assert(type == MADS_RECURSIVE_SORT || type == MADS_ITERATIVE_SORT);
    assert(A != NULL && n >= 0 && cmp != NULL);
    T = (void**)malloc((1 + n / 2) * sizeof(void*));
    assert(T != NULL);
    if (type == MADS_RECURSIVE_SORT) { merge_sort_recursive(A, T, n, cmp); }
    if (type == MADS_ITERATIVE_SORT) { merge_sort_iterative(A, T, n, cmp); }
    free(T);
    T = NULL;
}


void mads_insertion_sort(void** A, const long long int n, const mads_sort_compare_fn cmp)
{
    assert(A != NULL && n >= 0 && cmp != NULL);

    for (long long int i = 1; i < n; i++)
    {
        for (long long int j = i - 1; j >= 0 && cmp(A[j], A[j + 1]) > 0; j--)
        {
            swap(A, j, j + 1);
        }
    }
}


int mads_is_sorted(void** A, const long long int n, const mads_sort_compare_fn cmp)
{
    long long int i = 0;
    int flag = 0;
    assert(A != NULL && n >= 0 && cmp != NULL);

    for (i = 1; i < n; i++)
    {
        if (cmp(A[i - 1], A[i]) <= 0)
        {
            flag = 1;
            continue;
        }
        else
        {
            flag = 0;
            return flag;
        }
    }

    return flag;
}
