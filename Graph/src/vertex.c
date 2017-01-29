/*
 * This file contains definitions of
 * procedures regarding the vertex
 * data structure and the operations
 * associated with it.
 *
 * @author: Endri Kastrati
 * @date:   26/01/2017
 *
 */



/*
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertion library and the
 * header file vertex.h that contains datatype
 * definitions for the vertex data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vertex.h"




/*
 * @COMPLEXITY: O(f(n)) where f(n) is a function that
 *              describes the asymptotic complexity
 *              of the comparison procedure of the
 *              edge_t data structure's components.
 * 
 * The static function compare_edges(),takes two pointers 
 * to some immutable data.This function casts the given
 * pointers to edge_t data structures and invokes the
 * function edge_CompareTo() to compare the edges.
 * Once the edges have been compared the results is
 * returned.
 *
 * @param:  const void      *e1
 * @param:  const void      *e2
 * @return: int
 *
 */

static int compare_edges(const void *e1,const void *e2)
{
    edge_t *ee1=NULL,*ee2=NULL;
    ee1=(edge_t *)e1;
    ee2=(edge_t *)e2;
    return edge_compareTo(ee1,ee2->weight);
}




/*
 * @COMPLEXITY: O(f(n)) where f(n) is a function that
 *              describes the asymptotic complexity
 *              of the printing procedure of the
 *              edge_t data structure's components.
 *
 * The static function print_edge() takes a pointer
 * to some immutable data.This function casts the
 * given pointer to an edge_t data structure and
 * prints it by invoking the function edge_print().
 *
 * @param:  const void  *e
 * @return: void
 *
 */

static void print_edge(const void *e)
{
    edge_t *ee=NULL;
    ee=(edge_t *)e;
    edge_print(ee);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function destroy_edge(),takes a pointer
 * to some data and casts it into an edge_t data 
 * structure.Once the casting has been completed
 * the memory chunk associated with the given data
 * structure is deallocated using the function
 * edge_free().
 *
 * @param:  void    *e
 * @return: void
 *
 */

static void destroy_edge(void *e)
{
    edge_t *ee=NULL;
    ee=(edge_t *)e;
    edge_free(ee);
    ee=NULL; return;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*
 * @COMPLEXITY: O(m) where m is the initial size of 
 *              the cuckoo hash table data structure.
 * 
 * The function vertex_create(),takes five arguments as
 * parameters.The first argument is a pointer to some
 * form of identification for the vertex.The second is
 * a function pointer to a hash function for the kind
 * of identification provided.The last three are also
 * function pointers that enable polymorphism by providing
 * an interface for the comparison,print and destroy functions.
 * These functions have to be implemented by the user.Failure
 * to do so will result in program termination due to invalid
 * assertions.
 *
 * @param:  void                    *ident
 * @param:  CuckooHashFn            hash
 * @param:  VertexCompareFn         cmp
 * @param:  VertexPrintFn           print
 * @param:  VertexDestroyFn         destroy
 * @return: vertex_t                *
 *
 */

vertex_t *vertex_create(void *ident,CuckooHashFn hash,VertexCompareFn cmp,VertexPrintFn print,VertexDestroyFn destroy)
{
    vertex_t *new_vertex=NULL;
    assert(cmp!=NULL && print!=NULL);
    new_vertex=(vertex_t *)malloc(sizeof(*new_vertex));
    assert(new_vertex!=NULL);
    new_vertex->ident=ident;
    new_vertex->edges=cuckoo_create(hash);
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





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function vertex_addEdge(),takes three arguments
 * as parameters.The first one is a vertex_t data structure.
 * The second one is the identification of the vertex that
 * this edge points to and the third one is an edge_t data
 * structure.This function takes the given arguments and
 * inserts the given edge_t datatype into the hashtable
 * associating it with the given identification value.
 *
 * @param:  vertex_t        *vertex
 * @param:  void            *ident
 * @param:  edge_t          *edge
 * @return: void
 *
 */

void vertex_addEdge(vertex_t *vertex,void *ident,edge_t *edge)
{
    int query;
    cue_t *new_cue=NULL;
    value_t *new_value=NULL;
    pair_t *new_pair=NULL;
    assert(vertex!=NULL && edge!=NULL);
    new_cue=cue_create(ident,vertex->cmp,vertex->print,NULL);
    new_value=value_create(edge,compare_edges,print_edge,destroy_edge);
    new_pair=pair_create(new_cue,new_value);
    query=cuckoo_lookup(vertex->edges,ident);
    
    if (query==0)
    {
        cuckoo_insert(vertex->edges,new_pair);
        vertex->num_edges=vertex->edges->n;
        vertex->outflow_edges=vertex->edges->n;
    }
    else
    {
        pair_free(new_pair);
        new_pair=NULL;
    }

    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function vertex_hasEdge(),takes two arguments
 * as parameters.The first argument is a vertex_t
 * data structure and the second one a pointer to
 * some type of vertex identification.This function
 * takes the given arguments and searches into the
 * edge hash table of the given vertex for the specific
 * identification.If it is found,it means the vertex
 * has an edge to the specified vertex,otherwise it
 * does not.This operation is really fast as it takes
 * only constant time to look into the cuckoo hash
 * table data structure of the vertex.
 *
 * @param:  vertex_t    *vertex
 * @param:  void        *ident
 * @return: int
 *
 */

int vertex_hasEdge(vertex_t *vertex,void *ident)
{
    int query;
    assert(vertex!=NULL);
    query=cuckoo_lookup(vertex->edges,ident);
    return query;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function vertex_getEdge(),takes two arguments
 * as parameters.The first argument is a vertex_t
 * data structure and the second one a pointer to
 * some type of vertex identification.This function
 * takes the given arguments and returns the edge_t
 * data structure of the current vertex associated
 * with the given identification value.If the edge
 * does not exist it returns null instead.This operation
 * is really fast as it takes only constant time to look
 * for the value of particular key into the cuckoo table.
 *
 * @param:  vertex_t    *vertex
 * @param:  void        *ident
 * @return: edge_t      *
 *
 */

edge_t *vertex_getEdge(vertex_t *vertex,void *ident)
{
    assert(vertex!=NULL);
    return (edge_t *)cuckoo_getValue(vertex->edges,ident);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function vertex_removeEdge(),takes two arguments
 * as parameters.The first argument is a vertex_t data
 * structure and the second one a pointer to some kind
 * of vertex identification.This function takes the given
 * arguments and removes the edge_t data structure associated
 * with the given identification value.If the edge does not
 * exist then nothing happens.This operation is really fast
 * as it takes only constant time to delete items from the
 * cuckoo hash table.
 *
 * @param:  vertex_t    *vertex
 * @param:  void        *ident
 * @return: void
 *
 */

void vertex_removeEdge(vertex_t *vertex,void *ident)
{
    assert(vertex!=NULL);
    cuckoo_remove(vertex->edges,ident);
    vertex->num_edges=vertex->edges->n;
    vertex->outflow_edges=vertex->edges->n;
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function vertex_visited(),takes a vertex_t
 * data structure as an argument and sets the
 * value of the it's visited component to one.
 *
 * @param:  vertex_t    *vertex
 * @return: void
 *
 */

void vertex_visited(vertex_t *vertex)
{
    assert(vertex!=NULL);
    vertex->visited=1;
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function vertex_isVisited(),takes a vertex_t
 * data structure as an argument and returns the
 * value of the visited component.
 *
 * @param:  vertex_t    *vertex
 * @return: int
 *
 */

int vertex_isVisited(vertex_t *vertex)
{
    assert(vertex!=NULL);
    return vertex->visited;
}





/*
 * @COMPLEXITY: O(m) where m is the size of
 *              the cuckoo hash table.
 * 
 * The function vertex_arrayEdges(),takes a
 * vertex_t data structure as an argument and
 * returns an array containing the edges that
 * radiate from this vertex.The size of the
 * returned static array is equivalent to
 * the value of the vertex's num_edges value.
 * This function is a bit time consuming since
 * we have to iterate over two tables of the
 * cuckoo hash data structure to retrieve the
 * edge_t data structures.If the state of the
 * vertex changes (new edges added,removed etc..)
 * this function should be invoked again.The 
 * returned array has to be manually deallocated
 * by the user.
 *
 * @param:  vertex_t    *vertex
 * @return: edge_t      **
 *
 */

edge_t **vertex_arrayEdges(vertex_t *vertex)
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
            temp_value=pair_getValue(temp_pair);
            edges_array[step++]=value_get(temp_value);
        }

        temp_pair=vertex->edges->T2[i];
        if (temp_pair!=NULL)
        {
            temp_value=pair_getValue(temp_pair);
            edges_array[step++]=value_get(temp_value);
        }
    }

    return edges_array;
}




/*
 * @COMPLEXITY: O(m) where m is the size of
 *              the hash table that contains
 *              the edges that radiate from
 *              this vertex outwards.
 * 
 * The function vertex_print(),takes a vertex_t
 * data structure as an argument and prints it's
 * edge components in a user-friendly format.
 *
 * @param:  vertex_t    *vertex
 * @return: void
 *
 */

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
    return;
}




/*
 * @COMPLEXITY: O(m) where m is the size of the
 *              hash table that contains the
 *              edges that radiate outwards from
 *              the given vertex data structure.
 *
 * The function vertex_free(),takes a vertex_t
 * data structure as an argument and deallocates
 * the memory chunk associated with it and it's
 * components.
 *
 * @param:  vertex_t    *vertex
 * @return: void
 *
 */

void vertex_free(vertex_t *vertex)
{
    assert(vertex!=NULL); 
    if (vertex->destroy!=NULL)
    {
        vertex->destroy(vertex->ident);
        vertex->ident=NULL;
    }

    cuckoo_free(vertex->edges);
    vertex->edges=NULL;
    free(vertex);
    vertex=NULL;
    return;
}

