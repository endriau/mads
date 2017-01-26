/*
 * This file contains definitions of procedures
 * regarding the edge data structure and the
 * operations associated with it.
 *
 * @author: Endri Kastrati
 * @date:   25/01/2017
 *
 */



/*
 * Including the stanard input-output library,
 * the standard utilities library,the standard
 * assertions library and the header file edge.h
 * that cotains datatype definitions and function
 * prototyping regarding the edge data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "edge.h"





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function edge_create(),takes five arguments as parameters.
 * The first two arguments are pointers to some weight value
 * associated with this edge and a pointer to the next endpoint
 * (the address of a vertex).The last three are function pointers
 * that enable polymorphism.The user has to implement the functions
 * cmp,print and destroy (optionally).Failure to do so will result
 * in program terminantion due to invalid assertions.
 *
 * @param:  void                *w
 * @param:  void                *ep
 * @param:  EdgeCompareFn       cmp
 * @param:  EdgePrintFn         print
 * @param:  EdgeDestroyFn       destroy
 * @return: edge_t              *
 *
 */

edge_t *edge_create(void *w,void *ep,EdgeCompareFn cmp,EdgePrintFn print,EdgeDestroyFn destroy)
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




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function edge_getWeight(),takes an edge_t
 * data structure as an argument and returns it's
 * weight component.
 *
 * @param:  edge_t      *edge
 * @return: void        *
 *
 */

void *edge_getWeight(edge_t *edge)
{
    assert(edge!=NULL);
    return edge->weight;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function edge_getEndPoint(),takes an edge_t
 * data structure as an argument and returns it's
 * endpoint component.
 *
 * @param:  edge_t      *edge
 * @return: void        *
 *
 */

void *edge_getEndPoint(edge_t *edge)
{
    assert(edge!=NULL);
    return edge->endpoint;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function edge_changeWeight(),takes two arguments
 * as parameters.The first argument is a edge_t data
 * structure and the second one a pointer to a new
 * weight value.This function overrides the old 
 * weight value with the new one.
 *
 * @param:  edge_t      *edge
 * @param:  void        *new_w
 * @return: void
 *
 */

void edge_changeWeight(edge_t *edge,void *new_w)
{
    void *old_w=NULL;
    assert(edge!=NULL);
    old_w=edge_getWeight(edge);

    if (edge->destroy!=NULL)
    {
        edge->destroy(old_w);
        old_w=NULL;
    }

    edge->weight=new_w;
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function edge_changeEndPoint(),takes two arguments
 * as parameters.The first argument is an edge_t data
 * structure and the second one a pointer to some
 * new endpoint (new vertex).This function overrides
 * the old endpoint value with the new one.
 *
 * @param:  edge_t      *edge
 * @param:  void        *new_ep
 * @return: void
 *
 */

void edge_changeEndPoint(edge_t *edge,void *new_ep)
{
    assert(edge!=NULL);
    edge->endpoint=new_ep;
    return;
}



/*
 * @COMPLEXITY: O(f(n)) where f(n) is function
 *              that describes the given datatype's
 *              comparison complexity.
 * 
 * The function edge_compareTo(),takes two arguments
 * as parameters.The first one is an edge_t data
 * structure and the second one a pointer to some
 * data.This function compares the edge's weight
 * component to the given value.
 *
 * @param:  edge_t      *edge
 * @param:  void        *data
 * @return: int
 *
 */

int edge_compareTo(edge_t *edge,void *data)
{
    int result;
    assert(edge!=NULL);
    result=edge->cmp(edge->weight,data);
    return result;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function edge_print(),takes an edge_t data
 * structure as an argument and prints it's components
 * in a user-friendly format.
 *
 * @param:  edge_t      *edge
 * @return: void
 *
 */

void edge_print(edge_t *edge)
{
    void *ep=NULL;
    assert(edge!=NULL);
    printf("( weight = ");
    edge->print(edge->weight);
    ep=edge_getEndPoint(edge);
    printf(" ---> endpoint = %p )",ep);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The function edge_free(),takes an edge_t data
 * structure as an argument and deallocates memory
 * for it and it's components.
 *
 * @param:  edge_t      *edge
 * @return: void
 *
 */

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
    return;
}

