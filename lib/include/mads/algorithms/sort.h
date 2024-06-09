//
// Created by p0int3r on 6/12/21.
//

#ifndef MADS_ALGORITHMS_SORT_H
#define MADS_ALGORITHMS_SORT_H


#define MADS_RECURSIVE_SORT 82
#define MADS_ITERATIVE_SORT 73

typedef int (*mads_sort_compare_fn)(const void *, const void *);

void mads_quick_sort(void **A, long long int n, mads_sort_compare_fn cmp, int type);
void mads_merge_sort(void **A, long long int n, mads_sort_compare_fn cmp, int type);
void mads_insertion_sort(void **A, long long int n, mads_sort_compare_fn cmp);
int mads_is_sorted(void **A, long long int n, mads_sort_compare_fn cmp);

#endif //MADS_ALGORITHMS_SORT_H
