
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pair.h"



int compare_longs(const void *l1,const void *l2)
{
    long *ll1=NULL,*ll2=NULL;
    ll1=(long *)l1;
    ll2=(long *)l2;
    return (*ll1-*ll2);
}


void print_long(const void *l)
{
    long *ll=NULL;
    ll=(long *)l;
    printf("%ld",*ll);
    return;
}



int compare_strings(const void *s1,const void *s2)
{
    char *ss1=NULL, *ss2=NULL;
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


void destroy_long(void *l)
{
    assert(l!=NULL);
    free(l); l=NULL;
    return;
}




int main(int argc,char *argv[])
{
    cue_t *new_cue=NULL;
    value_t *new_value=NULL;
    pair_t *new_pair=NULL;
    long *age1=(long *)malloc(sizeof(long ));
    long *age2=(long *)malloc(sizeof(long ));
    *age1=25; *age2=23;

    new_cue=cue_create("endri",compare_strings,print_string,NULL);
    new_value=value_create((void *)age1,compare_longs,print_long,destroy_long);
    new_pair=pair_create(new_cue,new_value); pair_print(new_pair);
    pair_changeValue(new_pair,value_create((void *)age2,compare_longs,print_long,destroy_long));
    pair_print(new_pair);
    pair_changeCue(new_pair,cue_create("gresia",compare_strings,print_string,NULL));
    pair_print(new_pair);
    pair_free(new_pair);
    return 0;
}
