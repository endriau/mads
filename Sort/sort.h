/*
 * This header file contains function prototyping
 * and data definitions for a collection of
 * polymorphic sorting functions.
 *
 * @author: Endri Kastrati
 * @date:   19/10/2015
 *
 */



/*
 * Defining a new datatype of a function pointer called
 * SortCompareFn that takes as arguments two immutable
 * addresses to void pointers.These function pointer enables
 * polymorphism by specifying an interface for the comparison
 * function.The comparison function has to be written by the
 * user and has to meet the following criteria.
 *
 */

typedef int     (*SortCompareFn)(const void *,const void *);





/*
 * Function prototyping of sorting procedures,
 * such as quick sort,merge sort,insertion sort
 * and so on.
 *
 */

void        quick_sort(void **A,int n,SortCompareFn cmp);
void        merge_sort(void **A,int n,SortCompareFn cmp);
void        insertion_sort(void **A,int n,SortCompareFn cmp);


