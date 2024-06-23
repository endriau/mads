#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mads/data_structures/pair.h>


mads_cue_t *mads_cue_create(void *cue, const mads_cue_compare_fn cmp, const mads_cue_print_fn print, const mads_cue_destroy_fn destroy)
{
    mads_cue_t *new_cue = NULL;
    assert(cmp != NULL && print != NULL);
    new_cue = (mads_cue_t *)malloc(sizeof(mads_cue_t));
    assert(new_cue!=NULL);
    new_cue->cue = cue;
    new_cue->cmp = cmp;
    new_cue->print = print;
    new_cue->destroy = destroy;
    return new_cue;
}


void *mads_cue_get(const mads_cue_t *k)
{
    assert(k != NULL);
    return k->cue;
}


int mads_cue_compare_to(const mads_cue_t *k, const void *data)
{
    assert(k != NULL);
    const int result = k->cmp(k->cue, data);
    return result;
}


void mads_cue_print(const mads_cue_t *k)
{
    assert(k != NULL);
    k->print(k->cue);
}


void cue_free(mads_cue_t *k)
{
    assert(k != NULL);
    if (k->destroy != NULL) { k->destroy(k->cue); }
    k->cmp = NULL;
    k->print = NULL;
    k->destroy = NULL;
    free(k);
    k = NULL;
}


mads_value_t *mads_value_create(void *value, const mads_value_compare_fn cmp, const mads_value_print_fn print, const mads_value_destroy_fn destroy)
{
    mads_value_t *new_value = NULL;
    assert(cmp != NULL && print != NULL);
    new_value = (mads_value_t *)malloc(sizeof(mads_value_t));
    assert(new_value!=NULL);
    new_value->value = value;
    new_value->cmp = cmp;
    new_value->print = print;
    new_value->destroy = destroy;
    return new_value;
}


void *mads_value_get(const mads_value_t *v)
{
    assert(v != NULL);
    return v->value;
}


int mads_value_compare_to(const mads_value_t *v, const void *data)
{
    assert(v != NULL);
    const int result = v->cmp(v->value, data);
    return result;
}

void mads_value_print(const mads_value_t *v)
{
    assert(v != NULL);
    v->print(v->value);
}

void mads_value_free(mads_value_t *v)
{
    assert(v != NULL);
    if (v->destroy != NULL) { v->destroy(v->value); }
    v->cmp = NULL;
    v->print = NULL;
    v->destroy = NULL;
    free(v);
    v = NULL;
}

mads_pair_t *mads_pair_create(mads_cue_t *k, mads_value_t *v)
{
    mads_pair_t *new_pair = NULL;
    assert(k != NULL && v != NULL);
    new_pair = (mads_pair_t *)malloc(sizeof(mads_pair_t));
    assert(new_pair!=NULL);
    new_pair->k = k;
    new_pair->v = v;
    return new_pair;
}

mads_cue_t *mads_pair_get_cue(const mads_pair_t *p)
{
    assert(p != NULL);
    return p->k;
}


mads_value_t *mads_pair_get_value(const mads_pair_t *p)
{
    assert(p != NULL);
    return p->v;
}


void mads_pair_change_cue(mads_pair_t *p, mads_cue_t *new_k)
{
    mads_cue_t *old_cue = NULL;
    assert(p != NULL && new_k != NULL);
    old_cue = mads_pair_get_cue(p);
    cue_free(old_cue);
    p->k = new_k;
}

void mads_pair_change_value(mads_pair_t *p, mads_value_t *new_v)
{
    mads_value_t *old_value = NULL;
    assert(p != NULL && new_v != NULL);
    old_value = mads_pair_get_value(p);
    mads_value_free(old_value);
    p->v = new_v;
}


void mads_pair_print(const mads_pair_t *p)
{
    assert(p != NULL);
    const mads_cue_t *temp_cue = NULL;
    const mads_value_t *temp_value = NULL;
    temp_cue = mads_pair_get_cue(p);
    temp_value = mads_pair_get_value(p);
    printf("{ ");
    mads_cue_print(temp_cue);
    printf(" : ");
    mads_value_print(temp_value);
    printf(" }");
}


void mads_pair_free(mads_pair_t *p)
{
    assert(p != NULL);
    mads_value_free(mads_pair_get_value(p));
    cue_free(mads_pair_get_cue(p));
    free(p);
    p = NULL;
}
