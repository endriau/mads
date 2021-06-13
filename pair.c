//
// Created by p0int3r on 6/12/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pair.h"


cue_t *cue_create(void *cue, cue_compare_fn cmp, cue_print_fn print, cue_destroy_fn destroy)
{
    cue_t *new_cue=NULL;
    assert(cmp!=NULL && print!=NULL);
    new_cue=(cue_t *)malloc(sizeof(*new_cue));
    assert(new_cue!=NULL);
    new_cue->cue=cue;
    new_cue->cmp=cmp;
    new_cue->print=print;
    new_cue->destroy=destroy;
    return new_cue;
}


void *cue_get(cue_t *k)
{
    assert(k!=NULL);
    return k->cue;
}


int cue_compare_to(cue_t *k, void *data)
{
    int result;
    assert(k!=NULL);
    result=k->cmp(k->cue,data);
    return result;
}


void cue_print(cue_t *k)
{
    assert(k!=NULL);
    k->print(k->cue);
}


void cue_free(cue_t *k)
{
    assert(k!=NULL);
    if (k->destroy!=NULL) { k->destroy(k->cue); }
    k->cmp=NULL;
    k->print=NULL;
    k->destroy=NULL;
    free(k); k=NULL;
}


value_t *value_create(void *value, value_compare_fn cmp, value_print_fn print, value_destroy_fn destroy)
{
    value_t *new_value=NULL;
    assert(cmp!=NULL && print!=NULL);
    new_value=(value_t *)malloc(sizeof(*new_value));
    assert(new_value!=NULL);
    new_value->value=value;
    new_value->cmp=cmp;
    new_value->print=print;
    new_value->destroy=destroy;
    return new_value;
}


void *value_get(value_t *v)
{
    assert(v!=NULL);
    return v->value;
}


int value_compare_to(value_t *v, void *data)
{
    int result;
    assert(v!=NULL);
    result=v->cmp(v->value,data);
    return result;
}

void value_print(value_t *v)
{
    assert(v!=NULL);
    v->print(v->value);
}

void value_free(value_t *v)
{
    assert(v!=NULL);
    if (v->destroy!=NULL) { v->destroy(v->value); }
    v->cmp=NULL;
    v->print=NULL;
    v->destroy=NULL;
    free(v); v=NULL;
}

pair_t  *pair_create(cue_t *k,value_t *v)
{
    pair_t *new_pair=NULL;
    assert(k!=NULL && v!=NULL);
    new_pair=(pair_t *)malloc(sizeof(*new_pair));
    assert(new_pair!=NULL);
    new_pair->k=k;
    new_pair->v=v;
    return new_pair;
}

cue_t *pair_get_cue(pair_t *p)
{
    assert(p!=NULL);
    return p->k;
}


value_t *pair_get_value(pair_t *p)
{
    assert(p!=NULL);
    return p->v;
}


void pair_change_cue(pair_t *p, cue_t *new_k)
{
    cue_t *old_cue=NULL;
    assert(p!=NULL && new_k!=NULL);
    old_cue= pair_get_cue(p);
    cue_free(old_cue);
    p->k=new_k;
}

void pair_change_value(pair_t *p, value_t *new_v)
{
    value_t *old_value=NULL;
    assert(p!=NULL && new_v!=NULL);
    old_value= pair_get_value(p);
    value_free(old_value);
    p->v=new_v;
}


void pair_print(pair_t *p)
{
    assert(p!=NULL);
    cue_t *temp_cue=NULL;
    value_t *temp_value=NULL;
    temp_cue= pair_get_cue(p);
    temp_value= pair_get_value(p);
    printf("{ ");
    cue_print(temp_cue);
    printf(" : ");
    value_print(temp_value);
    printf(" }");
}


void pair_free(pair_t *p)
{
    assert(p!=NULL);
    value_free(pair_get_value(p));
    cue_free(pair_get_cue(p));
    free(p); p=NULL;
}