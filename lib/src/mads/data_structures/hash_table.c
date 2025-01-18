// ReSharper disable CppDFAConstantConditions
// ReSharper disable CppDFAUnreachableCode
// ReSharper disable CppRedundantElseKeywordInsideCompoundStatement
// ReSharper disable CppRedundantElseKeyword


// ReSharper disable CppDFANullDereference
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <mads/data_structures/list.h>
#include <mads/data_structures/avl_tree.h>
#include <mads/data_structures/hash_table.h>


static int hash_table_compare_pairs(const void *p1, const void *p2)
{
    const mads_pair_t *pp1 = NULL;
    const mads_pair_t *pp2 = NULL;
    const mads_cue_t *c1 = NULL;
    const mads_cue_t *c2 = NULL;
    pp1 = (mads_pair_t *)p1;
    pp2 = (mads_pair_t *)p2;
    c1 = mads_pair_get_cue(pp1);
    c2 = mads_pair_get_cue(pp2);
    return mads_cue_compare_to(c1, mads_cue_get(c2));
}


static void hash_table_print_pair(const void *p)
{
    const mads_pair_t *pair = NULL;
    pair = (mads_pair_t *)p;
    mads_pair_print(pair);
}


static void hash_table_deallocate_pair(void *p)
{
    mads_pair_t *pair = NULL;
    pair = (mads_pair_t *)p;
    mads_pair_free(pair);
    pair = NULL;
}


static double hash_table_load_factor(mads_hash_table_t *t)
{
    assert(t != NULL);
    const double lf = (double)t->n / t->size;
    t->load_factor = lf;
    return lf;
}


static int hash_table_is_prime(const unsigned long long int n)
{
    unsigned long long int isprime = 1;
    if (n < 2) { return 0; }

    for (unsigned long long int divisor = 2; divisor * divisor <= n; divisor++)
    {
        if (n % divisor == 0)
        {
            isprime = 0;
            break;
        }
    }

    return isprime;
}


static unsigned long long int hash_table_next_prime(const unsigned long long int n)
{
    assert(n != 0);
    unsigned long long int step = n + 1;

    while (hash_table_is_prime(step) == 0)
    {
        step++;
    }

    return step;
}


static void hash_table_rehash(mads_hash_table_t *t)
{
    assert(t != NULL);
    mads_uni_hash_t *new_h = NULL;
    const void *cue_data = NULL;
    unsigned long long int i, position;
    const mads_cue_t *temp_cue = NULL;
    mads_pair_t *temp_pair = NULL;
    mads_avl_tree_t *temp_tree = NULL;
    mads_list_t *temp_list = NULL;
    void **new_array = NULL;
    void **old_array = NULL;
    const unsigned long long int new_size = hash_table_next_prime((t->size) * 2);
    new_array = (void **)malloc(new_size * sizeof(void *));
    assert(new_array != NULL);
    new_h = mads_uni_hash_create(new_size, 20);

    for (i = 0; i < new_size; i++)
    {
        if (t->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
        {
            new_array[i] = mads_list_create(
                hash_table_compare_pairs,
                hash_table_print_pair,
                hash_table_deallocate_pair);
        }
        else if (t->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
        {
            new_array[i] = mads_avl_tree_create(
                hash_table_compare_pairs,
                hash_table_print_pair,
                hash_table_deallocate_pair);
        }
        else {}
    }

    for (i = 0; i < t->size; i++)
    {
        if (t->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
        {
            temp_list = t->A[i];
            temp_list->destroy = NULL;

            while (!mads_list_is_empty(temp_list))
            {
                temp_pair = mads_list_get_head(temp_list);
                temp_cue = mads_pair_get_cue(temp_pair);
                cue_data = mads_cue_get(temp_cue);
                position = t->hash(new_h, cue_data);
                mads_list_push(new_array[position], temp_pair);
                mads_list_remove_head(temp_list);
            }

            mads_list_free(&temp_list);
        }
        else if (t->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
        {
            temp_tree = t->A[i];
            temp_tree->destroy = NULL;

            while (!mads_avl_tree_is_empty(temp_tree))
            {
                temp_pair = mads_avl_tree_get_root(temp_tree);
                temp_cue = mads_pair_get_cue(temp_pair);
                cue_data = mads_cue_get(temp_cue);
                position = t->hash(new_h, cue_data);
                mads_avl_tree_insert(new_array[position], temp_pair);
                mads_avl_tree_remove_root(temp_tree);
            }

            mads_avl_tree_free(temp_tree);
        }
    }

    mads_uni_hash_free(t->hfunc);
    t->hfunc = new_h;
    old_array = t->A;
    free(old_array);
    t->A = new_array;
    t->size = new_size;
    hash_table_load_factor(t);
}


mads_hash_table_t *mads_hash_table_create(const mads_hash_table_hash_fn hash, const int chain_type)
{
    mads_hash_table_t *new_table = NULL;
    assert(hash != NULL);
    assert(chain_type == MADS_HASH_TABLE_CHAIN_LIST || chain_type == MADS_HASH_TABLE_CHAIN_TREE);
    new_table = (mads_hash_table_t *)malloc(sizeof(*new_table));
    assert(new_table != NULL);
    new_table->A = (void **)malloc(MADS_HASH_TABLE_INITIAL_SIZE * sizeof(void *));
    assert(new_table->A != NULL);
    new_table->chain_type = chain_type;

    for (unsigned long long int i = 0; i < MADS_HASH_TABLE_INITIAL_SIZE; i++)
    {
        if (new_table->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
        {
            new_table->A[i] = mads_list_create(
                hash_table_compare_pairs,
                hash_table_print_pair,
                hash_table_deallocate_pair);
        }
        else if (new_table->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
        {
            new_table->A[i] = mads_avl_tree_create(
                hash_table_compare_pairs,
                hash_table_print_pair,
                hash_table_deallocate_pair);
        }
    }

    new_table->n = 0;
    new_table->size = MADS_HASH_TABLE_INITIAL_SIZE;
    new_table->load_factor = (double)(new_table->n) / (new_table->size);
    new_table->hfunc = mads_uni_hash_create(MADS_HASH_TABLE_INITIAL_SIZE, 20);
    new_table->hash = hash;
    return new_table;
}

void mads_hash_table_insert(mads_hash_table_t *t, mads_pair_t *p)
{
    const double load_factor = hash_table_load_factor(t);
    if (load_factor > 0.85) { hash_table_rehash(t); }
    const mads_cue_t *temp_cue = NULL;
    void *cue_data = NULL;
    assert(t != NULL && p != NULL);
    temp_cue = mads_pair_get_cue(p);
    cue_data = mads_cue_get(temp_cue);
    if (mads_hash_table_lookup(t, cue_data) == 1) { return; }
    const unsigned long long int position = t->hash(t->hfunc, cue_data);

    if (t->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
    {
        mads_list_push(t->A[position], p);
        t->n = t->n + 1;
    }
    else if (t->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
    {
        mads_avl_tree_insert(t->A[position], p);
        t->n = t->n + 1;
    }

    hash_table_load_factor(t);
}


int mads_hash_table_lookup(const mads_hash_table_t *t, void *key)
{
    assert(t != NULL);
    int chain_query;
    mads_pair_t temp_pair;
    mads_cue_t temp_cue;
    const unsigned long long int position = t->hash(t->hfunc, key);
    temp_cue.cue = key;
    temp_pair.k = &temp_cue;

    if (t->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
    {
        chain_query = mads_list_has_elem(t->A[position], &temp_pair);
        return (chain_query > -1 ? 1 : 0);
    }
    else if (t->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
    {
        chain_query = mads_avl_tree_search(t->A[position], &temp_pair);
        return chain_query;
    }
    else
    {
        return 0;
    }
}


void mads_hash_table_remove(mads_hash_table_t *t, void *key)
{
    assert(t != NULL);
    mads_pair_t temp_pair;
    mads_cue_t temp_cue;
    const unsigned long long int position = t->hash(t->hfunc, key);
    if (mads_hash_table_lookup(t, key) == 0) { return; }
    temp_cue.cue = key;
    temp_pair.k = &temp_cue;

    if (t->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
    {
        const unsigned long long int chain_pos = mads_list_has_elem(t->A[position], &temp_pair);
        mads_list_remove_at(t->A[position], chain_pos);
        t->n = t->n - 1;
    }
    else if (t->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
    {
        mads_avl_tree_remove(t->A[position], &temp_pair);
        t->n = t->n - 1;
    }

    hash_table_load_factor(t);
}


void *mads_hash_table_get_value(const mads_hash_table_t *t, void *key)
{
    assert(t != NULL);
    mads_cue_t temp_cue;
    mads_pair_t temp_pair;
    const mads_pair_t *returned_pair = NULL;
    const mads_value_t *returned_value = NULL;
    if (mads_hash_table_lookup(t, key) == 0) { return NULL; }
    const unsigned long long int position = t->hash(t->hfunc, key);
    temp_cue.cue = key;
    temp_pair.k = &temp_cue;

    if (t->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
    {
        const unsigned long long int chain_query = mads_list_has_elem(t->A[position], &temp_pair);
        returned_pair = mads_list_get_at(t->A[position], chain_query);
        returned_value = mads_pair_get_value(returned_pair);
        return mads_value_get(returned_value);
    }
    else if (t->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
    {
        returned_pair = mads_avl_tree_get_elem(t->A[position], &temp_pair);
        returned_value = mads_pair_get_value(returned_pair);
        return mads_value_get(returned_value);
    }
    else
    {
        return NULL;
    }
}


void mads_hash_table_change_value(const mads_hash_table_t *t, void *key, void *value)
{
    assert(t != NULL);
    mads_pair_t *returned_pair = NULL;
    mads_cue_t temp_cue;
    mads_pair_t temp_pair;
    const mads_value_t *old_value = NULL;
    mads_value_t *new_value = NULL;
    if (mads_hash_table_lookup(t, key) == 0) { return; }
    const unsigned long long int position = t->hash(t->hfunc, key);
    temp_cue.cue = key;
    temp_pair.k = &temp_cue;


    if (t->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
    {
        const unsigned long long int chain_query = mads_list_has_elem(t->A[position], &temp_pair);
        returned_pair = mads_list_get_at(t->A[position], chain_query);
        old_value = mads_pair_get_value(returned_pair);
        new_value = mads_value_create(value, old_value->comparator, old_value->printer, old_value->destructor);
        mads_pair_change_value(returned_pair, new_value);
    }
    else if (t->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
    {
        returned_pair = mads_avl_tree_get_elem(t->A[position], &temp_pair);
        old_value = mads_pair_get_value(returned_pair);
        new_value = mads_value_create(value, old_value->comparator, old_value->printer, old_value->destructor);
        mads_pair_change_value(returned_pair, new_value);
    }
}


void mads_hash_table_print(const mads_hash_table_t *t)
{
    assert(t != NULL);

    for (unsigned long long int i = 0; i < t->size; i++)
    {
        printf("index %lld:", i);

        if (t->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
        {
            mads_list_print(t->A[i]);
        }
        else if (t->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
        {
            mads_avl_tree_print(t->A[i]);
        }
    }
}


void mads_hash_table_free(mads_hash_table_t **t)
{
    assert(t != NULL);

    for (unsigned long long int i = 0; i < (*t)->size; i++)
    {
        if ((*t)->chain_type == MADS_HASH_TABLE_CHAIN_LIST)
        {

            mads_list_free((mads_list_t **)&(*t)->A[i]);
        }
        else if ((*t)->chain_type == MADS_HASH_TABLE_CHAIN_TREE)
        {
            mads_avl_tree_free((*t)->A[i]);
        }
    }

    free((*t)->A); (*t)->A = NULL;
    mads_uni_hash_free((*t)->hfunc);
    (*t)->hfunc = NULL;
    free(*t); *t = NULL;
}
