/*
 * This file contains datatype definitions
 * and function prototypings regarding the
 * abstract concept of a vertex data structure
 * in a graph.
 *
 * @author: Endri Kastrati
 * @date:   26/01/2017
 *
 */





/*
 * Using include guards to check
 * if the vertex.h header file has
 * been included at least once.If it
 * hasn't,the compiler copy-pastes
 * everything into the file that is
 * including it.If the file on the 
 * other hand has been included the
 * compiler skips the contents entirely.
 *
 */

#ifndef VERTEX_H
#define VERTEX_H





/*
 * Including the edge.h header file
 * that contains datatype definitions
 * for the edge_t data structure and
 * the cuckootable.h header file that
 * contains datatype definitions for
 * the cuckoo hash table data structure.
 *
 */

#include "edge.h"
#include "cuckootable.h"




/*
 * Defining an alias for the unsigned long long int
 * native type as well as three function pointers
 * to enable polymorphism.The weight component
 * of the edge_t data structure can contain any
 * kind of datatype as long as the following
 * functions adhere to the following criteria.
 *
 */

typedef unsigned long long int  lluint;

typedef int     (*VertexCompareFn)(const void *,const void *);
typedef void    (*VertexPrintFn)(const void *);
typedef void    (*VertexDestroyFn)(void *);





/*
 * Defining a new data structure called vertex_t
 * that represents the abstract concept of a
 * vertex in a graph.This enhanced version has
 * as components a pointer to some form of
 * identification,a hash table that contains
 * the edges associated with this vertex,
 * the total number of edges,the total number
 * of inflow edges,the total number of outflow
 * edges,the previsit and postvisit and visited
 * values as well as three function pointers to
 * enable polymorphism.
 *
 */

typedef struct
{
    void                *ident;
    cuckoo_t            *edges;
    lluint              num_edges;
    lluint              inflow_edges;
    lluint              outflow_edges;
    lluint              previsit;
    lluint              postvisit;
    int                 visited;
    VertexCompareFn     cmp;
    VertexPrintFn       print;
    VertexDestroyFn     destroy;
} vertex_t;





/*
 * Function prototyping of procedures regarding the 
 * vertex data structure such as create,addEdge,
 * removeEdge,free,print etc,,
 *
 */

vertex_t    *vertex_create(void *ident,CuckooHashFn hash,VertexCompareFn cmp,VertexPrintFn print,VertexDestroyFn destroy);
void        vertex_addEdge(vertex_t *vertex,void *ident,edge_t *edge);
int         vertex_hasEdge(vertex_t *vertex,void *ident);
edge_t      *vertex_getEdge(vertex_t *vertex,void *ident);
void        vertex_removeEdge(vertex_t *vertex,void *ident);
void        vertex_visited(vertex_t *vertex);
int         vertex_isVisited(vertex_t *vertex);
edge_t      **vertex_arrayEdges(vertex_t *vertex);
void        vertex_print(vertex_t *vertex);
void        vertex_free(vertex_t *vertex);





/*
 * Once everything has benn copy-pasted
 * by the compiler and the macro constant
 * VERTEX_H has been defined,the vertex.h
 * header file will not be included more
 * than once.
 *
 */

#endif
