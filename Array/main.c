#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "array.h"




int     strings_compare(const void *s1,const void *s2);
void    string_print(const void *s);
void    string_destroy(void *s);
int     get_word(char *w,int limit);



int main(int argc,char *argv[])
{
    int length; char word[100];
    char *temp_string=NULL; array_t *array=NULL;
    array=array_create(strings_compare,string_print,string_destroy);
    
    while (get_word(word,10)!=EOF)
    {
        length=strlen(word)+1;
        temp_string=(char *)malloc(length*sizeof(char ));
        assert(temp_string!=NULL);
        strcpy(temp_string,word);
        array_insert(array,temp_string);
    }

    array_print(array);
    array_free(array);
    return 0;
}



int strings_compare(const void *s1,const void *s2)
{
    char *ss1=NULL,*ss2=NULL;
    ss1=(char *)s1;
    ss2=(char *)s2;
    return strcmp(ss1,ss2);
}


void string_print(const void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    printf("\"%s\"",ss);
    return;
}


void string_destroy(void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    free(ss); ss=NULL;
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
