//
// Created by p0int3r on 6/13/21.
//

#ifndef C_DATA_STRUCTURES_VERTEX_H
#define C_DATA_STRUCTURES_VERTEX_H


#include "edge.h"
#include "cuckoo_table.h"


typedef unsigned long long int lluint;

typedef int (*vertex_compare_fn)(const void *, const void *);
typedef void (*vertex_print_fn)(const void *);
typedef void (*vertex_destroy_fn)(void *);


typedef struct
{
    void *ident;
    cuckoo_table_t *edges;
    lluint num_edges;
    lluint inflow_edges;
    lluint outflow_edges;
    lluint previsit;
    lluint postvisit;
    int visited;
    vertex_compare_fn cmp;
    vertex_print_fn print;
    vertex_destroy_fn destroy;
} vertex_t;



vertex_t *vertex_create(void *ident, cuckoo_hash_fn hash, vertex_compare_fn cmp, vertex_print_fn print, vertex_destroy_fn destroy);
void vertex_add_edge(vertex_t *vertex, void *ident, edge_t *edge);
int vertex_has_edge(vertex_t *vertex, void *ident);
edge_t *vertex_get_edge(vertex_t *vertex, void *ident);
void vertex_remove_edge(vertex_t *vertex, void *ident);
void vertex_visited(vertex_t *vertex);
int vertex_is_visited(vertex_t *vertex);
edge_t **vertex_array_edges(vertex_t *vertex);
void vertex_print(vertex_t *vertex);
void vertex_free(vertex_t *vertex);


#endif //C_DATA_STRUCTURES_VERTEX_H
