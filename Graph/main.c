#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "graph.h"
#include "../Heap/heap.h"


int double_compare(const void *a,const void *b)
{
    return 0;
}


void print_doubles(const void *w)
{
    long *temp=NULL;
    temp=(long *)&w;
    printf("%ld",*temp);
    return;
}


void exploreDFS(graph_t *g,uint *counter,label_t u)
{
    uint n,i;
    time_t t;
    assert(g!=NULL);
    if (g->vertices[u].visited==1) { return; }
    g->vertices[u].visited=1;
    edge_t *edges=graph_getEdges(g,u,&n);
    g->vertices[u].previsit=*counter;
    *counter=*counter+1;
    srand((unsigned )time(&t));

    if (n>=1)
    {
        for (i=0;i<1000;i++)
        {
            int r1=random()%n;
            int r2=random()%n;
            edge_t temp_edge;
            temp_edge=edges[r1];
            edges[r1]=edges[r2];
            edges[r2]=temp_edge;
        }
    }

    for (i=0;i<n;i++)
    {
        exploreDFS(g,counter,edges[i].v);
    }

    g->vertices[u].postvisit=*counter;
    *counter=*counter+1;
    return;
}



int hcompare_postvisits(const void *ps1,const void *ps2)
{
    vertex_t *pss1=NULL,*pss2=NULL;
    pss1=(vertex_t *)ps1;
    pss2=(vertex_t *)ps2;

    if (pss1->postvisit>pss2->postvisit)
    {
        return 1;
    }
    else if (pss1->postvisit<pss2->postvisit)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


void hprint_postvisits(const void *ps1)
{
    vertex_t *pss1=NULL;
    pss1=(vertex_t *)ps1;
    printf("( vertex = %u, postvisit = %u )",pss1->u,pss1->postvisit);
    return;
}




int main(int argc,char *argv[])
{
    int i,n;
    void **temp=NULL;
    long *var=(long *)malloc(sizeof(long));
    assert(var!=NULL);
    uint number_of_vertices=7;
    graph_t *new_graph=NULL;
    new_graph=graph_create("graph1",number_of_vertices,
                    double_compare,print_doubles,NULL);
    graph_add_edge(new_graph,NULL,0,1);
    graph_add_edge(new_graph,NULL,0,3);
    graph_add_edge(new_graph,NULL,0,6);
    graph_add_edge(new_graph,NULL,1,2);
    graph_add_edge(new_graph,NULL,2,3);
    graph_add_edge(new_graph,NULL,2,4);
    graph_add_edge(new_graph,NULL,3,4);
    graph_add_edge(new_graph,NULL,4,5);
    graph_add_edge(new_graph,NULL,5,6);

    /*for (i=0;i<new_graph->num_vertices;i++)
    {
        printf("( vertex = %u, { previsit = %u, postvisit = %u }\n",
            new_graph->vertices[i].u,new_graph->vertices[i].previsit,
            new_graph->vertices[i].postvisit);
    }*/


    //graph_print(new_graph);
    graph_explore(new_graph,0,exploreDFS);
    heap_t *heap=heap_create(MAX_HEAP,hcompare_postvisits,hprint_postvisits,NULL);
    vertex_t *vertices=graph_getVertices(new_graph,&n);
    for (i=0;i<n;i++)
    {
        heap_insert(heap,(vertices+i));
    }

    heap_print(heap);
    heap_free(heap);
    graph_free(new_graph);
    free(var);
    return 0;
}
