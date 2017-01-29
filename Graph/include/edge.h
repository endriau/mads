/*
 * This file contains datatype definition
 * and function prototyping regarding the
 * edge data structure that represents the
 * abstract concept of an edge radiating
 * outwards or inwards a vertex.
 *
 * @author: Endri Kastrati
 * @date:   25/01/2017
 *
 */






/*
 * Using include guards to check if the
 * edge.h header file has been included
 * at least once.If it hasn't,the compiler
 * copy-pastes everything into the file
 * that is including it.If the file on
 * the other hand has been included the
 * compiler skips the contents entirely.
 *
 */

#ifndef EDGE_H
#define EDGE_H




/*
 * Defining three new datatypes of function pointers.These
 * functions enable polymorphism by providing an interface
 * for the comparison,print and memory deallocation functions
 * regarding the edge_t data structure's components.These
 * functions have to be implemented by the user and
 * meet the following criteria.
 *
 */

typedef int     (*EdgeCompareFn)(const void *,const void *);
typedef void    (*EdgePrintFn)(const void *);
typedef void    (*EdgeDestroyFn)(void *);




/*
 * Defining a new data structure called edge_t
 * that represents the abstract concept of an
 * edge radiating inwards or outwards a vertex.
 * This ehanced version has as components a
 * pointer to some weight data,a pointer to
 * the next endpoint (vertex) and three
 * function pointers to enable polymorphism.
 *
 */

typedef struct
{
    void                *weight;
    void                *endpoint;
    EdgeCompareFn       cmp;
    EdgePrintFn         print;
    EdgeDestroyFn       destroy;
} edge_t;





/*
 * Function prototyping of procedures regarding
 * the edge data structure such as create,getWeight,
 * getEndPoint etc..
 *
 */

edge_t      *edge_create(void *w,void *ep,EdgeCompareFn cmp,EdgePrintFn print,EdgeDestroyFn destroy);
void        *edge_getWeight(edge_t *edge);
void        *edge_getEndPoint(edge_t *edge);
void        edge_changeWeight(edge_t *edge,void *new_w);
void        edge_changeEndPoint(edge_t *edge,void *new_ep);
int         edge_compareTo(edge_t *edge,void *data);
void        edge_print(edge_t *edge);
void        edge_free(edge_t *edge);





/*
 * Once everything has benn copy-pasted
 * by the compiler and the macro constant
 * EDGE_H has been defined,the edge.h
 * header file will not be included more
 * than once.
 *
 */

#endif

