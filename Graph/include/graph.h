/*
 * This file contains datatype definitions and
 * function prototyping for the graph data 
 * structure.
 *
 * @author: Endri Kastrati
 * @date:   27/01/2017
 *
 */



/*
 * Using include guards to check if the
 * graph.h header file has been included
 * at least once.If it hasn't,the compiler
 * copy-pastes everything into the file that
 * is including it.If the file on the other
 * hand has been included the compiler skips
 * the contents entirely.
 *
 */

#ifndef GRAPH_H
#define GRAPH_H




/*
 * Including the vertex.h header file
 * that contains datatype definitions
 * for the vertex_t data structure and
 * the header file cuckootable.h that
 * contains definitions for the cuckoo
 * hash table data structure.
 *
 */

#include "vertex.h"
#include "cuckootable.h"



/*
 * Defining two new macro constants that
 * specify the type of the graph data
 * structure.The two main types are
 * a directed graph with edges going
 * one way only and an undirected graph
 * with edges going both wasy.
 *
 */

#define DIRECTED_GRAPH      68
#define UNDIRECTED_GRAPH    85






/*
 * Defining an alias for the unsigned long long
 * int native datatype and a function pointer 
 * to an exploration procedure regarding the
 * graph data structure.The function has to
 * be implemented by the user and meet the
 * following criteria.
 *
 */

typedef unsigned long long int  lluint;

typedef void    (*GraphExploreFn)(vertex_t *,lluint *);




/*
 * Defining a new data structure called graph_t
 * that represents the abstract concept of a
 * graph with vertices and edges.This enhanced
 * version has as components a hash table of
 * vertices associated with an id,the total
 * number of vertices in the table,a flag
 * on whether the graph is connected or not,
 * the type of graph (directed or undirected)
 * and a function pointer to an exploration
 * procedure to increase flexibility.
 *
 */

typedef struct
{
    cuckoo_t            *vertices;
    lluint              num_vertices;
    lluint              total_num_edges;
    int                 connected;
    int                 type;
    GraphExploreFn      explore;
} graph_t;




/*
 * Function prototyping of procedures regarding the graph data
 * structure such as create,addVertex,print,free etc..
 *
 */

graph_t         *graph_create(int type,CuckooHashFn hash,GraphExploreFn explore);
void            graph_setExplorer(graph_t *graph,GraphExploreFn explore);
void            graph_addVertex(graph_t *graph,vertex_t *vertex);
int             graph_hasVertex(graph_t *graph,void *ident);
vertex_t        *graph_getVertex(graph_t *graph,void *ident);
void            graph_removeVertex(graph_t *graph,void *ident);
void            graph_addEdge(graph_t *graph,void *ident1,void *ident2,edge_t *edge);
int             graph_hasEdge(graph_t *graph,void *ident1,void *ident2);
edge_t          *graph_getEdge(graph_t *graph,void *ident1,void *ident2);
void            graph_removeEdge(graph_t *graph,void *ident1,void *ident2);
void            graph_explore(graph_t *graph,void *ident);
vertex_t        **graph_arrayVertices(graph_t *graph);
void            graph_print(graph_t *graph);
void            graph_free(graph_t *graph);




/*
 * Once everything has been copy-pasted
 * by the compiler and the macro constant
 * GRAPH_H has been defined,the graph.h
 * header file will not be included more
 * than once.
 *
 */

#endif
