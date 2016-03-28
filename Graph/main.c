#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"


int double_compare(const void *a,const void *b)
{
    return 1;
}


void print_doubles(const void *w)
{
    long *temp=NULL;
    temp=(long *)&w;
    printf("%ld",*temp);
    return;
}




int main(int argc,char *argv[])
{
    int i;
    void **temp=NULL;
    long *var=(long *)malloc(sizeof(long));
    assert(var!=NULL);
    uint number_of_vertices=4;
    graph_t *new_graph=NULL;
    new_graph=graph_create("graph1",number_of_vertices,
                    double_compare,print_doubles,NULL);

    *var=50;
    temp=(void **)var;
    graph_add_edge(new_graph,*temp,0,1);
    graph_add_edge(new_graph,*temp,1,0);

    *var=100;
    temp=(void **)var;
    graph_add_edge(new_graph,*temp,0,2);
    graph_add_edge(new_graph,*temp,2,0);

    *var=300;
    temp=(void **)var;
    graph_add_edge(new_graph,*temp,2,3);
    graph_add_edge(new_graph,*temp,3,2);

    graph_del_edge(new_graph,3,2);
    graph_print(new_graph);
    graph_free(new_graph);
    free(var);
    return 0;
}
