//
// Created by p0int3r on 6/12/21.
//

#ifndef TINYLIB_SORT_H
#define TINYLIB_SORT_H


#define RECURSIVE_SORT 82
#define ITERATIVE_SORT 73

typedef int (*sort_compare_fn)(const void *, const void *);


void quick_sort(void **A, long long int n, sort_compare_fn cmp, int type);
void merge_sort(void **A, long long int n, sort_compare_fn cmp, int type);
void insertion_sort(void **A, long long int n, sort_compare_fn cmp);
int is_sorted(void **A, long long int n, sort_compare_fn cmp);

#endif //TINYLIB_SORT_H
