//
// Created by p0int3r on 6/13/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vertex.h"


static int vertex_compare_edges(const void *e1, const void *e2)
{
    edge_t *ee1=NULL,*ee2=NULL;
    ee1=(edge_t *)e1;
    ee2=(edge_t *)e2;
    return edge_compare_to(ee1, ee2->weight);
}


static void vertex_print_edge(const void *e)
{
    edge_t *ee=NULL;
    ee=(edge_t *)e;
    edge_print(ee);
}


static void vertex_destroy_edge(void *e)
{
    edge_t *ee=NULL;
    ee=(edge_t *)e;
    edge_free(ee);
    ee=NULL;
}


vertex_t *vertex_create(void *ident, cuckoo_hash_fn hash, vertex_compare_fn cmp, vertex_print_fn print, vertex_destroy_fn destroy)
{
    vertex_t *new_vertex=NULL;
    assert(cmp!=NULL && print!=NULL);
    new_vertex=(vertex_t *)malloc(sizeof(*new_vertex));
    assert(new_vertex!=NULL);
    new_vertex->ident=ident;
    new_vertex->edges= cuckoo_table_create(hash);
    new_vertex->num_edges=0;
    new_vertex->inflow_edges=0;
    new_vertex->outflow_edges=0;
    new_vertex->previsit=0;
    new_vertex->postvisit=0;
    new_vertex->visited=0;
    new_vertex->cmp=cmp;
    new_vertex->print=print;
    new_vertex->destroy=destroy;
    return new_vertex;
}


void vertex_add_edge(vertex_t *vertex, void *ident, edge_t *edge)
{
    int query;
    cue_t *new_cue=NULL;
    value_t *new_value=NULL;
    pair_t *new_pair=NULL;
    assert(vertex!=NULL && edge!=NULL);
    new_cue=cue_create(ident,vertex->cmp,vertex->print,NULL);
    new_value= value_create(edge, vertex_compare_edges, vertex_print_edge, vertex_destroy_edge);
    new_pair=pair_create(new_cue,new_value);
    query= cuckoo_table_lookup(vertex->edges, ident);

    if (query==0)
    {
        cuckoo_table_insert(vertex->edges, new_pair);
        vertex->num_edges=vertex->edges->n;
        vertex->outflow_edges=vertex->edges->n;
    }
    else
    {
        pair_free(new_pair);
        new_pair=NULL;
    }
}



int vertex_has_edge(vertex_t *vertex, void *ident)
{
    int query;
    assert(vertex!=NULL);
    query= cuckoo_table_lookup(vertex->edges, ident);
    return query;
}


edge_t *vertex_get_edge(vertex_t *vertex, void *ident)
{
    assert(vertex!=NULL);
    return (edge_t *) cuckoo_table_get_value(vertex->edges, ident);
}


void vertex_remove_edge(vertex_t *vertex, void *ident)
{
    assert(vertex!=NULL);
    cuckoo_table_remove(vertex->edges, ident);
    vertex->num_edges=vertex->edges->n;
    vertex->outflow_edges=vertex->edges->n;
}


void vertex_visited(vertex_t *vertex)
{
    assert(vertex!=NULL);
    vertex->visited=1;
}


int vertex_is_visited(vertex_t *vertex)
{
    assert(vertex!=NULL);
    return vertex->visited;
}



edge_t **vertex_array_edges(vertex_t *vertex)
{
    lluint i,size,step;
    assert(vertex!=NULL);
    edge_t **edges_array=NULL;
    pair_t *temp_pair=NULL;
    value_t *temp_value=NULL;
    size=vertex->num_edges;
    if (size==0) { return NULL; }
    edges_array=(edge_t **)malloc(size*sizeof(**edges_array));
    assert(edges_array!=NULL); step=0;

    for (i=0;i<vertex->edges->size;i++)
    {
        temp_pair=vertex->edges->T1[i];
        if (temp_pair!=NULL)
        {
            temp_value= pair_get_value(temp_pair);
            edges_array[step++]=value_get(temp_value);
        }

        temp_pair=vertex->edges->T2[i];
        if (temp_pair!=NULL)
        {
            temp_value= pair_get_value(temp_pair);
            edges_array[step++]=value_get(temp_value);
        }
    }

    return edges_array;
}


void vertex_print(vertex_t *vertex)
{
    lluint i;
    pair_t *temp_pair=NULL;
    assert(vertex!=NULL);
    printf("[ vertex_id = ");
    vertex->print(vertex->ident);
    printf(", num_edges = %lld",vertex->num_edges);
    printf(", inflow_edges = %lld",vertex->inflow_edges);
    printf(", outflow_edges = %lld",vertex->outflow_edges);
    printf(", previsit = %lld",vertex->previsit);
    printf(", postvisit = %lld",vertex->postvisit);
    printf(", visited = %d ]",vertex->visited);
    printf(" ===> "); printf("[ ");

    for (i=0;i<vertex->edges->size;i++)
    {
        temp_pair=vertex->edges->T1[i];
        if (temp_pair!=NULL)
        {
            pair_print(temp_pair);
            printf(", ");
        }

        temp_pair=vertex->edges->T2[i];
        if (temp_pair!=NULL)
        {
            pair_print(temp_pair);
            printf(", ");
        }
    }

    if (vertex->edges->n>0) { printf(" \b\b\b ]"); }
    else { printf("]"); }
}



void vertex_free(vertex_t *vertex)
{
    assert(vertex!=NULL);
    if (vertex->destroy!=NULL)
    {
        vertex->destroy(vertex->ident);
        vertex->ident=NULL;
    }

    cuckoo_table_free(vertex->edges);
    vertex->edges=NULL;
    free(vertex);
    vertex=NULL;
}

