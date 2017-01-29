/*
 * This file contains function definitions
 * of procedures regarding the graph data
 * structure and the operations associated
 * with it.
 *
 * @author: Endri Kastrati
 * @date:   27/01/2017
 *
 */




/*
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertions library and the
 * header file graph.h that contains datatype
 * definitions and function prototyping about
 * the graph data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"






/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function compare_vertices(),takes two pointers
 * to some immutable data.This is a dummy function for comparing
 * the addresses of the two vertex data structures it does nothing
 * but it is a prerequisited for creating a value_t data structure
 * that has the address of the vertex_t as a value.
 *
 * @param:  const void      *v1
 * @param:  const void      *v2
 * @return: int
 *
 */

static int compare_vertices(const void *v1,const void *v2)
{

    // Dummy functions,but here is a nice
    // way on how to check if the given
    // address of vertex_t types are the
    // same or not.
    vertex_t *vv1=NULL,*vv2=NULL;
    vv1=(vertex_t *)v1;
    vv2=(vertex_t *)v2;
    if (vv1<vv2)  { return -1; }
    if (vv1==vv2) { return  0; }
    if (vv1>vv2)  { return  1; }
    return 0;
}




/*
 * @COMPLEXITY: O(m*f(n)) where f(n) is the function
 *              that describes the asymptotic 
 *              complexity of the datatype that
 *              the vertex data structure will print
 *              and m is the size of the hash table
 *              of the vertex that contains the edges.
 * 
 * The static function print_vertex(),takes a pointer
 * to some constant data and casts it into a vertex_t
 * data structure.Once the casting has been completed
 * the vertex is printed by invoking the vertex_print()
 * function.
 *
 * @param:  const void  *v
 * @return: void
 *
 */

static void print_vertex(const void *v)
{
    vertex_t *vv=NULL;
    vv=(vertex_t *)v;
    vertex_print(vv);
    return;
}




/*
 * @COMPLEXITY: O(m) where m is the size of the
 *              hash table that contains the edges
 *              that radiate outwards from the given
 *              vertex data structure.
 *
 * The static function destroy_vertex(),takes a pointer
 * to some immutable data and casts it into a vertex_t
 * data structure.Once the casting has been completed
 * the memory chunk associated with this vertex_t datatype
 * is deallocated.
 *
 * @param:  void    *
 * @return: void
 *
 */

static void destroy_vertex(void *v)
{
    vertex_t *vv=NULL;
    vv=(vertex_t *)v;
    vertex_free(vv);
    return;
}


//////////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////





/*
 * @COMPLEXITY: O(m) where m is the initial size of
 *              the hash table data structure.
 * 
 * The function graph_create(),takes three arguments
 * as parameters.The first argument is an integer
 * that indicates the type of graph to create,namely
 * DIRECTED_GRAPH or UNDIRECTED_GRAPH.The second one
 * is a function pointer to a hash function associated
 * with the vertex identification type.The last one is
 * a function pointer to a procedure that specifies how
 * to explore this graph data structure.This function
 * creates a new graph_t data structure and allocates
 * memory for it and it's components and instantiates
 * them to their default values.
 *
 * @param:  int                 type
 * @param:  CuckooHashFn        hash
 * @param:  GraphExploreFn      explore
 * @return: graph_t             *
 *
 */

graph_t *graph_create(int type,CuckooHashFn hash,GraphExploreFn explore)
{
    graph_t *new_graph=NULL;
    assert(type==DIRECTED_GRAPH || type==UNDIRECTED_GRAPH);
    new_graph=(graph_t *)malloc(sizeof(*new_graph));
    assert(new_graph!=NULL);
    new_graph->vertices=cuckoo_create(hash);
    new_graph->num_vertices=0;
    new_graph->total_num_edges=0;
    new_graph->connected=0;
    new_graph->type=type;
    new_graph->explore=explore;
    return new_graph;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_setExplorer(),takes two arguments
 * as parameters.The first argument is graph_t data
 * structure and the second one a function pointer to
 * a new graph exploration procedure.This function changes
 * the old explore function with the supplied one.
 *
 * @param:  graph_t             *graph
 * @param:  GraphExploreFn      explore
 * @return: void
 *
 */

void graph_setExplorer(graph_t *graph,GraphExploreFn explore)
{
    assert(graph!=NULL);
    graph->explore=explore;
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_addVertex(),takes two arguments
 * as parameters.The first argument is a graph_t data
 * structure and the second one is a vertex_t data
 * structure.This function checks first if the given
 * vertex id exists in the hash table.If it does exist
 * nothing happens.Otherwise the vertex data structure
 * is inserted into the hash table with key it's ident
 * component and value it's memory address.This operation
 * is really fast as it takes only constant time to insert
 * elements into the cuckoo hash table data structure.
 *
 * @param:  graph_t     *graph
 * @param:  vertex_t    *vertex
 * @return: void
 *
 */

void graph_addVertex(graph_t *graph,vertex_t *vertex)
{
    cue_t *new_cue=NULL;
    value_t *new_value=NULL;
    pair_t *new_pair=NULL;
    assert(graph!=NULL && vertex!=NULL);
    if (graph_hasVertex(graph,vertex->ident)) { return; }
    new_cue=cue_create(vertex->ident,vertex->cmp,vertex->print,NULL);
    new_value=value_create(vertex,compare_vertices,print_vertex,destroy_vertex);
    new_pair=pair_create(new_cue,new_value);
    cuckoo_insert(graph->vertices,new_pair);
    graph->num_vertices=graph->vertices->n;
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_hasVertex(),takes two arguments
 * as parameters.The first argument is a graph_t data
 * structure and the second one a void pointer to some
 * type of identification value.This function checks
 * if the given key exists in the cuckoo hash table or
 * not.If the key exists then it returns the value of one
 * otherwise it returns the value of zero.This operation
 * is really fast as it takes only constant time to query
 * elements into the cuckoo hash table data structure.
 *
 * @param:  graph_t         *graph
 * @param:  void            *ident
 * @return: int
 *
 */

int graph_hasVertex(graph_t *graph,void *ident)
{
    int query;
    assert(graph!=NULL);
    query=cuckoo_lookup(graph->vertices,ident);
    return query;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_getVertex(),takes two arguments
 * as parameters.The first argument is a graph_t data
 * structure and the second one a void pointer to some
 * type of identification value.This function searches
 * the hash table for the given key value.If the key
 * exists it returns the value associated with it
 * otherwise it returns null.This operation is really
 * fast as it takes only constant time to retrieve the
 * value component of a key into the cuckoo hash table
 * data structure.
 *
 * @param:  graph_t     *graph
 * @param:  void        *ident
 * @return: vertex_t    *
 *
 */

vertex_t *graph_getVertex(graph_t *graph,void *ident)
{
    assert(graph!=NULL);
    return (vertex_t *)cuckoo_getValue(graph->vertices,ident);
}




/*
 * @COMPLEXITY: O(V) where V is the total number of
 *              vertices in the graph if the type
 *              is directed.
 *              O(E) worst case,where E is the total
 *              number of edges in the graph if the
 *              type is undirected.
 * 
 * The function graph_removeVertex(),takes two arguments
 * as parameters.The first argument is a graph_t data
 * structure and the second one a pointer to some type
 * of identification value.This function firstly,checks
 * if the given id exists in the table.If the key does
 * not exist nothing happens.If the key exists we retrieve
 * the vertex address associated with it and if the type
 * of the graph is directed we iterate over the entire
 * vertices table and remove from each vertex the edges
 * that point to the given id.If the type of the graph
 * is undirected then we only iterate over the table of
 * edges of the particular vertex,go through each endpoint
 * and remove from their edge's table the given id.
 * Once all edges associated with this vertex id have been
 * removed the vertex itself is deleted from the graph.
 * This operation can be very expensive computationally
 * if the type is directed.However if the type is undirected,
 * and not all edges point to the particular vertex,it can
 * be reasonably fast.In general this function does not have
 * constant time operability so it is reccomended to use only
 * when necessary.
 *
 * @param:  graph_t     *graph
 * @param:  void        *ident
 * @return: void
 *
 */

void graph_removeVertex(graph_t *graph,void *ident)
{
    int query; lluint i;
    assert(graph!=NULL); value_t *temp_value=NULL;
    vertex_t *temp_vertex=NULL,*adj_vertex=NULL;
    pair_t *temp_pair=NULL; cue_t *temp_cue=NULL;
    query=cuckoo_lookup(graph->vertices,ident);
    if (query==0) { return; }
    
    if (graph->type==DIRECTED_GRAPH)
    {
        for (i=0;i<graph->vertices->size;i++)
        {
            temp_pair=graph->vertices->T1[i];
            if (temp_pair!=NULL)
            {
                temp_value=pair_getValue(temp_pair);
                temp_vertex=value_get(temp_value);
                vertex_removeEdge(temp_vertex,ident);
            }

            temp_pair=graph->vertices->T2[i];
            if (temp_pair!=NULL)
            {
                temp_value=pair_getValue(temp_pair);
                temp_vertex=value_get(temp_value);
                vertex_removeEdge(temp_vertex,ident);
            }
        }

        cuckoo_remove(graph->vertices,ident);
        graph->num_vertices=graph->vertices->n;
    }
    else
    {
        temp_vertex=graph_getVertex(graph,ident);
        for (i=0;i<temp_vertex->edges->size;i++)
        {
            temp_pair=temp_vertex->edges->T1[i];
            if (temp_pair!=NULL)
            {
                temp_cue=pair_getCue(temp_pair);
                adj_vertex=graph_getVertex(graph,cue_get(temp_cue));
                vertex_removeEdge(adj_vertex,ident);
                adj_vertex->inflow_edges--;
            }

            temp_pair=temp_vertex->edges->T2[i];
            if (temp_pair!=NULL)
            {
                temp_cue=pair_getCue(temp_pair);
                adj_vertex=graph_getVertex(graph,cue_get(temp_cue));
                vertex_removeEdge(adj_vertex,ident);
                adj_vertex->inflow_edges--;
            }
        }

        cuckoo_remove(graph->vertices,ident);
        graph->num_vertices=graph->vertices->n;
    }

    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_addEdge(),takes four arguments as parameters.
 * The first argument is a graph_t data structure.The next two are
 * pointers to some type of vertex identifications representing an
 * edge (ident1,ident2).The last argument is an edge_t data structure.
 * This function firstly,checks if the given (ident1,ident2) exist as
 * an edge data structure in the graph.If yes,then nothing happens.
 * If the edge does not exist it is inserted into the graph.Firstly
 * the given edge data structure is inserted into the vertex's hash
 * table that is associated with the ident1 value.If the type of graph
 * is undirected then a mirror edge data structure is created as well
 * and inserted into the vertex's hash table associated with the ident2
 * value.This operation is really fast as it takes costant time to lookup
 * and insert items into the cuckoo hash table data structure.
 *
 * @param:  graph_t         *graph
 * @param:  void            *ident1
 * @param:  void            *ident2
 * @param:  edge_t          *edge
 * @return: void
 *
 */

void graph_addEdge(graph_t *graph,void *ident1,void *ident2,edge_t *edge)
{
    int query;
    void *mirror_endpoint=NULL;
    void *mirror_weight=NULL;
    edge_t *mirror_edge=NULL;
    vertex_t *temp_vertex1=NULL;
    vertex_t *temp_vertex2=NULL;
    assert(graph!=NULL && edge!=NULL);
    query=graph_hasEdge(graph,ident1,ident2);
    if (query==1) { return; }

    temp_vertex1=graph_getVertex(graph,ident1);
    temp_vertex2=graph_getVertex(graph,ident2);
    assert(temp_vertex2==edge_getEndPoint(edge));
    vertex_addEdge(temp_vertex1,ident2,edge);
    temp_vertex2->inflow_edges++;

    if (graph->type==UNDIRECTED_GRAPH)
    {
        mirror_weight=edge_getWeight(edge);
        mirror_endpoint=temp_vertex1;
        mirror_edge=edge_create(mirror_weight,mirror_endpoint,
            edge->cmp,edge->print,edge->destroy);
        vertex_addEdge(temp_vertex2,ident1,mirror_edge);
        temp_vertex1->inflow_edges++;
    }
    
    graph->total_num_edges++;
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_hasEdge(),takes three arguments
 * as parameters.The first argument is a graph_t data
 * structure and the rest are pointers to some type of
 * vertex identification values.This function checks 
 * whether the edge (ident1,ident2) exists in the graph
 * data structure.It it does exist it returns one,otherwise
 * it returns zero.This operation is really fast as it takes
 * only constant time to lookup into the cuckoo hash table
 * data structure.
 *
 * @param:  graph_t     *graph
 * @param:  void        *ident1
 * @param:  void        *ident2
 * 
 */

int graph_hasEdge(graph_t *graph,void *ident1,void *ident2)
{
    int query1,query2,query;
    vertex_t *temp_vertex=NULL;
    assert(graph!=NULL);
    query1=graph_hasVertex(graph,ident1);
    if (query1==0) { return 0; }
    query2=graph_hasVertex(graph,ident2);
    if (query2==0) { return 0; }
    temp_vertex=graph_getVertex(graph,ident1);
    query=vertex_hasEdge(temp_vertex,ident2);
    return query;
}






/*
 * @COMPLEXITY: Theta(1)
 *
 * The function graph_getEdge(),takes three arguments
 * parameters.The first argument is a graph_t data
 * structure and the rest are two pointers to some type
 * of vertex identification values.This function returns
 * the edge_t data structure associated with the given
 * (ident1,ident2) values.If the edge does not exist then
 * null is returned instead.This operation is really fast
 * as it takes constant time to perform lookups into the
 * cuckoo hash table data structure.
 *
 * @param:  graph_t     *graph
 * @param:  void        *ident1
 * @param:  void        *ident2
 * return:  edge_t      *
 *
 */

edge_t *graph_getEdge(graph_t *graph,void *ident1,void *ident2)
{
    vertex_t *temp_vertex=NULL;
    edge_t *temp_edge=NULL;
    assert(graph!=NULL);
    if (!graph_hasEdge(graph,ident1,ident2)) { return NULL; }
    temp_vertex=graph_getVertex(graph,ident1);
    temp_edge=vertex_getEdge(temp_vertex,ident2);
    return temp_edge;
}



/*
 * COMPLEXITY: Theta(1)
 *
 * The function graph_removeEdge(),takes three arguments
 * as parameters.The first argument is a graph_t data
 * structure and the rest two are pointers to some type
 * of vertex identification values.This function checks
 * if the edge exists in the graph.If the edge does not
 * exist then nothing happens,otherwise it is deleted
 * from the vertex's hash table associated with the ident1 value.
 * If the type of the graph is undirected then the mirror edge
 * is also deleted from the vertex's hash table associated with
 * the ident2 value.This operation is really fast as it takes
 * only constant time to lookup and remove items from the cuckoo
 * hash table data structure.
 *
 * @param:  graph_t     *graph
 * @param:  void        *ident1
 * @param:  void        *ident2
 * @return: void
 *
 */

void graph_removeEdge(graph_t *graph,void *ident1,void *ident2)
{
    vertex_t *temp_vertex1=NULL;
    vertex_t *temp_vertex2=NULL;
    assert(graph!=NULL);
    if (!graph_hasEdge(graph,ident1,ident2)) { return; }
    temp_vertex1=graph_getVertex(graph,ident1);
    temp_vertex2=graph_getVertex(graph,ident2);
    vertex_removeEdge(temp_vertex1,ident2);
    temp_vertex2->inflow_edges--;

    if (graph->type==UNDIRECTED_GRAPH)
    {
        vertex_removeEdge(temp_vertex2,ident1);
        temp_vertex1->inflow_edges--;
    }
    
    graph->total_num_edges--;
    return;
}





/*
 * @COMPLEXITY: O(f(n)) where f(n) is the function
 *              that describes the asymptotic complexity
 *              of the explore function implemented and
 *              provided by the user.
 * 
 * The function graph_explore(),takes two arguments as
 * parameters.The first argument is a graph_t data structure
 * and the second one a pointer to some type of identification
 * value.This function runs the exploration procedure provided
 * by the user, using as a starting point the vertex that matches
 * the given id, and them applying it to all the other vertices
 * of the graph as well.
 *
 * @param:  graph_t     *graph
 * @param:  void        *ident
 * @return: void
 *
 */

void graph_explore(graph_t *graph,void *ident)
{
    int query;
    lluint i,counter=0;
    vertex_t *curr_vertex=NULL;
    vertex_t **vertices_array=NULL;
    assert(graph!=NULL && graph->explore!=NULL);
    query=graph_hasVertex(graph,ident);
    assert(query==1);
    curr_vertex=graph_getVertex(graph,ident);
    graph->explore(curr_vertex,&counter);
    vertices_array=graph_arrayVertices(graph);

    for (i=0;i<graph->num_vertices;i++)
    {
        if (vertex_isVisited(vertices_array[i])==0)
            graph->explore(vertices_array[i],&counter);
    }
    
    free(vertices_array);
    return;
}




/*
 * @COMPLEXITY: O(m) where m is the size of
 *              the hash table data structure
 *              that contains the vertices of
 *              the graph.
 * 
 * The function graph_arrayVertices(),takes a graph_t
 * data structure as an argument loops through the 
 * entire hash table and returns an array of all the
 * vertices that exist in the current state of the
 * hash table.This function is computationally expensive
 * since we iterate over the entire hash table data structure.
 * The user bares the responsibility to deallocate memory for
 * the returned array.In the state of the graph data structure
 * changes,this function should be called again.
 *
 * @param:  graph_t     *graph
 * @return: vertex_t    **
 *
 */

vertex_t **graph_arrayVertices(graph_t *graph)
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
            temp_value=pair_getValue(temp_pair);
            vertices_array[step++]=value_get(temp_value);
        }

        temp_pair=graph->vertices->T2[i];
        if (temp_pair!=NULL)
        {
            temp_value=pair_getValue(temp_pair);
            vertices_array[step++]=value_get(temp_value);
        }
    }

    return vertices_array;
}




/*
 * @COMPLEXITY: O(m*n*f(n)) where m is the current
 *              size of the hash table that contains
 *              the vertices and n is the size of the
 *              hash table of the vertex data structure
 *              that has the largest number of edges 
 *              associated with it.f(n) is the function
 *              that describes the asymptotic complexity
 *              of the printing procedure for the particular
 *              datatype.
 * 
 * The function graphp_print(),takes a graph_t data structure
 * as an argument,iterates over the entire hash table and
 * prints each vertex data structure in a user-friendly
 * format.
 *
 * @param:  graph_t     *graph
 * @return: void
 *
 */

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

    return;
}




/*
 * @COMPLEXITY: O(m*n) where m is the current size of
 *              the hash table that contains the vertices
 *              and n is the size of the hash table of the
 *              vertex data structure that has the largest
 *              number of edges associated with it.
 * 
 * The function graph_free(),takes a graph_t data structure
 * as an argument and deallocates memory for it and it's
 * components,including the vertices and edges contained
 * in the graph.
 *
 * @param:  graph_t     *graph
 * @return: void
 *
 */

void graph_free(graph_t *graph)
{
    assert(graph!=NULL);
    cuckoo_free(graph->vertices);
    graph->vertices=NULL;
    free(graph); graph=NULL;
    return;
}

