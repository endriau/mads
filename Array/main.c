/*
 * Including the standard input-output library, the standard utilities library,the standard
 * assertions library,the standard string library, the standard types library and the "array.h" 
 * header file that contains data type definitions and function prototypings regarding the
 * array data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "array.h"



/*
 * Function prototypings of the string comparison,
 * string printing and string dellocation functions,
 * as well as the word reading function.
 *
 */

int     strings_compare(const void *s1,const void *s2);
void    string_print(const void *s);
void    string_destroy(void *s);
int     get_word(char *w,int limit);



/*
 * Main exeuction program,creates a new array
 * data structure that will store strings.This
 * function reads words from the standard input
 * and stores them into the array.Once the reading
 * of words has been completed the current state
 * of the array is printed and then destroyed
 * along with the strings in it.
 *
 */

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



/*
 * @COMPLEXITY: O(n)    Where n is the length of the smallest string
 *
 * The function string_compare() take two immutable void
 * pointers as arguments and casts them into pointers to
 * chars.Once the casting has been completed it compares
 * them using the strcmp() function from the standard
 * string library and returns the result.
 *
 * @param:  const void      *s1
 * @param:  const void      *s2
 * @return: int
 *
 */

int strings_compare(const void *s1,const void *s2)
{
    char *ss1=NULL,*ss2=NULL;
    ss1=(char *)s1;
    ss2=(char *)s2;
    return strcmp(ss1,ss2);
}




/*
 * @COMPLEXITY: O(n)    Where n is the length of the string
 *
 * The function string_print() takes one immutable void
 * pointer as argument and casts it into a pointer to a
 * char.Once the casting has been completed it prints
 * the string into the standard output stream.
 *
 * @param:  const void      *s
 * @return: void
 *
 */

void string_print(const void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    printf("\"%s\"",ss);
    return;
}



/*
 * @COMPLEXITY; Theta(1)
 *
 * The function string_destroy() takes a void pointer
 * as parameter and casts it into a pointer to a char.
 * Once casting has been completed it deallocates all
 * memory blocks associated with that pointer.
 *
 * @param:  void    *s
 * @return: void
 *
 */

void string_destroy(void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    free(ss); ss=NULL;
    return;
}





/*
 * The function get_word() takes two arguments as parameters.
 * The first one is a pointer to a char and the second one
 * is the limit of characters the given array can have.
 * This function reads characters from the standard input
 * until a word has been read or the end of file.It returns
 * zero if a word was read successfully and end of file if
 * there is no more input.
 *
 * @param:  char        *W
 * @param:  int         limit
 * @return: int
 *
 */

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
