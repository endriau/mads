/*
 * This file contains function definitions
 * of procedures regarding the Graph
 * data structure.
 *
 * @author: Endri Kastrati
 * @date:   16/02/2016
 *
 */



/*
 * Including the standard input-output library,
 * the standard utilities library, the standard
 * assertion library and the graph.h header file
 * that contains data type definitions and function
 * prototypings for the Graph data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"





/*
 * @COMPLEXITY: O(n), where n is the number of vertices.
 *
 * The function graph_create() takes five arguments,a void pointer
 * to some data,the fixed size of vertices and three function pointers.
 * It creates a new graph_t data structure by allocating memory for it
 * and it's components and instantiates it's components to the default
 * values.The print and cmp components are mandatory and cannot be null.
 * The user has to create their own cmp,print,destroy ( optional ) functions.
 * Failure to do so will result in program termination due to invalid assertions.
 *
 * @param:   void               *gdata
 * @param:   uint               n
 * @param:   GraphCompareFn     cmp
 * @param:   GraphPrintFn       print
 * @param:   GraphDestroyFn     destroy
 * @return:  graph_t            *
 *
 */

graph_t *graph_create(void *gdata,uint n,GraphCompareFn cmp,GraphPrintFn print,GraphDestroyFn destroy)
{
    uint init_edges_size=1,i;
    graph_t *graph=NULL;
    assert(cmp!=NULL && print!=NULL);
    graph=(graph_t *)malloc(sizeof(*graph));
    assert(graph!=NULL);
    graph->gdata=gdata;
    graph->vertices=(vertex_t *)malloc(n*sizeof(vertex_t ));
    assert(graph->vertices!=NULL);
    graph->num_vertices=n;
    
    for (i=0;i<graph->num_vertices;i++)
    {
        graph->vertices[i].edges=(edge_t *)malloc(init_edges_size*sizeof(edge_t ));
        assert(graph->vertices[i].edges!=NULL);
        graph->vertices[i].num_edges=0;
        graph->vertices[i].max_num_edges=init_edges_size;
        graph->vertices[i].u=i;
        graph->vertices[i].previsit=0;
        graph->vertices[i].postvisit=0;
        graph->vertices[i].visited=0;
    }

    graph->cmp=cmp;
    graph->print=print;
    graph->destroy=destroy;
    return graph;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_getEdges() takes three arguments,
 * a graph_t data structure,a uint ( vertex label ),a
 * pointer to an int that gets assigned the size of the edges
 * and returns the edges of the specified vertex.
 *
 * @param:   graph_t    *g
 * @param:   label_t    u
 * @param:   int        *num_edges
 * @return:  edge_t     *
 *
 */

edge_t *graph_getEdges(graph_t *g,label_t u,int *num_edges)
{
    assert(g!=NULL);
    assert(u>=0 && u<g->num_vertices);
    *num_edges=g->vertices[u].num_edges;
    return g->vertices[u].edges;
}






/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_getVertices() takes two arguments 
 * a graph_t data structure and a pointer to an int that
 * gets assigned the size of the vertices and returns the
 * vertices of the graph.
 *
 * @param:   graph_t    *g
 * @param:   int        *num_vertices
 * @return:  vertex_t   *
 *
 */

vertex_t *graph_getVertices(graph_t *g,int *num_vertices)
{
    assert(g!=NULL);
    *num_vertices=g->num_vertices;
    return g->vertices;
}






/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_add_edge() takes four arguments,a graph_t
 * data structure,a void pointer to some data,two label_t types
 * and adds a new edge between the specified vertices and with the
 * given weight value.
 *
 * @param:   graph_t    *g
 * @param:   void       *weight
 * @param:   label_t    u
 * @param:   label_t    v
 * @return:  void
 *
 */

void graph_add_edge(graph_t *g,void *weight,label_t u,label_t v)
{
    int double_size;
    assert(g!=NULL);
    assert(u>=0 && u<g->num_vertices);
    assert(v>=0 && v<g->num_vertices);

    if (g->vertices[u].num_edges+1==g->vertices[u].max_num_edges)
    {
        double_size=2*g->vertices[u].max_num_edges;
        g->vertices[u].edges=(edge_t *)realloc(g->vertices[u].edges,double_size*sizeof(edge_t ));
        assert(g->vertices[u].edges!=NULL);
        g->vertices[u].max_num_edges=double_size;
    }

    g->vertices[u].edges[g->vertices[u].num_edges].weight=weight;
    g->vertices[u].edges[g->vertices[u].num_edges].v=v;
    g->vertices[u].num_edges+=1;
    return;
}





/*
 * @COMPLEXITY: O(n), where n is the number of vertices.
 *
 * The function graph_del_edge() takes three arguments,
 * a graph_t data structure,two label_t types and deletes
 * the edge between the two given vertices.
 *
 * @param:   graph_t    *g
 * @param:   label_t    u
 * @param:   label_t    v
 * @return:  void
 *
 */

void graph_del_edge(graph_t *g,label_t u,label_t v)
{
    int i;
    assert(g!=NULL);
    assert(u>=0 && u<g->num_vertices);
    assert(v>=0 && v<g->num_vertices);

    for (i=0;i<g->vertices[u].num_edges;i++)
    {
        if (g->vertices[u].edges[i].v==v && g->vertices[u].edges[i].weight!=(void *)(-1))
        {
            g->vertices[u].edges[i].weight=(void *)(-1);
        }
    }

    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_setVertex() takes three arguments,
 * a graph_t data structure,a void pointer to some data,
 * a labe_t type and assigns the data to the vdata component
 * of the specified vertex in the graph.
 *
 * @param:   graph_t    *g
 * @param:   void       *data
 * @param:   label_t    u
 * @return:  void
 *
 */

void graph_setVertex(graph_t *g,void *data,label_t u)
{
    assert(g!=NULL);
    assert(u>=0 && u<g->num_vertices);
    g->vertices[u].vdata=data;
    return;
}






/*
 * @COMPLEXITY: O(n), where n is the number of vertices.
 *
 * The function graph_hasEdge() takes three arguments,
 * a graph_t data structure and two labe_t types and
 * traverses the edges of the specified vertex u to see
 * if it has an edge to vertex v.
 *
 * @param:   graph_t    *g
 * @param:   label_t    u
 * @param:   label_t    v
 * @return:  int
 *
 */

int graph_hasEdge(graph_t *g,label_t u,label_t v)
{
    int i;
    assert(g!=NULL);
    assert(u>=0 && u<g->num_vertices);
    assert(v>=0 && v<g->num_vertices);

    for (i=0;i<g->vertices[u].num_edges;i++)
    {
        if (g->vertices[u].edges[i].v==v && g->vertices[u].edges[i].weight!=(void *)(-1))
        {
            return 1;
        }
    }

    return 0;
}






/*
 * @COMPLEXITY: O(n), where n is the number of vertices.
 *
 * The function graph_isConnected() takes only one argument,
 * a graph_t data structure and checks whether the current
 * graph is connected or not.If the graph is connected it
 * returns one otherwise it returns zero.
 *
 * @param:   grpah_t    *g
 * @return:  int
 *
 */

int graph_isConnected(graph_t *g)
{
    int n=0,m=0,i;
    assert(g!=NULL);
    n=g->num_vertices;

    for (i=0;i<n;i++)
    {
        m+=g->vertices[i].num_edges;
    }

    if (m>=n-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}





/*
 * @COMPLEXITY: O(m+n), where n is the number of vertices
 * and m is the number of edges.Depends on given explore function.
 *
 * The function graph_explore() takes three arguments, a graph_t
 * data structure,a labe_t type and a function pointer called exploreFn
 * and explores the vertices of the graph using the given strategy.
 * The user has to implement the exploreFn function.
 *
 * @param:   graph_t    *g
 * @param:   label_t    u
 * @param:   void       (*exploreFn)(graph_t *g,uint *counter,label_t u)
 * @return:  void
 *
 */

void graph_explore(graph_t *g,label_t u,void (*exploreFn)(graph_t *g,uint *counter,label_t u))
{
    int i;
    uint counter=0;
    assert(g!=NULL);
    assert(exploreFn!=NULL);
    assert(u>=0 && u<g->num_vertices);
    exploreFn(g,&counter,u);
    
    for (i=0;i<g->num_vertices;i++)
    {
            exploreFn(g,&counter,i);
    }

    return;
}







/*
 * @COMPLEXITY: O(mn), where n is the number of vertices
 * and m is the number of edges.
 *
 * The graph_print() function takes one argument only,
 * a graph_t data structure and prints the edges of the
 * graph in a triple format, ( u, v, weight ).It also 
 * prints if the graph is connected or not.
 *
 * @param:   graph_t    *g
 * @return:  void
 *
 */

void graph_print(graph_t *g)
{
    int i,j,flag;
    assert(g!=NULL);

    for (i=0;i<g->num_vertices;i++)
    {
        for (j=0;j<g->vertices[i].num_edges;j++)
        {
            if (g->vertices[i].edges[j].weight!=(void *)(-1))
            {
                printf("( %d, %d, weight = ",g->vertices[i].u,g->vertices[i].edges[j].v);
                g->print(g->vertices[i].edges[j].weight);
                printf(" )\n");
            }
        }
    }

    flag=graph_isConnected(g);
    
    if (flag==1)
    {
        printf("Graph is Connected\n");
    }
    else
    {
        printf("Graph is not connected\n");
    }


    return;
}






/*
 * @COMPLEXITY: O(mn), where n is the number of vertices
 * and m is the number of edges.
 *
 * The function graph_free() takes only one argument,
 * a graph_t data structure and deallocates memory for all
 * it's components and itself.If the destroy component of the
 * graph is not null then the weight component of the edge_t
 * datatypes is deallocated as well.
 *
 * @param:   graph_t    *g
 * @return:  void
 *
 */

void graph_free(graph_t *g)
{
    int i,j;
    assert(g!=NULL);

    for (i=0;i<g->num_vertices;i++)
    {
        if (g->destroy!=NULL)
        {
            for (j=0;j<g->vertices[i].num_edges;j++)
            {
                g->destroy(g->vertices[i].edges[j].weight);
                g->vertices[i].edges[j].weight=NULL;
            }
        }

        free(g->vertices[i].edges);
        g->vertices[i].edges=NULL;
    }

    free(g->vertices);
    g->vertices=NULL;
    free(g);
    g=NULL;
}

