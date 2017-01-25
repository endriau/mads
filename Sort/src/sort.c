/*
 * This file contains definitions for procedures
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
 * the standard assertion library,the header file
 * random.h that contains datatype definitions and
 * function prototyping regarding the mersenne twister
 * pseudo-random number generator and the header 
 * files sort.h and stack.h which  contain datatype 
 * definitions  and function prototypings for the 
 * sort and stack procedures.
 *
 */

#include <stdlib.h>
#include <assert.h>
#include "random.h"
#include "stack.h"
#include "sort.h"






/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function compare_indices() is a dummy pointer
 * function which does nothing but is needed for the creation
 * of the stack_t data structure which will be used in the
 * iterative versions of quick sort and merge sort.
 *
 * @param:   const void     *i1
 * @param:   const void     *i2
 * @return:  int
 *
 */

static int compare_indices(const void *i1,const void *i2)
{
    // Not Required since we will not be looking
    // into the stack data structure as it is needed
    // only for insertions and pop outs.
    return 0;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function compare_indices() is a dummy pointer
 * function which does nothing but is needed for the creation
 * of the stack_t data structure which will be used in the
 * iterative versions of quick sort and merge sort.
 *
 * @param:   const void     *i
 * @return:  void
 *
 */

static void print_index(const void *i)
{
    // Not requred since we will not be printing
    // the elements of the stack data structure.
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function swap() takes an array
 * of void pointers and two numeric values 
 * i,j representing indices and swaps the
 * the address at i with the address at j.
 *
 * @param:   void       **A
 * @param:   llint      i
 * @param:   llint      j
 * @return:  void
 *
 */

static void swap(void **A,llint i,llint j)
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
 * when the partition has finished, and a function pointer of type SortCompareFn.
 * The partitioning process moves elements greater than the pivot to the right
 * of the pivot and elements less than the pivot to the left of the pivot.
 * It also keeps track of equal items thus not including then in the partitioning.
 * 
 * @param:   void               **A
 * @param:   llint              n
 * @param:   void               *pivot
 * @param:   llint              *first_eq
 * @param:   llint              *first_gt
 * @param:   SortCompareFn      cmp
 * @return:  void
 *
 */

static void partition(void **A,llint n,void *pivot,llint *first_eq,llint *first_gt,SortCompareFn cmp)
{
    llint next=0,fe=0,fg=n,outcome=0;
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
 * implementaiton of the quick sort algorithm in C.It has a base
 * case to end recursion.It partitions an array into two subarrays
 * based on a randomly selected pivot and calls quick_sort_recursive()
 * on those two subarrays respectively and so on.
 *
 * @param:   void               **A
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @return:  void
 *
 */

static void quick_sort_recursive(void **A,llint n,SortCompareFn cmp)
{
    llint first_eq,first_gt;
    if (n<=1) { return; }
    partition(A,n,A[genrand64_int63()%n],&first_eq,&first_gt,cmp);
    quick_sort_recursive(A,first_eq,cmp);
    quick_sort_recursive(A+first_gt,n-first_gt,cmp);
    return;
}






/*
 * @COMPLEXITY: Best O(nlogn), Worst O(n^2)
 *
 * The static function quick_sort_iterative() is the iterative
 * implementation of the quick sort algorithm in C using explicit
 * stacks instead of recursion.This function takes three arguments
 * as parameters,namely an array of void pointers,it's length and
 * a function pointer of type SortCompareFn.The result of each
 * partition ( left and right ) is pushed into the stack if it is
 * larger than zero in length.Initially the stack contains the whole
 * range ( 0 to n-1 ) to be sorted.Sorting continues until the stack
 * is empty.
 *
 * @param:   void               **A
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @return:  void
 * 
 */

static void quick_sort_iterative(void **A,llint n,SortCompareFn cmp)
{
    stack_t *stack=NULL;
    llint first_eq,first_gt,new_n;
    llint left=0,right=n-1,random_index;
    assert(A!=NULL && cmp!=NULL && n>=0);
    stack=stack_create(compare_indices,print_index,NULL);
    stack_push(stack,(void *)left);
    stack_push(stack,(void *)right);

    while (!stack_isEmpty(stack))
    {
        right=(llint )stack_pop(stack);
        left=(llint )stack_pop(stack);

        if ((right-left)>0)
        {
            new_n=(right-left)+1;
            random_index=left+genrand64_int63()%new_n;
            partition(A+left,new_n,A[random_index],
                        &first_eq,&first_gt,cmp);

            if (first_eq>1)
            {
                stack_push(stack,(void *)left);
                stack_push(stack,(void *)(left+first_eq-1));
            }

            if (first_gt<new_n)
            {
                stack_push(stack,(void *)(left+first_gt));
                stack_push(stack,(void *)right);
            }
        }
    }

    stack_free(stack);
    return;
}







/*
 * @COMPLEXITY: Best O(nlogn), Worst O(n^2)
 *
 * The function quick_sort() is the calling interface for the
 * recursive/iterative implementation of quick sort algorithm.
 * Checks if the given arguments are valid, if so proceeds,
 * otherwise terminates execution based on failed assertions.
 *
 * @param:   void               **A
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @param:   int                type
 * @return:  void
 *
 */

void quick_sort(void **A,llint n,SortCompareFn cmp,int type)
{
    assert(A!=NULL && n>=0 && cmp!=NULL);
    assert(type==RECURSIVE_SORT || type==ITERATIVE_SORT);
    if (type==RECURSIVE_SORT) { quick_sort_recursive(A,n,cmp); }
    if (type==ITERATIVE_SORT) { quick_sort_iterative(A,n,cmp); }
    return;
}






/*
 * @COMPLEXITY: O(n)
 *
 * The static function merge() takes as arguments two arrays 
 * A,T of void pointers, the middle,the length of array A and a comparison function.
 * To merge, the first of the two regions of A ( from 0 .. mid-1 ) is copied into 
 * the temporary array T.Elements are peeled off the front of the temporary array T
 * and the front of the second segment of the array A ( mid .. n-1 ) in sorted order
 * filling up A again, starting at A[0].Once either of the segments is exhausted the
 * remaining elements from T are copied into the last vacant locations in A.If T
 * is exhausted first, the remaining items in the second segment in A are already
 * in their correct locations, and no further action is required.
 *
 * @param:   void               **A
 * @param:   void               **T
 * @param:   llint              mid
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @return:  void
 *
 */

static void merge(void **A,void **T,llint mid,llint n,SortCompareFn cmp)
{
    llint i,s1=0,s2=mid,outcome;
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
 * @param:   void               **A
 * @param:   void               **T
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @return:  void
 *
 */

static void merge_sort_recursive(void **A,void **T,llint n,SortCompareFn cmp)
{
    if (n<=1) { return; }
    llint middle=n/2;
    merge_sort_recursive(A,T,middle,cmp);
    merge_sort_recursive(A+middle,T,n-middle,cmp);
    merge(A,T,middle,n,cmp);
    return;
}





/*
 * @COMPLEXITY: O(nlogn)
 *
 * The static function merge_sort_iterative() is the iterative implementation
 * of the merge sort algorithm in C using explicit stacks instead of recursion.
 * This function takes four arguments as parameters,namely two arrays of void
 * pointers,the length of the first array and a function pointer of type 
 * SortCompareFn.Allocates memory for two stacks,one that contains the boundaries
 * left and right and another one that contains the type of call for those particular
 * boundaries.The type can either be 'c' ( for call ) or 'm' ( for merge ).If the type
 * is 'c' then change it to an 'm' and push the boundaries back into the stack.If on
 * the other hand the type is 'm' then it is safe to merge the partitions as they have
 * been sorted.
 *
 * @param:   void               **A
 * @param:   void               **T
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @return:  void
 *
 */

static void merge_sort_iterative(void **A,void **T,llint n,SortCompareFn cmp)
{
    llint left=0,right=n-1,mid;
    stack_t *stack=NULL,*calls=NULL;
    llint type_call=99,type_merge=109,type;
    assert(A!=NULL && T!=NULL);
    assert(n>=0 && cmp!=NULL);
    stack=stack_create(compare_indices,print_index,NULL);
    calls=stack_create(compare_indices,print_index,NULL);
    stack_push(stack,(void *)left);
    stack_push(stack,(void *)right);
    stack_push(calls,(void *)type_call);

    while (!stack_isEmpty(stack))
    {
        right=(llint )stack_pop(stack);
        left=(llint )stack_pop(stack);
        type=(llint )stack_pop(calls);
        mid=(right+left)/2;

        if (type==type_call)
        {
            if ((right-left)>0)
            {
                stack_push(stack,(void *)left);
                stack_push(stack,(void *)right);
                stack_push(calls,(void *)type_merge);
                stack_push(stack,(void *)left);
                stack_push(stack,(void *)mid);
                stack_push(calls,(void *)type_call);
                stack_push(stack,(void *)(mid+1));
                stack_push(stack,(void *)right);
                stack_push(calls,(void *)type_call);
            }
        }
        else
        {
            merge(A+left,T,mid-left+1,right-left+1,cmp);
        }
    }

    stack_free(stack);
    stack_free(calls);
    return;
}









/*
 * @COMPLEXITY: O(nlogn)
 *
 * The function merge_sort() is the calling interface for the
 * iterative/recursive merge sort algorithm in C.It checks
 * if the given arguments are valid, if so it proceeds,
 * otherwise it terminates execution based on invalid assertions.
 *
 * @param:   void               **A
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @param:   int                type
 * @return:  void
 *
 */

void merge_sort(void **A,llint n,SortCompareFn cmp,int type)
{
    void **T=NULL;
    assert(type==RECURSIVE_SORT || type==ITERATIVE_SORT);
    assert(A!=NULL && n>=0 && cmp!=NULL);
    T=(void **)malloc((1+n/2)*sizeof(void *)); assert(T!=NULL);
    if (type==RECURSIVE_SORT) { merge_sort_recursive(A,T,n,cmp); }
    if (type==ITERATIVE_SORT) { merge_sort_iterative(A,T,n,cmp); }
    free(T); T=NULL;
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
 * @param:   void               **A
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @return:  void
 *
 */

void insertion_sort(void **A,llint n,SortCompareFn cmp)
{
    llint i,j;
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




/*
 * @COMPLEXITY: O(n)
 *
 * The function is_sorted(),takes three arguments
 * as parameters,namely an array of void pointers,
 * it's length and a function pointer of type
 * SortCompareFn.It iterates through the entire
 * array and checks if the consecutive elements
 * match the comparison criteria and satisfy the
 * sort properties.
 *
 * @param:   void               **A
 * @param:   llint              n
 * @param:   SortCompareFn      cmp
 * @return:  int
 *
 */

int is_sorted(void **A,llint n,SortCompareFn cmp)
{
    llint i=0; int flag=0;
    assert(A!=NULL && n>=0 && cmp!=NULL);
    
    for (i=1;i<n;i++)
    {
        if (cmp(A[i-1],A[i])<=0)
        {
            flag=1;
            continue;
        }
        else
        {
            flag=0;
            return flag;
        }
    }

    return flag;
}
