/*
 * This file contains data type definitions
 * and function prototypings for procedures 
 * regarding the graph data structure.
 *
 * @author: Endri Kastrati
 * @date:   16/02/2016
 *
 */




/*
 * Using include guards to check if the
 * graph.h header file has been included
 * at least once.If it hasns't the compiler
 * copy-pastes everything into the file that
 * is including it.If the file on the other
 * hand has been included the compiler
 * skips the contents entirely.
 *
 */

#ifndef GRAPH_H
#define GRAPH_H





/*
 * Defining two aliases for the unsigned integer native type,
 * called uint and label_t.Defining three new data types of
 * function pointers called GraphCompareFn,GraphPrintFn,GraphDestroyFn.
 * These functions enable polymorphism by specifying an interface
 * for the comparison,printing and memory deallocation function.
 * These functions have to be written by the user and meet the
 * following criteria.
 *
 */

typedef unsigned int    label_t;
typedef unsigned int    uint;

typedef int     (*GraphCompareFn)(const void *,const void *);
typedef void    (*GraphPrintFn)(const void *);
typedef void    (*GraphDestroyFn)(void *);




/*
 * Defining a new data type that represents the 
 * abstract concept of an edge in a graph.This 
 * structure has as components a void pointer to
 * some data that represents the weight and an
 * label_t type.
 *
 */

typedef struct
{
    void        *weight;
    label_t     v;
} edge_t;




/*
 * Defining a new data type that represents the
 * abstract concept of a vertex in a graph.This
 * structure has for components a void pointer to
 * some data,a labe_t type,an uint,an array of edge_t datatypes
 * the current number of edges and the maximum number of
 * edges as well as two uint named previsit,postvisit
 * that will assist in the exploration and topological
 * sorting ( if it is directed ) of the graph.
 *
 */

typedef struct
{
    void        *vdata;
    label_t     u;
    uint        visited;
    edge_t      *edges;
    uint        num_edges;
    uint        max_num_edges;
    uint        previsit;
    uint        postvisit;
} vertex_t;





/*
 * This is the C implementation of the Graph data structure.
 * This enhanced version contains as components a void pointer
 * to some data,an array of vertex_t datatypes, number
 * of vertices in the graph ( fixed ) and three function
 * pointers cmp,print,destroy to enable polymorphism.
 *
 */

typedef struct
{
    void                *gdata;
    vertex_t            *vertices;
    uint                num_vertices;
    GraphCompareFn      cmp;
    GraphPrintFn        print;
    GraphDestroyFn      destroy;
} graph_t;





/*
 * Function prototypings of procedures regarding the
 * Graph data structure such as create,add edge,remove edge,
 * depth first search, etc..
 *
 */

graph_t     *graph_create(void *gdata,uint n,GraphCompareFn cmp,GraphPrintFn print,GraphDestroyFn destroy);
edge_t      *graph_getEdges(graph_t *g,label_t u,int *num_edges);
vertex_t    *graph_getVertices(graph_t *g,int *num_vertices);
void        graph_add_edge(graph_t *g,void *weight,label_t u,label_t v);
void        graph_del_edge(graph_t *g,label_t u,label_t v);
void        graph_setVertex(graph_t *g,void *data,label_t u);
int         graph_hasEdge(graph_t *g,label_t u,label_t v);
int         graph_isConnected(graph_t *g);
void        graph_explore(graph_t *g,label_t u,void (*exploreFn)(graph_t *g,uint *counter,label_t u));
void        graph_print(graph_t *g);
void        graph_free(graph_t *g);




/*
 * Once everything has been copy-pasted by
 * the compiler and the macro GRAPH_H has
 * been defined, the graph.h header file 
 * will not be included more than once.
 *
 */

#endif