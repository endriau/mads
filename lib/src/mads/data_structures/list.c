// ReSharper disable CppDFANullDereference
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/data_structures/list.h>


mads_list_t *mads_list_create(const mads_list_compare_fn cmp, const mads_list_print_fn print, const mads_list_destroy_fn destroy)
{
    mads_list_t *list = NULL;
    assert(cmp!=NULL && print!=NULL);
    list = (mads_list_t *)malloc(sizeof(*list));
    assert(list!=NULL);
    list->size = 0;
    list->head = list->foot = NULL;
    list->cmp = cmp;
    list->print = print;
    list->destroy = destroy;
    return list;
}


void mads_list_push(mads_list_t *list, void *data)
{
    mads_llnode_t *new_node = NULL;
    assert(list!=NULL);
    new_node = (mads_llnode_t *)malloc(sizeof(*new_node));
    assert(new_node!=NULL);
    new_node->data = data;
    new_node->previous = new_node->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
        list->foot = new_node;
    }
    else
    {
        list->head->previous = new_node;
        new_node->next = list->head;
        list->head = new_node;
    }

    list->size++;
}


void mads_list_append(mads_list_t *list, void *data)
{
    mads_llnode_t *new_node = NULL;
    assert(list!=NULL);
    new_node = (mads_llnode_t *)malloc(sizeof(*new_node));
    assert(new_node!=NULL);
    new_node->data = data;
    new_node->next = new_node->previous = NULL;

    if (list->foot == NULL)
    {
        list->foot = new_node;
        list->head = new_node;
    }
    else
    {
        list->foot->next = new_node;
        new_node->previous = list->foot;
        list->foot = new_node;
    }

    list->size++;
}


void mads_list_insert_at(mads_list_t *list, void *data, const unsigned long long int position)
{
    mads_llnode_t *next_node = NULL, *new_node = NULL;
    assert(list!=NULL && position<list->size);

    if (position == 0)
    {
        mads_list_push(list, data);
    }
    else if (position == list->size - 1)
    {
        mads_list_append(list, data);
    }
    else
    {
        unsigned long long int step = 0;
        new_node = (mads_llnode_t *)malloc(sizeof(*new_node));
        assert(new_node!=NULL);
        new_node->data = data;
        new_node->next = new_node->previous = NULL;
        next_node = list->head;

        while (next_node != NULL && step < position)
        {
            next_node = next_node->next;
            step++;
        }

        next_node->previous->next = new_node;
        new_node->previous = next_node->previous;
        next_node->previous = new_node;
        new_node->next = next_node;
        list->size++;
    }
}


void *mads_list_get_head(const mads_list_t *list)
{
    assert(list!=NULL);
    return list->head->data;
}


void *mads_list_get_foot(const mads_list_t *list)
{
    assert(list!=NULL);
    return list->foot->data;
}


void *mads_list_get_at(const mads_list_t *list, const unsigned long long int position)
{
    const mads_llnode_t *next_node = NULL;
    assert(list!=NULL && position<list->size);

    if (position == 0)
    {
        return mads_list_get_head(list);
    }

    if (position == list->size - 1)
    {
        return mads_list_get_foot(list);
    }

    unsigned long long int step = 0;
    next_node = list->head;

    while (next_node != NULL && step <= position)
    {
        next_node = next_node->next;
        step++;
    }

    return next_node->data;
}


void mads_list_remove_head(mads_list_t *list)
{
    mads_llnode_t *old_node = NULL;
    assert(list!=NULL);
    if (mads_list_is_empty(list)) { return; }

    if (list->head != list->foot)
    {
        list->head->next->previous = NULL;
        old_node = list->head;
        list->head = list->head->next;
        old_node->next = old_node->previous = NULL;
    }
    else
    {
        old_node = list->head;
        list->head = list->foot = NULL;
    }

    if (list->destroy != NULL)
    {
        list->destroy(old_node->data);
        old_node->data = NULL;
    }

    free(old_node);
    old_node = NULL;
    list->size--;
}


void mads_list_remove_foot(mads_list_t *list)
{
    mads_llnode_t *old_node = NULL;
    assert(list!=NULL);
    if (mads_list_is_empty(list)) { return; }

    if (list->foot != list->head)
    {
        list->foot->previous->next = NULL;
        old_node = list->foot;
        list->foot = list->foot->previous;
        old_node->next = old_node->previous = NULL;
    }
    else
    {
        old_node = list->foot;
        list->foot = list->head = NULL;
    }

    if (list->destroy != NULL)
    {
        list->destroy(old_node->data);
        old_node->data = NULL;
    }

    free(old_node);
    old_node = NULL;
    list->size--;
}


void mads_list_remove_at(mads_list_t *list, const unsigned long long int position)
{
    mads_llnode_t *old_node = NULL, *next_node = NULL;
    assert(list!=NULL && position<list->size);
    if (mads_list_is_empty(list)) { return; }

    if (position == 0)
    {
        mads_list_remove_head(list);
    }
    else if (position == list->size - 1)
    {
        mads_list_remove_foot(list);
    }
    else
    {
        unsigned long long int step = 0;
        next_node = list->head;

        while (next_node != NULL && step <= position)
        {
            next_node = next_node->next;
            step++;
        }

        next_node->next->previous = next_node->previous;
        next_node->previous->next = next_node->next;
        old_node = next_node;
        old_node->previous = old_node->next = NULL;

        if (list->destroy != NULL)
        {
            list->destroy(old_node->data);
            old_node->data = NULL;
        }

        free(old_node);
        old_node = NULL;
        list->size--;
    }
}


void mads_list_print(const mads_list_t *list)
{
    const mads_llnode_t *current_node = NULL;
    assert(list!=NULL);
    current_node = list->head;

    if (mads_list_is_empty(list) == 1)
    {
        printf("[]\n");
        return;
    }

    printf("[ ");

    while (current_node != NULL)
    {
        list->print(current_node->data);
        printf(", ");
        current_node = current_node->next;
    }

    printf("\b\b ]\n");
}


void mads_list_free(mads_list_t *list)
{
    mads_llnode_t *old_node = NULL, *next_node = NULL;
    assert(list!=NULL);
    next_node = list->head;

    while (next_node != NULL)
    {
        if (list->destroy != NULL)
        {
            list->destroy(next_node->data);
            next_node->data = NULL;
        }

        old_node = next_node;
        next_node = next_node->next;
        free(old_node);
        old_node = NULL;
    }

    old_node = NULL;
    free(list);
    list = NULL;
}


unsigned long long int mads_list_size(const mads_list_t *list)
{
    assert(list!=NULL);
    return (list->size);
}


int mads_list_is_empty(const mads_list_t *list)
{
    assert(list!=NULL);
    return (list->size == 0 ? 1 : 0);
}


int mads_list_has_elem(const mads_list_t *list, const void *item)
{
    unsigned long long int step = 0;
    const mads_llnode_t *next_node = NULL;
    assert(list!=NULL);
    next_node = list->head;

    while (next_node != NULL)
    {
        const int result = list->cmp(next_node->data, item);

        if (result == 0)
        {
            return step;
        }

        step++;
        next_node = next_node->next;
    }

    next_node = NULL;
    return -1;
}
