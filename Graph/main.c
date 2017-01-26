#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "random.h"
#include "vertex.h"



int compare_lluint(const void *l1,const void *l2)
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



int main(int argc,char *argv[])
{
    vertex_t *v1,*v2,*v3;
    lluint weight1,weight2,weight3;
    weight1=100; weight2=200; weight3=40;
    edge_t *e12,*e13;
    time_t seed;
    init_genrand64((lluint )time(&seed));

    v1=vertex_create(random_string_generate(10),hash_string_calculate,
        compare_strings,print_string,deallocate_string);
    v2=vertex_create(random_string_generate(11),hash_string_calculate,
    compare_strings,print_string,deallocate_string);
    v3=vertex_create(random_string_generate(12),hash_string_calculate,
        compare_strings,print_string,deallocate_string);


    void **temp=NULL;
    temp=(void **)&weight2;
    e12=edge_create(*temp,v2,compare_lluint,print_lluint,NULL);
    temp=(void **)&weight2;
    temp=(void **)&weight3;
    e13=edge_create(*temp,v3,compare_lluint,print_lluint,NULL);
    



    vertex_addEdge(v1,v2->ident,e12);
    vertex_addEdge(v1,v3->ident,e13);

    printf("vertex has edge: %d\n",vertex_hasEdge(v1,v2->ident));
    edge_t *temp_edge=vertex_getEdge(v1,v2->ident);
    edge_print(temp_edge);
    printf("\n\n");
    
    edge_t **temp_edges=NULL;
    temp_edges=vertex_arrayEdges(v1);

    for (int i=0;i<v1->num_edges;i++)
    {
        edge_print(temp_edges[i]);
    }
    
    printf("\n");
    free(temp_edges);


    vertex_print(v1);
    printf("\n");
    vertex_removeEdge(v1,v3->ident);
    vertex_print(v1);
    printf("\n");
    vertex_free(v1);
    vertex_free(v2);
    vertex_free(v3);
    return 0;
}
