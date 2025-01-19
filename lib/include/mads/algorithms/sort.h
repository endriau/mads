// ReSharper disable CppDoxygenUnresolvedReference

/**
 * @file sort.h
 * @brief Contains prototypes for different sorting algorithms i.e., QuickSort, MergeSort, and InsertionSort.
 * It also includes utility macros and a check function for array sorting validation.
 *
 * The sorting algorithms provide both iterative and recursive variants where applicable.
 * These algorithms operate on arrays of generic pointers and use a comparison function to determine the sorting order.
 * The caller must provide the actual comparison function.
 */


#ifndef MADS_ALGORITHMS_SORT_H
#define MADS_ALGORITHMS_SORT_H


#ifdef __cplusplus
extern "C" {
#endif


#include <mads_export.h>


/**
 * @def MADS_SORT_RECURSIVE
 * @brief A macro constant to specify the type of sorting as recursive.
 */
#define MADS_SORT_RECURSIVE 82


/**
 * @def MADS_SORT_ITERATIVE
 * @brief A macro constant to specify the type of sorting as iterative.
 */
#define MADS_SORT_ITERATIVE 73


/**
 * @brief A comparison function type for mads sorting algorithms.
 * @param[in] GenericPointer to the first object.
 * @param[in] GenericPointer to the second object.
 * @return An integer less than, equal to, or greater than zero if the first argument is
 * considered to be respectively less than, equal to, or greater than the second.
 */
typedef int (*mads_sort_compare_fn)(const void *, const void *);

/**
 * @brief An implementation of the QuickSort algorithm in the mads library.
 * @param[in,out] A Array of generic pointers to be sorted.
 * @param[in] n Size of the array.
 * @param[in] cmp A comparison function to determine the sorting order.
 * @param[in] type A constant representing the type of sorting (recursive or iterative).
 */
MADS_EXPORT void mads_quick_sort(void **A, long long int n, mads_sort_compare_fn cmp, int type);

/**
 * @brief An implementation of the MergeSort algorithm in the mads library.
 * @param[in,out] A Array of generic pointers to be sorted.
 * @param[in] n Size of the array.
 * @param[in] cmp A comparison function to determine the sorting order.
 * @param[in] type A constant representing the type of sorting (recursive or iterative).
 */
MADS_EXPORT void mads_merge_sort(void **A, long long int n, mads_sort_compare_fn cmp, int type);

/**
 * @brief An implementation of the InsertionSort algorithm in the mads library.
 * @param[in,out] A Array of generic pointers to be sorted.
 * @param[in] n Size of the array.
 * @param[in] cmp A comparison function to determine the sorting order.
 */
MADS_EXPORT void mads_insertion_sort(void **A, long long int n, mads_sort_compare_fn cmp);

/**
 * @brief Checks whether an array is sorted according to a comparison function.
 * @param[in] A Array of generic pointers.
 * @param[in] n Size of the array.
 * @param[in] cmp The comparison function that determines the sorting order.
 * @return Non-zero if the array is sorted, zero otherwise.
 */
MADS_EXPORT int mads_is_sorted(void **A, long long int n, mads_sort_compare_fn cmp);

#ifdef __cplusplus
}
#endif

#endif //MADS_ALGORITHMS_SORT_H
