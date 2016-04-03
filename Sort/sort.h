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
 * Using include guards to check if the
 * sort.h header file has been included
 * at least once.If it hasns't the compiler
 * copy-pastes everything into the file that
 * is including it.If the file on the other
 * hand has been included the compiler
 * skips the contents entirely.
 *
 */

#ifndef SORT_H
#define SORT_H





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




/*
 * Once everything has been copy-pasted by
 * the compiler and the macro SORT_H has
 * been defined, the sort.h header file 
 * will not be included more than once.
 *
 */

#endif