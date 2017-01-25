#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "cuckootable.h"

#define MAXCHARS    20
#define MAXKEY      100


int     compare_strings(const void *s1,const void *s2);
void    print_string(const void *s);
void    destroy_string(void *s);
int     compare_longs(const void *l1,const void *l2);
void    print_long(const void *l);
void    destroy_long(void *l);
lluint  hash_string_calculate(hashfn_t *h,const void *key);
int     get_word(char *A,int limit);





int main(int argc,char *argv[])
{
    time_t seed; int length; //long *temp_long=NULL;
    char *temp_string=NULL; cuckoo_t *table=NULL;
    cue_t *temp_key=NULL; value_t *temp_value=NULL;
    pair_t *temp_pair=NULL; char one_word[MAXCHARS+1];
    srand((unsigned int )time(&seed));
    table=cuckoo_create(hash_string_calculate);
    
    while (get_word(one_word,MAXCHARS)!=EOF)
    {

        if (cuckoo_lookup(table,one_word)==0)
        {
            length=strlen(one_word);
            temp_string=(char *)malloc((length+1)*sizeof(char ));
            assert(temp_string!=NULL);
            strcpy(temp_string,one_word);
            // temp_long=(long *)malloc(sizeof(long ));
            // *temp_long=rand()%MAXKEY;
            temp_key=cue_create(temp_string,compare_strings,
                            print_string,destroy_string);

            long value=rand()%100;
            void **temp=NULL; temp=(void **)&value;
            temp_value=value_create(*temp,compare_longs,
                            print_long,NULL);
            temp_pair=pair_create(temp_key,temp_value);
            cuckoo_insert(table,temp_pair);
            // // printf("\n\n\n\n");
            // cuckoo_print(table);
            // temp_string=NULL;
            // temp_long=NULL;
        }
    }
    
    cuckoo_print(table);
    cuckoo_free(table);
    return 0;
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



void destroy_string(void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    free(ss); ss=NULL;
    return;
}




int compare_longs(const void *l1,const void *l2)
{
    long *ll1=NULL,*ll2=NULL;
    ll1=(long *)&l1;
    ll2=(long *)&l2;
    return (*ll1-*ll2);
}


void print_long(const void *l)
{
    long *ll=NULL;
    ll=(long *)&l;
    printf("%ld",*ll);
    return;
}




void destroy_long(void *l)
{
    long *ll=NULL;
    ll=(long *)l;
    free(ll); ll=NULL;
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
