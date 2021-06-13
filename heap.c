//
// Created by p0int3r on 6/13/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"



heap_t *heap_create(int type, heap_compare_fn cmp, heap_print_fn print, heap_destroy_fn destroy)
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


static void heap_bubble_up(heap_t *h, lluint position)
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
}


void heap_insert(heap_t *h,void *data)
{
    lluint double_size=0;
    assert(h!=NULL);

    if (heap_is_empty(h) == 1)
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
    heap_bubble_up(h, h->n);
    h->n++;
}


void heap_build(heap_t *h,void **Array,lluint n)
{
    lluint i;
    assert(h!=NULL && Array!=NULL);

    while (heap_is_empty(h) == 0)
    {
        heap_remove_root(h);
    }

    for (i=0;i<n;i++)
    {
        heap_insert(h,Array[i]);
    }
}


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


void *heap_get_root(heap_t *h)
{
    assert(h!=NULL);

    if (heap_is_empty(h) == 1)
    {
        return NULL;
    }
    else
    {
        return h->A[1];
    }
}


static lluint heap_min_child(heap_t *h, lluint parent)
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


static lluint heap_max_child(heap_t *h, lluint parent)
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


static void heap_sift_down(heap_t *h, lluint position)
{
    void *temp=NULL;
    lluint child,parent=position;
    assert(h!=NULL);

    if (h->type==MIN_HEAP)
    {
        child= heap_min_child(h, parent);

        while (child!=0 && h->cmp(h->A[child],h->A[parent])<0)
        {
            temp=h->A[parent];
            h->A[parent]=h->A[child];
            h->A[child]=temp;
            parent=child;
            child= heap_min_child(h, parent);
        }
    }
    else
    {
        child= heap_max_child(h, parent);

        while (child!=0 && h->cmp(h->A[child],h->A[parent])>0)
        {
            temp=h->A[parent];
            h->A[parent]=h->A[child];
            h->A[child]=temp;
            parent=child;
            child= heap_max_child(h, parent);
        }
    }

    temp=NULL;
}


void heap_remove_root(heap_t *h)
{
    void *temp=NULL;
    assert(h!=NULL);

    if (heap_is_empty(h) == 1)
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

    heap_sift_down(h, 1);
    h->A[h->n]=NULL;
    temp=NULL;
}


void heap_change_key(heap_t *h, lluint position, void *item)
{
    int result;
    void *old_temp=NULL;
    assert(h!=NULL);

    if (position == -1)
    {
        return;
    }
    else
    {
        old_temp=h->A[position];
        h->A[position]=item;
        result=h->cmp(old_temp,item);

        if (h->type==MAX_HEAP)
        {
            if (result>0)
            {
                heap_sift_down(h, position);
            }
            else
            {
                heap_bubble_up(h, position);
            }
        }
        else
        {
            if (result<0)
            {
                heap_sift_down(h, position);
            }
            else
            {
                heap_bubble_up(h, position);
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



int heap_is_empty(heap_t *h)
{
    assert(h!=NULL);
    return (h->n==0 ? 1 : 0);
}


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
}


void heap_print(heap_t *h)
{
    lluint root=1;
    assert(h!=NULL);
    printf("----------BINARY HEAP----------\n");
    heap_recursive_print(h,root,1);
    printf("-------------------------------\n");
}



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
}
