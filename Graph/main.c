#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "random.h"
#include "graph.h"



#define MAXCHARS    20
#define MAXKEY      100




int compare_lluints(const void *l1,const void *l2)
{
    lluint *ll1=NULL,*ll2=NULL;
    ll1=(lluint *)&l1;
    ll2=(lluint *)&l2;

    if (*ll1<*ll2)  { return -1; }
    if (*ll1==*ll2) { return  0; }
    if (*ll1>*ll2)  { return  1; }
    return 0;
}


void print_lluint(const void *l)
{
    lluint *ll=NULL;
    ll=(lluint *)&l;
    printf("%lld",*ll);
    return;
}


char *random_string_generate(lluint length)
{
    lluint i;
    assert(length>=0);
    char *new_string=NULL;
    new_string=(char *)malloc((length+1)*sizeof(*new_string));
    assert(new_string!=NULL);

    for (i=0;i<length;i++)
    {
        new_string[i]=65+(unsigned )genrand64_int64()%26;
    }

    new_string[length]='\0';
    return new_string;
}



int compare_strings(const void *s1,const void *s2)
{
    char *ss1=NULL,*ss2=NULL;
    ss1=(char *)s1;
    ss2=(char *)s2;
    return strcmp(ss1,ss2);
}


void print_string(const void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    printf("%s",ss);
    return;
}


void deallocate_string(void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    free(ss); ss=NULL;
    return;
}



lluint hash_string_calculate(hashfn_t *h,const void *key)
{
    uint i,step=0,hval=0;
    char *string=NULL;
    uint kvalue,table_size;
    assert(h!=NULL && key!=NULL);
    string=(char *)key;
    kvalue=hashfn_getK(h);
    table_size=hashfn_getTableSize(h);

    for (i=0;string[i]!='\0';i++)
    {
        hval+=string[i]*h->values[step];
        if (step==kvalue) { step=0; }
        step++;

    }

    return (hval%table_size);
}



void depth_first_search(vertex_t *vv,lluint *counter)
{
    lluint i; int flag;
    vertex_t *adj=NULL;
    edge_t **edges_array=NULL;
    vertex_visited(vv);
    vv->previsit=*counter;
    *counter=*counter+1;
    edges_array=vertex_arrayEdges(vv);

    for (i=0;i<vv->num_edges;i++)
    {
        adj=(vertex_t *)edge_getEndPoint(edges_array[i]);
        flag=vertex_isVisited(adj);
        if (flag==0) { depth_first_search(adj,counter); }
    }
    
    vv->postvisit=*counter;
    *counter=*counter+1;
    free(edges_array);
    return;
}
        


int get_word(char *W,int limit)
{
    int c,len=0;    
    while ((c=getchar())!=EOF && !isalpha(c)) {}
    if (c==EOF) { return EOF; }
    *(W+len)=c; len++;  
    while (len<limit && (c=getchar())!=EOF && isalpha(c))
    {
        *(W+len)=c;
        len++;  
    }

    *(W+len)='\0';  
    return 0;   
}



int graph_readFile(graph_t *graph)
{
    lluint total_vertices,step=0;
    assert(graph!=NULL);
    char one_word1[MAXCHARS+1];
    char one_word2[MAXCHARS+1];
    if (scanf("%lld",&total_vertices)!=EOF);

    while (get_word(one_word1,MAXCHARS)!=EOF)
    {
        if (step<total_vertices)
        {
            if (!graph_hasVertex(graph,one_word1))
            {
                char *new_id=NULL;
                int length=strlen(one_word1);
                new_id=(char *)malloc((length+1)*sizeof(char ));
                assert(new_id!=NULL);
                strcpy(new_id,one_word1);
                vertex_t *new_vertex=NULL;
                new_vertex=vertex_create(new_id,hash_string_calculate,
                    compare_strings,print_string,deallocate_string);
                graph_addVertex(graph,new_vertex);
            }

            step++;
        }
        else
        {
            get_word(one_word2,MAXCHARS);
            if (!graph_hasEdge(graph,one_word1,one_word2))
            {
                vertex_t *v1=graph_getVertex(graph,one_word1);
                vertex_t *v2=graph_getVertex(graph,one_word2);
                edge_t *new_edge=NULL;
                new_edge=edge_create(NULL,v2,compare_strings,
                    print_string,deallocate_string);
                graph_addEdge(graph,v1->ident,v2->ident,new_edge);
            }
        }
    }

    return 1;
}




int main(int argc,char *argv[])
{
    time_t seed;
    graph_t *graph=NULL;
    init_genrand64((lluint )time(&seed));
    graph=graph_create(DIRECTED_GRAPH,hash_string_calculate,depth_first_search);
    graph_readFile(graph);
    graph_explore(graph,"A");
    graph_print(graph);
    graph_free(graph);
    return 0;
}
