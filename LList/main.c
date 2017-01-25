#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"



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


int main(int argc,char *argv[])
{
    time_t seed;
    void **temp=NULL;
    list_t *list=NULL; lluint i;
    srand((lluint )time(&seed));
    list=list_create(compare_lluints,print_lluint,NULL);

    for (i=0;i<10;i++)
    {
        temp=(void **)&i;
        list_append(list,*temp);
        printf("size = %lld ",list_getSize(list));
        list_print(list);
    }
    

    while (!list_isEmpty(list))
    {
        list_removeAt(list,0);
    }


    int j=2000;
    while (j>=0)
    {
        list_removeFoot(list);
        list_removeHead(list);
        j--;
    }



    list_removeHead(list);
    list_removeHead(list);
    list_removeHead(list);
    list_print(list);
    printf("the size of the list is: %lld\n",list->size);
    list_free(list);
    return 0;
}

