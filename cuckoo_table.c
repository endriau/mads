//
// Created by p0int3r on 6/13/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cuckoo_table.h"


static double cuckoo_table_load_factor(cuckoo_table_t *t)
{
    double lf;
    assert(t!=NULL);
    lf=(double )(t->n)/(t->size*2);
    t->lf=lf; return lf;
}


static int cuckoo_table_is_prime(lluint n)
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


static lluint cuckoo_table_next_prime(lluint n)
{
    lluint step;
    assert(n!=0);
    step=n+1;

    while (cuckoo_table_is_prime(step) == 0)
    {
        step++;
    }

    return step;
}

static void cuckoo_table_rehash(cuckoo_table_t *c)
{
    pair_t *temp_pair=NULL;
    lluint double_size,i,old_size;
    void **old_T1=NULL,**old_T2=NULL;
    old_T1=c->T1; old_T2=c->T2;
    c->T1=NULL; c->T2=NULL;
    old_size=c->size;
    double_size= cuckoo_table_next_prime(c->size * 2);
    c->T1=(void **)malloc(double_size*sizeof(void *));
    assert(c->T1!=NULL);
    c->T2=(void **)malloc(double_size*sizeof(void *));
    assert(c->T2!=NULL);

    for (i=0;i<double_size;i++)
    {
        c->T1[i]=NULL;
        c->T2[i]=NULL;
    }

    c->size=double_size; c->n=0;
    uni_hash_free(c->hfunc1); c->hfunc1=NULL;
    uni_hash_free(c->hfunc2); c->hfunc2=NULL;
    c->hfunc1=uni_hash_create(double_size,20);
    c->hfunc2=uni_hash_create(double_size,20);

    for (i=0;i<old_size;i++)
    {
        temp_pair=old_T1[i];
        old_T1[i]=NULL;

        if (temp_pair!=NULL)
        {
            cuckoo_table_insert(c, temp_pair);
        }

        temp_pair=old_T2[i];
        old_T2[i]=NULL;

        if (temp_pair!=NULL)
        {
            cuckoo_table_insert(c, temp_pair);
        }
    }

    free(old_T1); old_T1=NULL;
    free(old_T2); old_T2=NULL;
}


cuckoo_table_t *cuckoo_table_create(cuckoo_hash_fn hash)
{
    lluint i;
    cuckoo_table_t *new_table=NULL;
    assert(hash!=NULL);
    new_table=(cuckoo_table_t *)malloc(sizeof(*new_table));
    assert(new_table!=NULL);
    new_table->T1=(void **)malloc(INITIAL_CUCKOO_SIZE*sizeof(void *));
    assert(new_table->T1!=NULL);
    new_table->T2=(void **)malloc(INITIAL_CUCKOO_SIZE*sizeof(void *));
    new_table->n=0; new_table->size=INITIAL_CUCKOO_SIZE;

    for (i=0;i<INITIAL_CUCKOO_SIZE;i++)
    {
        new_table->T1[i]=NULL;
        new_table->T2[i]=NULL;
    }

    new_table->lf=(double )(new_table->n)/(new_table->size*2);
    new_table->hfunc1=uni_hash_create(INITIAL_CUCKOO_SIZE,20);
    new_table->hfunc2=uni_hash_create(INITIAL_CUCKOO_SIZE,20);
    new_table->hash=hash;
    return new_table;
}


void cuckoo_table_insert(cuckoo_table_t *c, pair_t *p)
{
    lluint position1,position2;
    assert(c!=NULL && p!=NULL); int i;
    pair_t *swap_pair=NULL,*temp_pair=NULL;
    cue_t *temp_cue=NULL; void *cue_data=NULL;
    temp_cue= pair_get_cue(p); cue_data=cue_get(temp_cue);
    if (cuckoo_table_lookup(c, cue_data) == 1) { return; }
    temp_pair=p;

    for (i=0;i<MAX_LOOP_ITERATIONS;i++)
    {
        temp_cue= pair_get_cue(temp_pair);
        cue_data=cue_get(temp_cue);
        position1=c->hash(c->hfunc1,cue_data);
        swap_pair=c->T1[position1];

        if (swap_pair==NULL)
        {
            c->T1[position1]=temp_pair;
            c->n++;
            cuckoo_table_load_factor(c);
            return;
        }
        else
        {
            c->T1[position1]=temp_pair;
            temp_pair=swap_pair;
        }

        temp_cue= pair_get_cue(temp_pair);
        cue_data=cue_get(temp_cue);
        position2=c->hash(c->hfunc2,cue_data);
        swap_pair=c->T2[position2];

        if (swap_pair==NULL)
        {
            c->T2[position2]=temp_pair;
            c->n++;
            cuckoo_table_load_factor(c);
            return;
        }
        else
        {
            c->T2[position2]=temp_pair;
            temp_pair=swap_pair;
        }
    }

    cuckoo_table_rehash(c);
    cuckoo_table_insert(c, temp_pair);
}


int cuckoo_table_lookup(cuckoo_table_t *c, void *key)
{
    assert(c!=NULL);
    int query1,query2;
    lluint position1,position2;
    pair_t *temp_pair1=NULL,*temp_pair2=NULL;
    cue_t *temp_cue1=NULL,*temp_cue2=NULL;
    position1=c->hash(c->hfunc1,key);
    position2=c->hash(c->hfunc2,key);
    temp_pair1=c->T1[position1];
    temp_pair2=c->T2[position2];

    if (temp_pair1!=NULL)
    {
        temp_cue1= pair_get_cue(temp_pair1);
        query1= cue_compare_to(temp_cue1, key);
        if (query1==0) { return 1; }
    }

    if (temp_pair2!=NULL)
    {
        temp_cue2= pair_get_cue(temp_pair2);
        query2= cue_compare_to(temp_cue2, key);
        if (query2==0) { return 1; }
    }

    return 0;
}


void cuckoo_table_remove(cuckoo_table_t *c, void *key)
{
    assert(c!=NULL);
    int query1,query2;
    lluint position1,position2;
    pair_t *temp_pair1=NULL,*temp_pair2=NULL;
    cue_t *temp_cue1=NULL,*temp_cue2=NULL;
    if (cuckoo_table_lookup(c, key) == 0) { return; }
    position1=c->hash(c->hfunc1,key);
    position2=c->hash(c->hfunc2,key);
    temp_pair1=c->T1[position1];
    temp_pair2=c->T2[position2];

    if (temp_pair1!=NULL)
    {
        temp_cue1= pair_get_cue(temp_pair1);
        query1= cue_compare_to(temp_cue1, key);

        if (query1==0)
        {
            pair_free(temp_pair1);
            temp_pair1=NULL;
            c->T1[position1]=NULL;
            c->n--;
            cuckoo_table_load_factor(c);
            return;
        }

    }

    if (temp_pair2!=NULL)
    {
        temp_cue2= pair_get_cue(temp_pair2);
        query2= cue_compare_to(temp_cue2, key);

        if (query2==0)
        {
            pair_free(temp_pair2);
            temp_pair2=NULL;
            c->T2[position2]=NULL;
            c->n--;
            cuckoo_table_load_factor(c);
            return;
        }
    }
}



void *cuckoo_table_get_value(cuckoo_table_t *c, void *key)
{
    assert(c!=NULL);
    int query1,query2;
    lluint position1,position2;
    pair_t *temp_pair1=NULL,*temp_pair2=NULL;
    cue_t *temp_cue1=NULL,*temp_cue2=NULL;
    value_t *temp_value1=NULL,*temp_value2=NULL;
    if (cuckoo_table_lookup(c, key) == 0) { return NULL; }
    position1=c->hash(c->hfunc1,key);
    position2=c->hash(c->hfunc2,key);
    temp_pair1=c->T1[position1];
    temp_pair2=c->T2[position2];

    if (temp_pair1!=NULL)
    {
        temp_cue1= pair_get_cue(temp_pair1);
        query1= cue_compare_to(temp_cue1, key);
        if (query1==0)
        {
            temp_value1= pair_get_value(temp_pair1);
            return value_get(temp_value1);
        }
    }

    if (temp_pair2!=NULL)
    {
        temp_cue2= pair_get_cue(temp_pair2);
        query2= cue_compare_to(temp_cue2, key);
        if (query2==0)
        {
            temp_value2= pair_get_value(temp_pair2);
            return value_get(temp_value2);
        }
    }

    return NULL;
}



void cuckoo_table_change_value(cuckoo_table_t *c, void *key, void *value)
{
    assert(c!=NULL);
    int query1,query2;
    lluint position1,position2;
    value_t *old_value=NULL,*new_value=NULL;
    pair_t *temp_pair1=NULL,*temp_pair2=NULL;
    cue_t *temp_cue1=NULL,*temp_cue2=NULL;
    if (cuckoo_table_lookup(c, key) == 0) { return; }
    position1=c->hash(c->hfunc1,key);
    position2=c->hash(c->hfunc2,key);
    temp_pair1=c->T1[position1];
    temp_pair2=c->T2[position2];

    if (temp_pair1!=NULL)
    {
        temp_cue1= pair_get_cue(temp_pair1);
        query1= cue_compare_to(temp_cue1, key);

        if (query1==0)
        {
            old_value= pair_get_value(temp_pair1);
            new_value=value_create(value,old_value->cmp,
                                   old_value->print,old_value->destroy);
            pair_change_value(temp_pair1, new_value);
            return;
        }
    }


    if (temp_pair2!=NULL)
    {
        temp_cue2= pair_get_cue(temp_pair2);
        query2= cue_compare_to(temp_cue2, key);

        if (query2==0)
        {
            old_value= pair_get_value(temp_pair2);
            new_value=value_create(value,old_value->cmp,
                                   old_value->print,old_value->destroy);
            pair_change_value(temp_pair2, new_value);
            return;
        }
    }
}


void cuckoo_table_print(cuckoo_table_t *c)
{
    lluint i;
    assert(c!=NULL);
    pair_t *temp_pair=NULL;
    printf("-------CUCKOO_HASH--------\n");
    printf("total = %lld, load factor = %.2lf\n",c->n,c->lf);
    printf("INDEX: TABLE_1, TABLE_2\n");

    for (i=0;i<c->size;i++)
    {
        printf("%lld:",i); temp_pair=c->T1[i];
        if (temp_pair!=NULL) { pair_print(temp_pair); }
        else { printf("____"); }
        printf(", "); temp_pair=c->T2[i];
        if (temp_pair!=NULL) { pair_print(temp_pair); }
        else { printf("____"); }
        printf("\n");
    }

    printf("-----------END-------------\n");
}



void cuckoo_table_free(cuckoo_table_t *c)
{
    lluint i;
    assert(c!=NULL);

    for (i=0;i<c->size;i++)
    {
        if (c->T1[i]!=NULL)
        {
            pair_free(c->T1[i]);
            c->T1[i]=NULL;
        }

        if (c->T2[i]!=NULL)
        {
            pair_free(c->T2[i]);
            c->T2[i]=NULL;
        }
    }

    free(c->T1); c->T1=NULL;
    free(c->T2); c->T2=NULL;
    uni_hash_free(c->hfunc1); c->hfunc1=NULL;
    uni_hash_free(c->hfunc2); c->hfunc2=NULL;
    c->n=0; c->size=0;
    free(c); c=NULL;
}
