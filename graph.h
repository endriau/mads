//
// Created by p0int3r on 6/13/21.
//

#ifndef C_DATA_STRUCTURES_GRAPH_H
#define C_DATA_STRUCTURES_GRAPH_H



#include "vertex.h"
#include "cuckoo_table.h"


#define DIRECTED_GRAPH 68
#define UNDIRECTED_GRAPH 85


typedef unsigned long long int lluint;

typedef void (*graph_explore_fn)(vertex_t *, lluint *);


typedef struct
{
    cuckoo_table_t *vertices;
    lluint num_vertices;
    lluint total_num_edges;
    int connected;
    int type;
    graph_explore_fn explore;
} graph_t;


graph_t *graph_create(int type, cuckoo_hash_fn hash, graph_explore_fn explore);
void graph_set_explorer(graph_t *graph, graph_explore_fn explore);
void graph_add_vertex(graph_t *graph, vertex_t *vertex);
int graph_has_vertex(graph_t *graph, void *ident);
vertex_t *graph_get_vertex(graph_t *graph, void *ident);
void graph_remove_vertex(graph_t *graph, void *ident);
void graph_add_edge(graph_t *graph, void *ident1, void *ident2, edge_t *edge);
int graph_has_edge(graph_t *graph, void *ident1, void *ident2);
edge_t *graph_get_edge(graph_t *graph, void *ident1, void *ident2);
void graph_remove_edge(graph_t *graph, void *ident1, void *ident2);
void graph_explore(graph_t *graph,void *ident);
vertex_t **graph_array_vertices(graph_t *graph);
void graph_print(graph_t *graph);
void graph_free(graph_t *graph);


#endif //C_DATA_STRUCTURES_GRAPH_H
