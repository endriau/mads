//
// Created by p0int3r on 6/13/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "edge.h"



edge_t *edge_create(void *w, void *ep, edge_compare_fn cmp, edge_print_fn print, edge_destroy_fn destroy)
{
    edge_t *new_edge=NULL;
    assert(cmp!=NULL && print!=NULL);
    new_edge=(edge_t *)malloc(sizeof(*new_edge));
    assert(new_edge!=NULL);
    new_edge->weight=w;
    new_edge->endpoint=ep;
    new_edge->cmp=cmp;
    new_edge->print=print;
    new_edge->destroy=destroy;
    return new_edge;
}



void *edge_get_weight(edge_t *edge)
{
    assert(edge!=NULL);
    return edge->weight;
}


void *edge_get_end_point(edge_t *edge)
{
    assert(edge!=NULL);
    return edge->endpoint;
}


void edge_change_weight(edge_t *edge, void *new_w)
{
    void *old_w=NULL;
    assert(edge!=NULL);
    old_w= edge_get_weight(edge);

    if (edge->destroy!=NULL)
    {
        edge->destroy(old_w);
        old_w=NULL;
    }

    edge->weight=new_w;
}


void edge_change_end_point(edge_t *edge, void *new_ep)
{
    assert(edge!=NULL);
    edge->endpoint=new_ep;
}



int edge_compare_to(edge_t *edge, void *data)
{
    int result;
    assert(edge!=NULL);
    result=edge->cmp(edge->weight,data);
    return result;
}


void edge_print(edge_t *edge)
{
    void *ep=NULL;
    assert(edge!=NULL);
    printf("( weight = ");
    edge->print(edge->weight);
    ep= edge_get_end_point(edge);
    printf(" ---> endpoint = %p )",ep);
}



void edge_free(edge_t *edge)
{
    assert(edge!=NULL);

    if (edge->destroy!=NULL)
    {
        edge->destroy(edge->weight);
        edge->weight=NULL;
    }
    else
    {
        edge->weight=NULL;
    }

    edge->endpoint=NULL;
    free(edge); edge=NULL;
}

