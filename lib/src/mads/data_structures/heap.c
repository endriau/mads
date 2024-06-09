// ReSharper disable CppDFANullDereference
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/data_structures/heap.h>


mads_heap_t *mads_heap_create(const int type, const mads_heap_compare_fn cmp, const mads_heap_print_fn print, const mads_heap_destroy_fn destroy)
{
    const unsigned long long int initial_size = 4;
    mads_heap_t *heap = NULL;
    assert(type == MADS_HEAP_MIN || type == MADS_HEAP_MAX);
    assert(cmp != NULL && print != NULL);
    heap = (mads_heap_t *)malloc(sizeof(*heap));
    assert(heap != NULL);
    heap->A = (void **)malloc(initial_size * sizeof(void *));
    assert(heap->A != NULL);
    heap->size = initial_size;
    heap->n = 0;
    heap->type = type;
    heap->cmp = cmp;
    heap->print = print;
    heap->destroy = destroy;
    return heap;
}


static void heap_bubble_up(const mads_heap_t *h, const unsigned long long int position)
{
    void *temp = NULL;
    unsigned long long int parent = position / 2, index = position;

    if (h->type == MADS_HEAP_MIN)
    {
        while (index != 1 && h->cmp(h->A[parent], h->A[index]) > 0)
        {
            temp = h->A[index];
            h->A[index] = h->A[parent];
            h->A[parent] = temp;
            index = parent;
            parent = index / 2;
        }
    }
    else
    {
        while (index != 1 && h->cmp(h->A[parent], h->A[index]) < 0)
        {
            temp = h->A[index];
            h->A[index] = h->A[parent];
            h->A[parent] = temp;
            index = parent;
            parent = index / 2;
        }
    }

    temp = NULL;
}


void mads_heap_insert(mads_heap_t *h, void *data)
{
    assert(h != NULL);

    if (mads_heap_is_empty(h) == 1)
    {
        h->n = 1;
    }

    if (h->n + 1 == h->size)
    {
        const unsigned long long int double_size = h->size * 2;
        h->A = (void **)realloc(h->A, double_size * sizeof(void **));
        assert(h->A != NULL);
        h->size = double_size;
    }

    h->A[h->n] = data;
    heap_bubble_up(h, h->n);
    h->n++;
}


void mads_heap_build(mads_heap_t *h, void **Array, const unsigned long long int n)
{
    assert(h != NULL && Array != NULL);

    while (mads_heap_is_empty(h) == 0)
    {
        mads_heap_remove_root(h);
    }

    for (unsigned long long int i = 0; i < n; i++)
    {
        mads_heap_insert(h, Array[i]);
    }
}


int mads_heap_find(const mads_heap_t *h, const void *item)
{
    assert(h != NULL && item != NULL);

    for (unsigned long long int i = 1; i < h->n; i++)
    {
        const int compare = h->cmp(h->A[i], item);

        if (compare == 0)
        {
            return i;
        }
    }

    return -1;
}


void *mads_heap_get_root(const mads_heap_t *h)
{
    assert(h != NULL);

    if (mads_heap_is_empty(h) == 1)
    {
        return NULL;
    }
    else
    {
        return h->A[1];
    }
}


static unsigned long long int heap_min_child(const mads_heap_t *h, const unsigned long long int parent)
{
    unsigned long long int minimum;
    assert(h != NULL);
    const unsigned long long int right_child = 2 * parent + 1;
    const unsigned long long int left_child = 2 * parent;

    if (left_child < h->n)
    {
        if (right_child < h->n)
        {
            const int result = h->cmp(h->A[left_child], h->A[right_child]);

            if (result < 0)
            {
                minimum = left_child;
            }
            else
            {
                minimum = right_child;
            }
        }
        else
        {
            minimum = left_child;
        }
    }
    else
    {
        minimum = 0;
    }

    return minimum;
}


static unsigned long long int heap_max_child(const mads_heap_t *h, const unsigned long long int parent)
{
    unsigned long long int maximum;
    assert(h != NULL);
    const unsigned long long int right_child = 2 * parent + 1;
    const unsigned long long int left_child = 2 * parent;

    if (left_child < h->n)
    {
        if (right_child < h->n)
        {
            const int result = h->cmp(h->A[left_child], h->A[right_child]);

            if (result > 0)
            {
                maximum = left_child;
            }
            else
            {
                maximum = right_child;
            }
        }
        else
        {
            maximum = left_child;
        }
    }
    else
    {
        maximum = 0;
    }

    return maximum;
}


static void heap_sift_down(const mads_heap_t *h, const unsigned long long int position)
{
    void *temp = NULL;
    unsigned long long int child, parent = position;
    assert(h != NULL);

    if (h->type == MADS_HEAP_MIN)
    {
        child = heap_min_child(h, parent);

        while (child != 0 && h->cmp(h->A[child], h->A[parent]) < 0)
        {
            temp = h->A[parent];
            h->A[parent] = h->A[child];
            h->A[child] = temp;
            parent = child;
            child = heap_min_child(h, parent);
        }
    }
    else
    {
        child = heap_max_child(h, parent);

        while (child != 0 && h->cmp(h->A[child], h->A[parent]) > 0)
        {
            temp = h->A[parent];
            h->A[parent] = h->A[child];
            h->A[child] = temp;
            parent = child;
            child = heap_max_child(h, parent);
        }
    }

    temp = NULL;
}


void mads_heap_remove_root(mads_heap_t *h)
{
    void *temp = NULL;
    assert(h != NULL);

    if (mads_heap_is_empty(h) == 1)
    {
        return;
    }

    temp = h->A[1];
    h->A[1] = h->A[h->n - 1];
    h->A[h->n - 1] = temp;
    h->n -= 1;

    if (h->destroy != NULL)
    {
        h->destroy(h->A[h->n]);
    }

    heap_sift_down(h, 1);
    h->A[h->n] = NULL;
    temp = NULL;
}


void mads_heap_change_key(const mads_heap_t *h, const unsigned long long int position, void *item)
{
    void *old_temp = NULL;
    assert(h != NULL);

    if (position == -1)
    {
        return;
    }
    else
    {
        old_temp = h->A[position];
        h->A[position] = item;
        const int result = h->cmp(old_temp, item);

        if (h->type == MADS_HEAP_MAX)
        {
            if (result > 0)
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
            if (result < 0)
            {
                heap_sift_down(h, position);
            }
            else
            {
                heap_bubble_up(h, position);
            }
        }

        if (h->destroy != NULL)
        {
            h->destroy(old_temp);
        }

        old_temp = NULL;
    }
}


int mads_heap_is_empty(const mads_heap_t *h)
{
    assert(h != NULL);
    return (h->n == 0 ? 1 : 0);
}


static void heap_recursive_print(mads_heap_t *h, const unsigned long long int child, const unsigned long long int depth)
{
    assert(h != NULL);

    if (h->n <= child)
    {
        return;
    }

    heap_recursive_print(h, child * 2 + 1, depth + 1);

    for (unsigned long long int i = 0; i < depth; i++)
    {
        printf("        ");
    }

    h->print(h->A[child]);
    printf("\n");
    heap_recursive_print(h, child * 2, depth + 1);
}


void mads_heap_print(mads_heap_t *h)
{
    const unsigned long long int root = 1;
    assert(h != NULL);
    printf("----------BINARY HEAP----------\n");
    heap_recursive_print(h, root, 1);
    printf("-------------------------------\n");
}


void mads_heap_free(mads_heap_t *h)
{
    assert(h != NULL);

    if (h->destroy != NULL)
    {
        for (unsigned long long int i = 1; i < h->n; i++)
        {
            free(h->A[i]);
            h->A[i] = NULL;
        }
    }

    free(h->A);
    h->A = NULL;
    free(h);
    h = NULL;
}
