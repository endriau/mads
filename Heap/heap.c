/*
 * This file contains function definitions
 * of procedures regarding the binary heap
 * data structure.
 *
 * @author: Endri Kastrati
 * @date:   8/01/2016
 *
 */




/*
 * Including the standard input-output library,
 * the standard utilities library, the standard
 * assertion library and the heap.h header file
 * that contains data type definitions and function
 * prototypings for the binary heap data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"






/*
 * @COMPLEXITY: Theta(1)
 *
 * The function heap_create() takes four arguments, an integer and three
 * function pointers.It creates a new heap_t data structure by allocating
 * memory for it and it's components and instantiates it's components to
 * the default values.The print and cmp components are mandatory and
 * cannot be null, the destroy component on the other hand can be null.
 * The integer type has to be either MIN_HEAP or MAX_HEAP.The user has
 * to create their own cmp,print,destroy (optional) functions.
 * Failure to do so will result in program termination due to invalid
 * assertions.
 *      
 * @param:   int                type
 * @param:   HeapCompareFn      cmp
 * @param:   HeapPrintFn        print
 * @param:   HeapDestroyFn      destroy
 * @return:  heap_t             *
 *
 */

heap_t *heap_create(int type,HeapCompareFn cmp,HeapPrintFn print,HeapDestroyFn destroy)
{
    lluint initial_size=4;
    heap_t *heap=NULL;
    assert(type==MIN_HEAP || type==MAX_HEAP);
    assert(cmp!=NULL && print!=NULL);
    heap=(heap_t *)malloc(sizeof(*heap));
    assert(heap!=NULL);
    heap->A=(void **)malloc(initial_size*sizeof(void *));
    assert(heap->A!=NULL);
    heap->size=initial_size;
    heap->n=0;
    heap->type=type;
    heap->cmp=cmp;
    heap->print=print;
    heap->destroy=destroy;
    return heap;
}








/*
 * @COMPLEXITY: O(logn)
 *
 * The static function heap_bubbleup() takes two arguments, a heap_t
 * data structure, an integer that represents a position within
 * the array and it bubbles up the item at the given index 
 * until the heap property is preserved depending on the
 * type of heap that has been created.
 *
 * @param:   heap_t     *h
 * @praam:   lluint     position
 * @return:  void
 *
 */

static void heap_bubbleup(heap_t *h,lluint position)
{
    void *temp=NULL;
    lluint parent=position/2,index=position;

    if (h->type==MIN_HEAP)
    {
        while (index!=1 && h->cmp(h->A[parent],h->A[index])>0)
        {
            temp=h->A[index];
            h->A[index]=h->A[parent];
            h->A[parent]=temp;
            index=parent;
            parent=index/2;
        }
    }
    else
    {
        while (index!=1 && h->cmp(h->A[parent],h->A[index])<0)
        {
            temp=h->A[index];
            h->A[index]=h->A[parent];
            h->A[parent]=temp;
            index=parent;
            parent=index/2;
        }
    }

    temp=NULL;
    return;
}







/*
 * @COMPLEXITY: O(logn)
 *
 * The heap_insert() function takes two arguments, a heap_t
 * data structure, an address to some data and inserts
 * that data at the end of the array and invokes the heap_bubbleup()
 * function to restore the heap property.
 *
 * @param:   heap_t     *h
 * @param:   void       *data
 * @return:  void
 *
 */

void heap_insert(heap_t *h,void *data)
{
    lluint double_size=0;
    assert(h!=NULL);
    
    if (heap_isEmpty(h)==1)
    {
        h->n=1;
    }

    if (h->n+1==h->size)
    {
        double_size=h->size*2;
        h->A=(void **)realloc(h->A,double_size*sizeof(void **));
        assert(h->A!=NULL);
        h->size=double_size;
    }

    h->A[h->n]=data;
    heap_bubbleup(h,h->n);
    h->n++;
    return;
}







/*
 * @COMPLEXITY: O(2n)
 *
 * The function heap_build() takes three arguments,
 * a heap_t data structure, an array of void pointers
 * and the size of the array and inserts all the elements
 * of the array into the heap by invoking the heap_insert()
 * function for every element of the array.Building a heap
 * via this method takes linear time.
 *
 * @param:   heap_t     *h
 * @param:   void       **Array
 * @param:   lluint     n
 * @return:  void
 *
 */

void heap_build(heap_t *h,void **Array,lluint n)
{
    lluint i;
    assert(h!=NULL && Array!=NULL);
    
    while (heap_isEmpty(h)==0)
    {
        heap_removeRoot(h);
    }

    for (i=0;i<n;i++)
    {
        heap_insert(h,Array[i]);
    }
    
    return;
}






/*
 * @COMPLEXITY: O(n)
 *
 * The function heap_find() takes two arguments
 * a heap_t data structure and an adress to some
 * data and performs a linear search throughout
 * the populated heap array.If it finds the given
 * data it returns the location of it in the array,
 * otherwise it returns minus one.
 *
 * @param:   heap_t     *h
 * @param:   void       *item
 * @return:  int
 *
 */

int heap_find(heap_t *h,void *item)
{
    int compare; lluint i;
    assert(h!=NULL && item!=NULL);

    for (i=1;i<h->n;i++)
    {
        compare=h->cmp(h->A[i],item);

        if (compare==0)
        {
            return i;
        }
    }

    return -1;
}







/*
 * @COMPLEXITY: Theta(1)
 *
 * The function heap_getRoot() takes as argument
 * a heap_t data structure and returns the
 * root element of the binary heap data structure,
 * if the heap is empty it returns null.
 *
 * @param:   heap_t     *h
 * @return:  void       *
 *
 */

void *heap_getRoot(heap_t *h)
{
    assert(h!=NULL);

    if (heap_isEmpty(h)==1)
    {
        return NULL;
    }
    else
    {
        return h->A[1];
    }
}








/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function minchild() takes two
 * arguments a heap_t data structure and an
 * integer representing the index of a subroot
 * into the heap tree and returns it's child with
 * the minimum value.
 *
 * @param:   heap_t     *h
 * @param:   lluint     parent
 * @return:  lluint
 *
 */

static lluint minchild(heap_t *h,lluint parent)
{

    lluint right_child,left_child;
    lluint minimum; int result;
    assert(h!=NULL);
    right_child=2*parent+1;
    left_child=2*parent;
    
    if (left_child<h->n)
    {
        if (right_child<h->n)
        {
            result=h->cmp(h->A[left_child],h->A[right_child]);

            if (result<0)
            {
                minimum=left_child;
            }
            else
            {
                minimum=right_child;
            }
        }
        else
        {
            minimum=left_child;
        }
    }
    else
    {
        minimum=0;
    }

    return minimum;
}






/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function maxchild() takes two
 * arguments, a heap_t data structure and
 * an integer representing the index of a subroot
 * into the heap tree and returns it's child with
 * the maximum value.
 *
 * @param:   heap_t     *h
 * @param:   lluint     parent
 * @return:  lluint
 *
 */

static lluint maxchild(heap_t *h,lluint parent)
{
    int result; lluint maximum;
    lluint left_child,right_child;
    assert(h!=NULL);
    right_child=2*parent+1;
    left_child=2*parent;

    if (left_child<h->n)
    {
        if (right_child<h->n)
        {
            result=h->cmp(h->A[left_child],h->A[right_child]);

            if (result>0)
            {
                maximum=left_child;
            }
            else
            {
                maximum=right_child;
            }
        }
        else
        {
            maximum=left_child;
        }
    }
    else
    {
        maximum=0;
    }

    return maximum;
}







/*
 * @COMPLEXITY: O(logn)
 *
 * The static function heap_siftdown() takes two arguments, a heap_t
 * data structure, an integer that represents a position within
 * the array and it sifts down the item at the given index 
 * until the heap property is preserved depending on the
 * type of heap that has been created.It invokes either
 * minchild() or maxchild() functions depending on the type
 * of the heap that has been created.
 *
 * @param:   heap_t     *h
 * @param:   lluint     position
 * @return:  void
 *
 */

static void heap_siftdown(heap_t *h,lluint position)
{ 
    void *temp=NULL;
    lluint child,parent=position;
    assert(h!=NULL);

    if (h->type==MIN_HEAP)
    {
        child=minchild(h,parent);

        while (child!=0 && h->cmp(h->A[child],h->A[parent])<0)
        {
            temp=h->A[parent];
            h->A[parent]=h->A[child];
            h->A[child]=temp;
            parent=child;
            child=minchild(h,parent);
        }
    }
    else
    {
        child=maxchild(h,parent);

        while (child!=0 && h->cmp(h->A[child],h->A[parent])>0)
        {
            temp=h->A[parent];
            h->A[parent]=h->A[child];
            h->A[child]=temp;
            parent=child;
            child=maxchild(h,parent);
        }
    }

    temp=NULL;
    return;
}








/*
 * @COMPLEXITY: O(logn)
 *
 * The function heap_removeRoot() takes only one
 * argument, a heap_t data structure and removes the
 * root of the binary heap and re-heapifies the entire
 * tree such that the heap property is preserved.
 *
 * @param:   heap_t     *h
 * @return:  void
 *
 */

void heap_removeRoot(heap_t *h)
{
    void *temp=NULL;
    assert(h!=NULL);
    
    if (heap_isEmpty(h)==1)
    {
        return;
    }

    temp=h->A[1];
    h->A[1]=h->A[h->n-1];
    h->A[h->n-1]=temp;
    h->n-=1;

    if (h->destroy!=NULL)
    {
        h->destroy(h->A[h->n]);
    }

    heap_siftdown(h,1);
    h->A[h->n]=NULL;
    temp=NULL;
    return;
}










/*
 * @COMPLEXITY: O(logn)
 *
 * The function heap_changeKey() takes three arguments,
 * a heap_t data structure,an integer that represents an
 * index within the heap array, an address to some data
 * and changes the item at the specific index with the
 * given one and restores the heap property if necessary,
 * depending on the type of heap constructed.
 * If the item does not exist nothing happens.
 *
 * @param:   heap_t     *h
 * @param:   lluint     index
 * @param:   void       *item
 * @return:  void
 *
 */

void heap_changeKey(heap_t *h,lluint index,void *item)
{
    int result;
    void *old_temp=NULL;
    assert(h!=NULL);

    if (index==-1)
    {
        return;
    }
    else
    {
        old_temp=h->A[index];
        h->A[index]=item;
        result=h->cmp(old_temp,item);

        if (h->type==MAX_HEAP)
        {
            if (result>0)
            {
                heap_siftdown(h,index);
            }
            else
            {
                heap_bubbleup(h,index);
            }
        }
        else
        {
            if (result<0)
            {
                heap_siftdown(h,index);
            }
            else
            {
                heap_bubbleup(h,index);
            }
        }

        if (h->destroy!=NULL)
        {
            h->destroy(old_temp);
        }

        old_temp=NULL;
        return;
    }
}
    








/*
 * @COMPLEXITY: Theta(1)
 *
 * The function heap_isEmpty() takes a heap_t
 * data structure as argument and checks whether
 * the heap array is empty or not.If the array is
 * empty it returns one otherwise it returns zero.
 *
 * @param:   heap_t     *h
 * @return:  int
 *
 */

int heap_isEmpty(heap_t *h)
{
    assert(h!=NULL);
    return (h->n==0 ? 1 : 0);
}






/*
 * @COMPLEXITY: O(n)
 *
 * The static function heap_recursive_print() takes three 
 * arguments, a heap_t data structure, an index to an element
 * of the heap array, an integer that represents the current
 * depth of the recursion and prints the elements of the heap
 * array in a binary tree format.
 *
 * @param:   heap_t     *h
 * @param:   lluint     child
 * @param:   lluint     depth
 * @return:  void
 *
 */

static void heap_recursive_print(heap_t *h,lluint child,lluint depth)
{
    lluint i;
    assert(h!=NULL);

    if (h->n<=child)
    {
        return;
    }

    heap_recursive_print(h,child*2+1,depth+1);

    for (i=0;i<depth;i++)
    {
        printf("        ");
    }

    h->print(h->A[child]);
    printf("\n");
    heap_recursive_print(h,child*2,depth+1);
    return;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The heap_print() function takes one argument,
 * a heap_t data structure and prints the elements
 * of the heap array in a tree-like format by
 * invoking the static function heap_recursive_print().
 * 
 * @param:   heap_t     *h
 * @return:  void
 *
 */

void heap_print(heap_t *h)
{
    lluint root=1;
    assert(h!=NULL);
    printf("----------BINARY HEAP----------\n");
    heap_recursive_print(h,root,1);
    printf("-------------------------------\n");
    return;
}







/*
 * @COMPLEXITY: Best case Theta(1),worst case O(n)
 *
 * The function heap_free() takes only one
 * argument a heap_t data structure and deallocates
 * all memory that has been allocated for it's components
 * and itself.If the destroy component does not equal to null
 * then the elements of the array are deallocated as well.
 *
 * @param:   heap_t     *h
 * @return:  void
 *
 */

void heap_free(heap_t *h)
{
    lluint i;
    assert(h!=NULL);
    
    if (h->destroy!=NULL)
    {
        for (i=1;i<h->n;i++)
        {
            free(h->A[i]);
            h->A[i]=NULL;
        }
    }

    free(h->A);
    h->A=NULL;
    free(h);
    h=NULL;
    return;
}
