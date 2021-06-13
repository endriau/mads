//
// Created by p0int3r on 6/13/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"


static int compare_vertices(const void *v1,const void *v2)
{
    vertex_t *vv1=NULL,*vv2=NULL;
    vv1=(vertex_t *)v1;
    vv2=(vertex_t *)v2;
    if (vv1<vv2)  { return -1; }
    if (vv1==vv2) { return  0; }
    if (vv1>vv2)  { return  1; }
    return 0;
}


static void print_vertex(const void *v)
{
    vertex_t *vv=NULL;
    vv=(vertex_t *)v;
    vertex_print(vv);
}


static void destroy_vertex(void *v)
{
    vertex_t *vv=NULL;
    vv=(vertex_t *)v;
    vertex_free(vv);
}

graph_t *graph_create(int type, cuckoo_hash_fn hash, graph_explore_fn explore)
{
    graph_t *new_graph=NULL;
    assert(type==DIRECTED_GRAPH || type==UNDIRECTED_GRAPH);
    new_graph=(graph_t *)malloc(sizeof(*new_graph));
    assert(new_graph!=NULL);
    new_graph->vertices= cuckoo_table_create(hash);
    new_graph->num_vertices=0;
    new_graph->total_num_edges=0;
    new_graph->connected=0;
    new_graph->type=type;
    new_graph->explore=explore;
    return new_graph;
}


void graph_set_explorer(graph_t *graph, graph_explore_fn explore)
{
    assert(graph!=NULL);
    graph->explore=explore;
}


void graph_add_vertex(graph_t *graph, vertex_t *vertex)
{
    cue_t *new_cue=NULL;
    value_t *new_value=NULL;
    pair_t *new_pair=NULL;
    assert(graph!=NULL && vertex!=NULL);
    if (graph_has_vertex(graph, vertex->ident)) { return; }
    new_cue=cue_create(vertex->ident,vertex->cmp,vertex->print,NULL);
    new_value=value_create(vertex,compare_vertices,print_vertex,destroy_vertex);
    new_pair=pair_create(new_cue,new_value);
    cuckoo_table_insert(graph->vertices, new_pair);
    graph->num_vertices=graph->vertices->n;
}


int graph_has_vertex(graph_t *graph, void *ident)
{
    int query;
    assert(graph!=NULL);
    query= cuckoo_table_lookup(graph->vertices, ident);
    return query;
}

vertex_t *graph_get_vertex(graph_t *graph, void *ident)
{
    assert(graph!=NULL);
    return (vertex_t *) cuckoo_table_get_value(graph->vertices, ident);
}

void graph_remove_vertex(graph_t *graph, void *ident)
{
    int query; lluint i;
    assert(graph!=NULL); value_t *temp_value=NULL;
    vertex_t *temp_vertex=NULL,*adj_vertex=NULL;
    pair_t *temp_pair=NULL; cue_t *temp_cue=NULL;
    query= cuckoo_table_lookup(graph->vertices, ident);
    if (query==0) { return; }

    if (graph->type==DIRECTED_GRAPH)
    {
        for (i=0;i<graph->vertices->size;i++)
        {
            temp_pair=graph->vertices->T1[i];
            if (temp_pair!=NULL)
            {
                temp_value= pair_get_value(temp_pair);
                temp_vertex=value_get(temp_value);
                vertex_remove_edge(temp_vertex, ident);
            }

            temp_pair=graph->vertices->T2[i];
            if (temp_pair!=NULL)
            {
                temp_value= pair_get_value(temp_pair);
                temp_vertex=value_get(temp_value);
                vertex_remove_edge(temp_vertex, ident);
            }
        }

        cuckoo_table_remove(graph->vertices, ident);
        graph->num_vertices=graph->vertices->n;
    }
    else
    {
        temp_vertex= graph_get_vertex(graph, ident);
        for (i=0;i<temp_vertex->edges->size;i++)
        {
            temp_pair=temp_vertex->edges->T1[i];
            if (temp_pair!=NULL)
            {
                temp_cue= pair_get_cue(temp_pair);
                adj_vertex= graph_get_vertex(graph, cue_get(temp_cue));
                vertex_remove_edge(adj_vertex, ident);
                adj_vertex->inflow_edges--;
            }

            temp_pair=temp_vertex->edges->T2[i];
            if (temp_pair!=NULL)
            {
                temp_cue= pair_get_cue(temp_pair);
                adj_vertex= graph_get_vertex(graph, cue_get(temp_cue));
                vertex_remove_edge(adj_vertex, ident);
                adj_vertex->inflow_edges--;
            }
        }

        cuckoo_table_remove(graph->vertices, ident);
        graph->num_vertices=graph->vertices->n;
    }
}


void graph_add_edge(graph_t *graph, void *ident1, void *ident2, edge_t *edge)
{
    int query;
    void *mirror_endpoint=NULL;
    void *mirror_weight=NULL;
    edge_t *mirror_edge=NULL;
    vertex_t *temp_vertex1=NULL;
    vertex_t *temp_vertex2=NULL;
    assert(graph!=NULL && edge!=NULL);
    query= graph_has_edge(graph, ident1, ident2);
    if (query==1) { return; }

    temp_vertex1= graph_get_vertex(graph, ident1);
    temp_vertex2= graph_get_vertex(graph, ident2);
    assert(temp_vertex2 == edge_get_end_point(edge));
    vertex_add_edge(temp_vertex1, ident2, edge);
    temp_vertex2->inflow_edges++;

    if (graph->type==UNDIRECTED_GRAPH)
    {
        mirror_weight= edge_get_weight(edge);
        mirror_endpoint=temp_vertex1;
        mirror_edge=edge_create(mirror_weight,mirror_endpoint,
                                edge->cmp,edge->print,edge->destroy);
        vertex_add_edge(temp_vertex2, ident1, mirror_edge);
        temp_vertex1->inflow_edges++;
    }

    graph->total_num_edges++;
}


int graph_has_edge(graph_t *graph, void *ident1, void *ident2)
{
    int query1,query2,query;
    vertex_t *temp_vertex=NULL;
    assert(graph!=NULL);
    query1= graph_has_vertex(graph, ident1);
    if (query1==0) { return 0; }
    query2= graph_has_vertex(graph, ident2);
    if (query2==0) { return 0; }
    temp_vertex= graph_get_vertex(graph, ident1);
    query= vertex_has_edge(temp_vertex, ident2);
    return query;
}


edge_t *graph_get_edge(graph_t *graph, void *ident1, void *ident2)
{
    vertex_t *temp_vertex=NULL;
    edge_t *temp_edge=NULL;
    assert(graph!=NULL);
    if (!graph_has_edge(graph, ident1, ident2)) { return NULL; }
    temp_vertex= graph_get_vertex(graph, ident1);
    temp_edge= vertex_get_edge(temp_vertex, ident2);
    return temp_edge;
}


void graph_remove_edge(graph_t *graph, void *ident1, void *ident2)
{
    vertex_t *temp_vertex1=NULL;
    vertex_t *temp_vertex2=NULL;
    assert(graph!=NULL);
    if (!graph_has_edge(graph, ident1, ident2)) { return; }
    temp_vertex1= graph_get_vertex(graph, ident1);
    temp_vertex2= graph_get_vertex(graph, ident2);
    vertex_remove_edge(temp_vertex1, ident2);
    temp_vertex2->inflow_edges--;

    if (graph->type==UNDIRECTED_GRAPH)
    {
        vertex_remove_edge(temp_vertex2, ident1);
        temp_vertex1->inflow_edges--;
    }

    graph->total_num_edges--;
}


void graph_explore(graph_t *graph,void *ident)
{
    int query;
    lluint i,counter=0;
    vertex_t *curr_vertex=NULL;
    vertex_t **vertices_array=NULL;
    assert(graph!=NULL && graph->explore!=NULL);
    query= graph_has_vertex(graph, ident);
    assert(query==1);
    curr_vertex= graph_get_vertex(graph, ident);
    graph->explore(curr_vertex,&counter);
    vertices_array= graph_array_vertices(graph);

    for (i=0;i<graph->num_vertices;i++)
    {
        if (vertex_is_visited(vertices_array[i]) == 0)
            graph->explore(vertices_array[i],&counter);
    }

    free(vertices_array);
}


vertex_t **graph_array_vertices(graph_t *graph)
{
    lluint i,size,step;
    assert(graph!=NULL);
    pair_t *temp_pair=NULL;
    value_t *temp_value=NULL;
    size=graph->vertices->n;
    vertex_t **vertices_array=NULL;
    if (size==0) { return NULL; }
    vertices_array=(vertex_t **)malloc(size*sizeof(**vertices_array));
    assert(vertices_array!=NULL); step=0;

    for (i=0;i<graph->vertices->size;i++)
    {
        temp_pair=graph->vertices->T1[i];
        if (temp_pair!=NULL)
        {
            temp_value= pair_get_value(temp_pair);
            vertices_array[step++]=value_get(temp_value);
        }

        temp_pair=graph->vertices->T2[i];
        if (temp_pair!=NULL)
        {
            temp_value= pair_get_value(temp_pair);
            vertices_array[step++]=value_get(temp_value);
        }
    }

    return vertices_array;
}


void graph_print(graph_t *graph)
{
    lluint i;
    assert(graph!=NULL);
    pair_t *temp_pair=NULL;
    printf("Graph information:");
    printf(" type = ");
    if (graph->type==DIRECTED_GRAPH) { printf("directed, "); }
    if (graph->type==UNDIRECTED_GRAPH) { printf("undirected, "); }
    printf("num_vertices = %lld, ",graph->num_vertices);
    printf("total_num_edges = %lld, ",graph->total_num_edges);
    printf(" connected = %d\n",graph->connected);
    for (i=0;i<graph->vertices->size;i++)
    {
        temp_pair=graph->vertices->T1[i];
        if (temp_pair!=NULL)
        {
            pair_print(temp_pair);
            printf("\n");
        }

        temp_pair=graph->vertices->T2[i];
        if (temp_pair!=NULL)
        {
            pair_print(temp_pair);
            printf("\n");
        }
    }
}


void graph_free(graph_t *graph)
{
    assert(graph!=NULL);
    cuckoo_table_free(graph->vertices);
    graph->vertices=NULL;
    free(graph); graph=NULL;
}

