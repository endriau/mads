//
// Created by p0int3r on 6/13/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data_structures/avl_tree.h"
#include "data_structures/list.h"
#include "hash_table.h"


static int hash_table_compare_pairs(const void *p1, const void *p2)
{
    pair_t *pp1=NULL,*pp2=NULL;
    cue_t *c1=NULL,*c2=NULL;
    pp1=(pair_t *)p1;
    pp2=(pair_t *)p2;
    c1= pair_get_cue(pp1);
    c2= pair_get_cue(pp2);
    return cue_compare_to(c1, cue_get(c2));
}


static void hash_table_print_pair(const void *p)
{
    pair_t *pair=NULL;
    pair=(pair_t *)p;
    pair_print(pair);
}


static void hash_table_deallocate_pair(void *p)
{
    pair_t *pair=NULL;
    pair=(pair_t *)p;
    pair_free(pair);
    pair=NULL;
}


static double hash_table_load_factor(hash_table_t *t)
{
    double lf;
    assert(t!=NULL);
    lf=(double )(t->n)/(t->size);
    t->lf=lf; return lf;
}


static int hash_table_is_prime(lluint n)
{
    lluint divisor;
    lluint isprime=1;
    if (n<2) { return 0; }

    for (divisor=2;divisor*divisor<=n;divisor++)
    {
        if (n%divisor==0)
        {
            isprime=0;
            break;
        }
    }

    return isprime;
}


static lluint hash_table_next_prime(lluint n)
{
    lluint step;
    assert(n!=0);
    step=n+1;

    while (hash_table_is_prime(step) == 0)
    {
        step++;
    }

    return step;
}


static void hash_table_rehash(hash_table_t *t)
{
    assert(t!=NULL); uni_hash_t *new_h=NULL;
    void *cue_data=NULL; lluint i,new_size,position;
    cue_t *temp_cue=NULL; pair_t *temp_pair=NULL;
    avl_tree_t *temp_tree=NULL; list_t *temp_list=NULL;
    void **new_array=NULL; void **old_array=NULL;
    new_size= hash_table_next_prime((t->size) * 2);
    new_array=(void **)malloc(new_size*sizeof(void *));
    assert(new_array!=NULL); new_h=uni_hash_create(new_size,20);

    for (i=0;i<new_size;i++)
    {
        if (t->type==CHAIN_LIST)
        {
            new_array[i]= list_create(hash_table_compare_pairs, hash_table_print_pair, hash_table_deallocate_pair);
        }
        else if (t->type==CHAIN_TREE)
        {
            new_array[i]= avl_tree_create(hash_table_compare_pairs, hash_table_print_pair, hash_table_deallocate_pair);
        }
        else {}
    }

    for (i=0;i<t->size;i++)
    {
        if (t->type==CHAIN_LIST)
        {
            temp_list=t->A[i];
            temp_list->destroy=NULL;

            while (!list_is_empty(temp_list))
            {
                temp_pair= list_get_head(temp_list);
                temp_cue= pair_get_cue(temp_pair);
                cue_data=cue_get(temp_cue);
                position=t->hash(new_h,cue_data);
                list_push(new_array[position],temp_pair);
                list_remove_head(temp_list);
            }

            list_free(temp_list);
        }
        else if (t->type==CHAIN_TREE)
        {
            temp_tree=t->A[i];
            temp_tree->destroy=NULL;

            while (!avl_tree_is_empty(temp_tree))
            {
                temp_pair= avl_tree_get_root(temp_tree);
                temp_cue= pair_get_cue(temp_pair);
                cue_data=cue_get(temp_cue);
                position=t->hash(new_h,cue_data);
                avl_tree_insert(new_array[position], temp_pair);
                avl_tree_remove_root(temp_tree);
            }

            avl_tree_free(temp_tree);
        }
    }

    uni_hash_free(t->hfunc); t->hfunc=new_h;
    old_array=t->A; free(old_array);
    t->A=new_array; t->size=new_size;
    hash_table_load_factor(t);
}



hash_table_t *hash_table_create(hash_table_hash_fn hash, int chain_type)
{
    lluint i;
    hash_table_t *new_table=NULL;
    assert(hash!=NULL);
    assert(chain_type==CHAIN_LIST || chain_type==CHAIN_TREE);
    new_table=(hash_table_t *)malloc(sizeof(*new_table));
    assert(new_table!=NULL);
    new_table->A=(void **)malloc(INITIAL_SIZE*sizeof(void *));
    assert(new_table->A!=NULL);
    new_table->type=chain_type;

    for (i=0;i<INITIAL_SIZE;i++)
    {
        if (new_table->type==CHAIN_LIST)
        {
            new_table->A[i]=list_create(
                    hash_table_compare_pairs,
                    hash_table_print_pair,
                    hash_table_deallocate_pair);
        }
        else if (new_table->type==CHAIN_TREE)
        {
            new_table->A[i]=avl_tree_create(
                    hash_table_compare_pairs,
                    hash_table_print_pair,
                    hash_table_deallocate_pair);
        }
    }

    new_table->n=0;
    new_table->size=INITIAL_SIZE;
    new_table->lf=(double )(new_table->n)/(new_table->size);
    new_table->hfunc=uni_hash_create(INITIAL_SIZE,20);
    new_table->hash=hash;
    return new_table;
}

void hash_table_insert(hash_table_t *t, pair_t *p)
{
    lluint position;
    double load_factor;
    load_factor= hash_table_load_factor(t);
    if (load_factor>0.85) { hash_table_rehash(t); }
    cue_t *temp_cue=NULL; void *cue_data=NULL;
    assert(t!=NULL && p!=NULL);
    temp_cue= pair_get_cue(p);
    cue_data=cue_get(temp_cue);
    if (hash_table_lookup(t, cue_data) == 1) { return; }
    position=t->hash(t->hfunc,cue_data);

    if (t->type==CHAIN_LIST)
    {
        list_push(t->A[position],p);
        t->n=t->n+1;
    }
    else if (t->type==CHAIN_TREE)
    {
        avl_tree_insert(t->A[position], p);
        t->n=t->n+1;
    }

    hash_table_load_factor(t);
}


int hash_table_lookup(hash_table_t *t, void *key)
{
    assert(t!=NULL);
    int chain_query; lluint position;
    pair_t temp_pair; cue_t temp_cue;
    position=t->hash(t->hfunc,key);
    temp_cue.cue=key;
    temp_pair.k=&temp_cue;

    if (t->type==CHAIN_LIST)
    {
        chain_query= list_has_elem(t->A[position], &temp_pair);
        return (chain_query>-1 ? 1 : 0);
    }
    else if (t->type==CHAIN_TREE)
    {
        chain_query= avl_tree_search(t->A[position], &temp_pair);
        return chain_query;
    }
    else
    {
        return 0;
    }
}


void hash_table_remove(hash_table_t *t, void *key)
{
    assert(t!=NULL);
    pair_t temp_pair; cue_t temp_cue;
    lluint position,chain_pos;
    position=t->hash(t->hfunc,key);
    if (hash_table_lookup(t, key) == 0) { return; }
    temp_cue.cue=key;
    temp_pair.k=&temp_cue;

    if (t->type==CHAIN_LIST)
    {
        chain_pos= list_has_elem(t->A[position], &temp_pair);
        list_remove_at(t->A[position], chain_pos);
        t->n=t->n-1;
    }
    else if (t->type==CHAIN_TREE)
    {
        avl_tree_remove(t->A[position], &temp_pair);
        t->n=t->n-1;
    }

    hash_table_load_factor(t);
}


void *hash_table_get_value(hash_table_t *t, void *key)
{
    assert(t!=NULL);
    cue_t temp_cue; pair_t temp_pair;
    lluint position,chain_query;
    pair_t *returned_pair=NULL;
    value_t *returned_value=NULL;
    if (hash_table_lookup(t, key) == 0) { return NULL; }
    position=t->hash(t->hfunc,key);
    temp_cue.cue=key;
    temp_pair.k=&temp_cue;

    if (t->type==CHAIN_LIST)
    {
        chain_query= list_has_elem(t->A[position], &temp_pair);
        returned_pair= list_get_at(t->A[position], chain_query);
        returned_value= pair_get_value(returned_pair);
        return value_get(returned_value);
    }
    else if (t->type==CHAIN_TREE)
    {
        returned_pair= avl_tree_get_elem(t->A[position], &temp_pair);
        returned_value= pair_get_value(returned_pair);
        return value_get(returned_value);
    }
    else
    {
        return NULL;
    }
}


void hash_table_change_value(hash_table_t *t, void *key, void *value)
{
    assert(t!=NULL);
    lluint position,chain_query;
    pair_t *returned_pair=NULL;
    cue_t temp_cue; pair_t temp_pair;
    value_t *old_value=NULL,*new_value=NULL;
    if (hash_table_lookup(t, key) == 0) { return; }
    position=t->hash(t->hfunc,key);
    temp_cue.cue=key;
    temp_pair.k=&temp_cue;


    if (t->type==CHAIN_LIST)
    {
        chain_query= list_has_elem(t->A[position], &temp_pair);
        returned_pair= list_get_at(t->A[position], chain_query);
        old_value= pair_get_value(returned_pair);
        new_value=value_create(value,old_value->cmp,old_value->print,old_value->destroy);
        pair_change_value(returned_pair, new_value);
    }
    else if (t->type==CHAIN_TREE)
    {
        returned_pair= avl_tree_get_elem(t->A[position], &temp_pair);
        old_value= pair_get_value(returned_pair);
        new_value=value_create(value,old_value->cmp,old_value->print,old_value->destroy);
        pair_change_value(returned_pair, new_value);
    }
}


void hash_table_print(hash_table_t *t)
{
    lluint i;
    assert(t!=NULL);

    for (i=0;i<t->size;i++)
    {
        printf("index %lld:",i);

        if (t->type==CHAIN_LIST)
        {
            list_print(t->A[i]);
        }
        else if (t->type==CHAIN_TREE)
        {
            avl_tree_print(t->A[i]);
        }
    }
}


void hash_table_free(hash_table_t *t)
{
    lluint i;
    assert(t!=NULL);

    for (i=0;i<t->size;i++)
    {
        if (t->type==CHAIN_LIST)
        {
            list_free(t->A[i]);
        }
        else if (t->type==CHAIN_TREE)
        {
            avl_tree_free(t->A[i]);
        }
    }

    free(t->A); t->A=NULL;
    uni_hash_free(t->hfunc);
    t->hfunc=NULL;
    free(t); t=NULL;
}