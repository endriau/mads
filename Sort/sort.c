/*
 * This file contains definitions for operations
 * regarding sorting algorithms such as quicksort,
 * mergesort and insertion sort.It also contains
 * private functions that are invokable only from
 * functions defined in this file.
 *
 * @author: Endri Kastrati
 * @date:   19/10/2015
 *
 */




/*
 * Including the standard utilities library,
 * the standard assertion library and
 * the header file sort.h which contains
 * datatype definitions and function prototypings.
 *
 */

#include <stdlib.h>
#include <assert.h>
#include "sort.h"




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function swap() takes an array
 * of void pointers and two numeric values 
 * i,j representing indices and swaps the
 * the address at i with the address at j.
 *
 * @param:  void     **A
 * @param:  int      i
 * @param:  int      j
 * @return: void
 *
 */

static void swap(void **A,int i,int j)
{
    void *temp=NULL;
    assert(A!=NULL && i>=0 && j>=0);
    temp=A[i];
    A[i]=A[j];
    A[j]=temp;
    temp=NULL;
    return;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The static function partition() takes an array of void pointers,
 * it's length,a pivot element between [0,n),two int pointers which will
 * be assigned the indices of the first equal and the first greater respectively
 * when the partition has finished and a function pointer of type SortCompareFn.
 * The partitioning process moves elements greater than the pivot to the right
 * of the pivot and elements less than the pivot to the left of the pivot.
 * It also keeps track of equal items thus not including then in the partitioning.
 * 
 * @param:  void            **A
 * @param:  int             n
 * @param:  void            *pivot
 * @param:  int             *first_eq
 * @param:  int             *first_gt
 * @param:  SortCompareFn   cmp
 * @return: void
 *
 */

static void partition(void **A,int n,void *pivot,int *first_eq,int *first_gt,SortCompareFn cmp)
{
    int next=0,fe=0,fg=n,outcome=0;
    assert(A!=NULL && cmp!=NULL);
    
    while (next<fg)
    {
        outcome=cmp(A[next],pivot);

        if (outcome<0)
        {
            swap(A,fe,next);
            fe++;
            next++;
        }
        else if (outcome>0)
        {
            fg--;
            swap(A,fg,next);
        }
        else
        {
            next++;
        }
    }

    assert(fe>=0 && fe<fg && fg<=n);
    *first_eq=fe;
    *first_gt=fg;
    return;
}




/*
 * @COMPLEXITY: Best O(nlogn), Worst O(n^2)
 *
 * The static function quick_sort_recursive() is the recursive
 * implementaiton of the quick sort Algorithm in C.It has a base
 * case to end recursion.It partitions an array into two subarrays
 * based on a randomly selected pivot and calls quick_sort_recursive()
 * on those two subarrays respectively and so on.
 *
 * @param:  void             **A
 * @param:  int              n
 * @param:  SortCompareFn    cmp
 * @return: void
 *
 */

static void quick_sort_recursive(void **A,int n,SortCompareFn cmp)
{
    int first_eq,first_gt;

    if (n<=1)
    {
        return;
    }

    partition(A,n,A[rand()%n],&first_eq,&first_gt,cmp);
    quick_sort_recursive(A,first_eq,cmp);
    quick_sort_recursive(A+first_gt,n-first_gt,cmp);
    return;
}




/*
 * @COMPLEXITY: Best O(nlogn), Worst O(n^2)
 *
 * The function quick_sort() is the calling interface
 * for the recursive implementation of quick sort algorithm.
 * Checks if the given arguments are valid, if so proceeds,
 * otherwise terminates execution based on failed assertion.
 *
 * @param:   void           **A
 * @param:   int            n
 * @param:   SortCompareFn  cmp
 * @return:  void
 */

void quick_sort(void **A,int n,SortCompareFn cmp)
{
    assert(A!=NULL && n>=0 && cmp!=NULL);
    quick_sort_recursive(A,n,cmp);
    return;
}






/*
 * @COMPLEXITY: O(n)
 *
 * The static function merge() takes as arguments two arrays A,T of void pointers,
 * the middle,the length of array A and a comparison function.
 * To merge, the first of the two regions of A ( from 0 .. mid-1 ) is copied into 
 * the temporary array T.Elements are peeled off the front of the temporary array T
 * and the front of the second segment of the array A ( mid .. n-1 ) in sorted order
 * filling up A again, starting at A[0].Once either of the segments is exhausted the
 * remaining elements from T are copied into the last vacant locations in A.If T
 * is exhausted first, the remaining items in the second segment in A are already
 * in their correct locations, and no further action is required.
 *
 * @param:   void           **A
 * @param:   void           **T
 * @param:   int            mid
 * @param:   int            n
 * @param:   SortCompareFn  cmp
 * @return:  void
 *
 */

static void merge(void **A,void **T,int mid,int n,SortCompareFn cmp)
{
    int i,s1=0,s2=mid,outcome;
    assert(A!=NULL && T!=NULL && cmp!=NULL);
    assert(n>=0 && mid>=0);

    for (i=0;i<mid;i++)
    {
        T[i]=A[i];
    }

    i=0;

    while (s1<mid && s2<n)
    {
        outcome=cmp(T[s1],A[s2]);

        if (outcome<0)
        {
            A[i]=T[s1];
            s1++;
        }
        else
        {
            A[i]=A[s2];
            s2++;
        }

        i++;
    }
    
    while (s1<mid)
    {
        A[i]=T[s1];
        i++;
        s1++;
    }

    return;
}




/*
 * @COMPLEXITY: O(nlogn)
 *
 * The static function merge_sort_recursive() is the recursive implementation
 * of the merge sort algorithm in C.It has a base case to end recursion.It splits
 * the array into two half subarrays, and those subarrays into two more subarrays
 * and so on.Once the base case has been reached, the two subarrrays are
 * merged into a single sorted array and so on, until the entire initial array
 * is completely sorted.
 *
 * @param:   void           **A
 * @param:   void           **T
 * @param:   int            n
 * @param:   SortCompareFn  cmp
 * @return:  void
 *
 */

static void merge_sort_recursive(void **A,void **T,int n,SortCompareFn cmp)
{
    int middle;

    if (n<=1)
    {
        return;
    }

    middle=n/2;
    merge_sort_recursive(A,T,middle,cmp);
    merge_sort_recursive(A+middle,T,n-middle,cmp);
    merge(A,T,middle,n,cmp);
    return;
}





/*
 * @COMPLEXITY: O(nlogn)
 *
 * The function merge_sort() is the calling interface
 * for the recursive merge sort algorithm in C.It checks
 * if the given arguments are valid, if so it proceeds,
 * otherwise it terminated execution based on invalid assertions.
 *
 * @param:   void           **A
 * @param:   int            n
 * @param:   SortCompareFn  cmp
 * @return:  void
 *
 */

void merge_sort(void **A,int n,SortCompareFn cmp)
{
    void **T=NULL;
    assert(A!=NULL && n>=0 && cmp!=NULL);
    T=(void **)malloc(n/2*sizeof(void *));
    assert(T!=NULL);
    merge_sort_recursive(A,T,n,cmp);
    free(T);
    T=NULL;
    return;
}





/*
 * @COMPLEXITY: Best O(n), Worst O(n^2) 
 *
 * The function insertion_sort() is the implementation
 * of the insertion sort algorithm in C.It takes as arugments 
 * an array of void pointers, the length of the array and
 * a comparison function.It iterates, consuming one input
 * element each repetition, and growing the sorted output list.
 * Each iteration, insertion sort removes one element from the
 * input data,finds the location it belongs within the sorted list
 * and it inserts it there,it repeats until no input element remains.
 *
 * @param:   void           **A
 * @param:   int            n
 * @param:   SortCompareFn  cmp
 * @return:  void
 *
 */

void insertion_sort(void **A,int n,SortCompareFn cmp)
{
    int i,j;
    assert(A!=NULL && n>=0 && cmp!=NULL);

    for (i=1;i<n;i++)
    {
        for (j=i-1;j>=0 && cmp(A[j],A[j+1])>0;j--)
        {
            swap(A,j,j+1);
        }
    }

    return;
}


