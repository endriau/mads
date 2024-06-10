// ReSharper disable CppDFANullDereference
// ReSharper disable CppDFAUnusedValue
// ReSharper disable CppDeclaratorNeverUsed


/**
 * \file sort.c
 *
 * This source file contains several sorting algorithms implemented in C language.
 *
 * \section sorting_algorithms Sorting Algorithms
 *
 * The sorting algorithms implemented in this source file include Quick Sort, Merge Sort, Insertion Sort,
 * and a function to check if an array is sorted. Both recursive and iterative versions of Quick Sort and
 * Merge Sort are included.
 *
 * The Quick Sort algorithm is implemented in the functions quick_sort_recursive() &
 * quick_sort_iterative(). It works by selecting a 'pivot' element and partitioning the array into two halves.
 * The left side contains elements less than the pivot and the right side contains elements greater than the pivot.
 * It recursively applies the same logic to the left and right side.
 *
 * The Merge Sort algorithm is implemented in the functions merge_sort_recursive() &
 * merge_sort_iterative(). It works by dividing an array into roughly two equal halves, sorts them separately
 * and then merges them.
 *
 * One of the simplest sorting algorithms, Insertion Sort, is implemented in mads_insertion_sort().
 * Being an in-place comparison-based algorithm makes this one useful for small data sets or arrays that are already
 * partially sorted.
 *
 * The mads_is_sorted() function checks if an array is sorted according to a given comparator function.
 *
 * \section utility_functions Utility Functions
 *
 * Also included are utility functions to support the implementation of these sorting algorithms:
 * compare_indices(), print_index(), swap(), partition(), and merge().
 */

#include <stdlib.h>
#include <assert.h>

#include <mads/algorithms/random.h>
#include <mads/algorithms/sort.h>

#include <mads/data_structures/stack.h>


// Here we are defining a utility function to compare two indices. However, as the message specifies, we will not be
// performing any actual comparisons; so, this function just returns 0 in all cases.
static int compare_indices(const void *i0, const void *i1)
{
    // Always returning 0, no real comparison is made here.
    return 0;
}

// This is a utility function that, ideally, would print an index. However, as mentioned in the comment,
// we will not be doing any printing here, so it is left empty.
static void print_index(const void *i)
{
    // No printing is done in this function
}

// This function swaps the elements at positions i and j in the array A. It can be used in various sorting
// algorithms where such operations are common.
static void swap(void **A, const long long int i, const long long int j)
{
    void *temp = NULL;

    // Ensure the array is not null and the indices are valid.
    assert(A != NULL && i >= 0 && j >= 0);

    // Swapping process
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    temp = NULL;
}

// This function partitions an array around a pivot element. It categories all elements smaller than the pivot to
// its left, and all elements larger than the pivot to its right. This is a critical part of the quick sort algorithm.
static void partition(void **A, const long long int n, const void *pivot,
    long long int *first_eq, long long int *first_gt, const mads_sort_compare_fn cmp)
{
    long long int next = 0, fe = 0, fg = n, outcome = 0;

    // Ensure input parameters are valid
    assert(A != NULL && cmp != NULL);

    // The partition process
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

    // Post condition also checked
    assert(fe >= 0 && fe < fg && fg <= n);
    *first_eq = fe;
    *first_gt = fg;
}

// This is an implementation of quick sort algorithm using recursion.
static void quick_sort_recursive(void **A, const long long int n, const mads_sort_compare_fn cmp)
{
    long long int first_eq, first_gt;
    if (n <= 1) { return; } // Base case of recursion

    // Partition the array around a randomly chosen pivot
    partition(A, n, A[mads_genrand64_int63() % n], &first_eq, &first_gt, cmp);

    // Recursive sort of the two partitions
    quick_sort_recursive(A, first_eq, cmp);
    quick_sort_recursive(A + first_gt, n - first_gt, cmp);
}

// An alternative implementation of quick sort algorithm. This version uses an iterative approach with a stack
// to avoid recursion. It's functionally equivalent to the recursive version but may have different performance
// characteristics.
static void quick_sort_iterative(void **A, const long long int n, const mads_sort_compare_fn cmp)
{
    // A stack is used to replace the call stack used in the recursive approach
    stack_t *stack = NULL;
    long long int first_eq, first_gt;
    long long int left = 0, right = n - 1;

    // Precondition checks
    assert(A != NULL && cmp != NULL && n >= 0);

    // Creating the stack and initializing it
    stack = stack_create(compare_indices, print_index, NULL);
    stack_push(stack, (void *)left);
    stack_push(stack, (void *)right);

    // while loop stands in for the recursion in the recursive quick sort
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
                stack_push(stack, (void *)left);
                stack_push(stack, (void *)(left + first_eq - 1));
            }
            if (first_gt < new_n)
            {
                stack_push(stack, (void *)(left + first_gt));
                stack_push(stack, (void *)right);
            }
        }
    }

    // proper cleanup
    stack_free(stack);
}

// Merge function used in merge sort algorithm. This function will merge two subsequent sorted segments of an array into
// a single sorted segment.
static void merge(void **A, void **T, const long long int mid, const long long int n, const mads_sort_compare_fn cmp)
{
    long long int i, s1 = 0, s2 = mid;

    // Input validity checks
    assert(A != NULL && T != NULL && cmp != NULL);
    assert(n >= 0 && mid >= 0);

    for (i = 0; i < mid; i++)
    {
        T[i] = A[i]; // Copy first half to temp array
    }

    i = 0;
    while (s1 < mid && s2 < n) // Merge two halves back into A
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

    while (s1 < mid) // Copy remaining elements of first half, if any
    {
        A[i] = T[s1];
        i++;
        s1++;
    }
}

// Recursive implementation of merge sort
static void merge_sort_recursive(void **A, void **T, const long long int n, const mads_sort_compare_fn cmp)
{
    if (n <= 1) { return; } // Base case, if the size is 1 or less, do nothing
    const long long int middle = n / 2; // Finding the middle of array
    merge_sort_recursive(A, T, middle, cmp); // Recursively sorting first half
    merge_sort_recursive(A + middle, T, n - middle, cmp); // Recursively sorting second half
    merge(A, T, middle, n, cmp); // Merge the two sorted halves
}

// Iterative implementation of merge sort
static void merge_sort_iterative(void **A, void **T, const long long int n, const mads_sort_compare_fn cmp)
{
    long long int left = 0, right = n - 1;
    stack_t *stack = NULL, *calls = NULL;
    const long long int type_call = 99;

    // Precondition checks
    assert(A != NULL && T != NULL);
    assert(n >= 0 && cmp != NULL);

    // Stack creation and initial push of elements
    stack = stack_create(compare_indices, print_index, NULL);
    calls = stack_create(compare_indices, print_index, NULL);
    stack_push(stack, (void *)left);
    stack_push(stack, (void *)right);
    stack_push(calls, (void *)type_call);

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
                stack_push(stack, (void *)left);
                stack_push(stack, (void *)right);
                stack_push(calls, (void *)type_merge);
                stack_push(stack, (void *)left);
                stack_push(stack, (void *)(mid + 1));
                stack_push(calls, (void *)type_call);
                stack_push(stack, (void *)(mid + 1));
                stack_push(stack, (void *)right);
                stack_push(calls, (void *)type_call);
            }
        }
        else
        {
            merge(A + left, T, mid - left + 1, right - left + 1, cmp);
        }
    }

    // Destroy stacks
    stack_free(stack);
    stack_free(calls);
}

// Main function to perform merge sort algorithm
void mads_merge_sort(void **A, const long long int n, const mads_sort_compare_fn cmp, const int type)
{
    void **T = NULL;

    // Input validation checks
    assert(type == MADS_SORT_RECURSIVE || type == MADS_SORT_ITERATIVE);
    assert(A != NULL && n >= 0 && cmp != NULL);
    T = (void **)malloc((1 + n / 2) * sizeof(void *));
    assert(T != NULL);

    // Perform merge sort according to the specified type
    if (type == MADS_SORT_RECURSIVE) { merge_sort_recursive(A, T, n, cmp); }
    if (type == MADS_SORT_ITERATIVE) { merge_sort_iterative(A, T, n, cmp); }

    // De-allocate temporary merge array
    free(T);
    T = NULL;
}

// This function implements the insertion sort algorithm. It's a simple, stable sorting algorithm that works well
// for small inputs or inputs that are already partially sorted.
void mads_insertion_sort(void **A, const long long int n, const mads_sort_compare_fn cmp)
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

// This function checks if the array A of length n is sorted according to the comparator cmp.
int mads_is_sorted(void **A, const long long int n, const mads_sort_compare_fn cmp)
{
    long long int i = 0;
    int flag = 0;

    // Check input validity
    assert(A != NULL && n >= 0 && cmp != NULL);

    // Iterate through array and compare adjacent elements
    for (i = 1; i < n; i++)
    {
        if (cmp(A[i - 1], A[i]) <= 0) // If the previous element is smaller than or equal to the current
        {
            flag = 1; // set flag to 1
        }
        else // As soon as previous element greater than current is found, array isn't sorted and flag is set to 0
        {
            flag = 0;
            return flag;
        }
    }

    // Return the result of whether the array is sorted or not
    return flag;
}
