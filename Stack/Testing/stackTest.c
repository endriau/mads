/*
 * This file contains the definition
 * of testing procedures for the
 * stack data structure and the
 * functions associated with it.
 *
 * @author: Endri Kastrati
 * @date:   9/01/2017
 *
 */




/*
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertions library,the standard
 * string library and the header file stack.h
 * that contains the definition of the stack
 * data structure and the header file stackTest.h
 * that contains the definitions of testing functions
 * for the stack data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stackTest.h"




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function compare_llints(),takes as
 * arguments two addresses that point to some datatype
 * and casts them using the pseudo-address casting
 * method to pointers to long long ints.Once the
 * casting has been completed the reference values
 * of the pointers are compared  based on a
 * conditional statement.
 *
 * @param:  const void      *l1
 * @param:  const void      *l2
 * @return: int
 *
 */

static int compare_llints(const void *l1,const void *l2)
{
    long long int *ll1=NULL,*ll2=NULL;
    ll1=(long long int *)&l1;
    ll2=(long long int *)&l2;
    if (*ll1<*ll2)  { return -1; }
    if (*ll1==*ll2) { return  0; }
    if (*ll1>*ll2)  { return  1; }
    return 0;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function compare_alloc_llints(),takes as
 * arguments two addresses that point to some datatype
 * and casts them using the usual casting technique into
 * pointers to long long ints.Once the casting has been
 * completed the referenced values of the pointers are
 * compared based on a conditional statement.
 *
 * @param:  const void      *l1
 * @param:  const void      *l2
 * @return: int
 *
 */

static int compare_alloc_llints(const void *l1,const void *l2)
{
    long long int *ll1=NULL,*ll2=NULL;
    ll1=(long long int *)l1;
    ll2=(long long int *)l2;
    if (*ll1<*ll2)  { return -1; }
    if (*ll1==*ll2) { return  0; }
    if (*ll1>*ll2)  { return  1; }
    return 0;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function compare_doubles() takes as
 * arguments two addresses that point to some datatype
 * and casts them using the pseudo-address casting
 * technique into pointers to doubles.Once the casting
 * has been completed the referenced values of the pointers
 * are compared based on a conditional statement.
 *
 * @param:  const void      *d1
 * @param:  const void      *d2
 * @return: int
 *
 */

static int compare_doubles(const void *d1,const void *d2)
{
    double *dd1=NULL,*dd2=NULL;
    dd1=(double *)&d1;
    dd2=(double *)&d2;
    if (*dd1<*dd2)  { return -1; }
    if (*dd1==*dd2) { return  0; }
    if (*dd1>*dd2)  { return  1; }
    return 0;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function compare_alloc_doubles(),takes as
 * arguments two addresses that point to some datatype
 * and casts them using the usual casting technique into
 * pointers to doubles.Once the casting has been completed
 * the referenced values are compared based on a conditional
 * statement.
 *
 * @param:  const void      *d1
 * @param:  const void      *d2
 * @return: int
 *
 */

static int compare_alloc_doubles(const void *d1,const void *d2)
{
    double *dd1=NULL,*dd2=NULL;
    dd1=(double *)d1;
    dd2=(double *)d2;
    if (*dd1<*dd2)  { return -1; }
    if (*dd1==*dd2) { return  0; }
    if (*dd1>*dd2)  { return  1; }
    return 0;
}





/*
 * @COMPLEXITY: O(n)
 *
 * The static function compare_strings() takes as 
 * arguments two addresses to some datatypes and
 * casts them to pointer to chars.Once the casting
 * has been completed the referenced values of the
 * pointers are compared using the standard library
 * function strcmp().
 *
 * @param:  const void      *s1
 * @param:  const void      *s2
 * @return: int
 *
 */

static int compare_strings(const void *s1,const void *s2)
{
    char *ss1=NULL,*ss2=NULL;
    ss1=(char *)s1;
    ss2=(char *)s2;
    return strcmp(ss1,ss2);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function print_llint(),takes as
 * argument an address to some datatype and
 * casts it using the pseudo-address casting
 * technique into a pointer to long long int.
 * Once the casting has been completed the
 * referenced value of the pointer is printed.
 *
 * @param:  const void  *l
 * @return: void
 *
 */

static void print_llint(const void *l)
{
    long long int *ll=NULL;
    ll=(long long int *)&l;
    printf("%lld",*ll);
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function print_alloc_llint(),takes
 * as argument an address to some datatype and
 * casts it using the usual casting technique
 * into a pointer to long long int.Once the 
 * casting has been completed the referenced
 * value of the pointer is printed.
 *
 * @param:  const void  *l
 * @return: void
 *
 */

static void print_alloc_llint(const void *l)
{
    long long int *ll=NULL;
    ll=(long long int *)l;
    printf("%lld",*ll);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function print_doubles(),takes as
 * an argument an address to some datatype and
 * casts it using the pseudo-address casting 
 * technique into a pointer to double.Once the 
 * casting has been completed the referenced value
 * of the pointer is printed.
 *
 * @param:  const void  *d
 * @return: void
 *
 */

static void print_doubles(const void *d)
{
    double *dd=NULL;
    dd=(double *)&d;
    printf("%.5lf\n",*dd);
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function print_alloc_doubles(),takes
 * as an argument an address to some datatype and
 * casts it using the usual casting technique into
 * a pointer to a double.Once the casting has been
 * completed the referenced value of the pointer is
 * printed.
 *
 * @param:  const void  *d
 * @return: int
 *
 */

static void print_alloc_doubles(const void *d)
{
    double *dd=NULL;
    dd=(double *)d;
    printf("%.5lf\n",*dd);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function print_string(),takes
 * as argument an address to some datatype
 * and casts it using the usual casting
 * technique into a pointer to a char.
 * Once the casting has been completed
 * the referenced value of the pointer
 * is printed.
 *
 * @param:  const void  *s
 * @return: void
 *
 */

static void print_string(const void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    printf("%s",ss);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function destroy_llint(),
 * takes as an argument an address to
 * some datatype and deallocates the
 * memory chunk associated with it.
 *
 * @param:  void    *l
 * @return: void
 *
 */

static void destroy_llint(void *l)
{
    long long int *ll=NULL;
    ll=(long long int *)l;
    free(ll); ll=NULL;
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 * The static function destroy_double()
 * takes as an argument an address to
 * some datatype and deallocates the
 * memory chunk associated with it.
 *
 * @param:  void    *d
 * @return: void
 *
 */

static void destroy_double(void *d)
{
    double *dd=NULL;
    dd=(double *)d;
    free(dd); dd=NULL;
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function destroy_string(),takes
 * as an argument an address to some datatype
 * and deallocates the memory chunk associated
 * with it.
 *
 * @param:  void    *s
 * @return: void
 *
 */

static void destroy_string(void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    free(ss); ss=NULL;
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The static function print_pass()
 * takes no arguments as parameters
 * and prints a user-friendly success
 * message.
 *
 * @param:  void
 * @return: void
 *
 */

static void print_pass()
{
    fprintf(stderr,"["GRN" PASS "RESET"]\n");
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 * 
 * The static function print_fail(),
 * takes no arguments as parameters
 * and prints a user-friendly fail
 * message.
 *
 * @param:  void
 * @return: void
 *
 */

static void print_fail()
{
    fprintf(stderr,"["RED" FAIL "RESET"]\n");
    return;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The static function generate_random_string(),takes
 * as an argument the length of the string,and generated
 * a new string with random characters based on the given
 * length.
 *
 * @param:  int     length
 * @return: char    *
 *
 */

static char *generate_random_string(int length)
{
    assert(length>0);
    char *string=NULL; int i;
    string=(char *)malloc((length+1)*sizeof(*string));
    assert(string!=NULL);
    for (i=0;i<=length;i++)
    {
        string[i]=65+rand()%25;
    }

    string[length]='\0';
    return string;
}






// ..............Add more functions above this comment to include
// more helper functions for additional datatypes.
///////////////////////////////////////////////////////////////////////////////













/*
 * @COMPLEXITY: O(n) where n is the size of the given arrays.
 *
 * The function stack_create_test(),takes three arrays of 
 * function pointers and an array of strings and instantiates
 * an array of stacks based on those arguments.This function
 * tests the stack_create() procedure for all the different
 * given function pointers.
 *
 * @param:  StackCompareFn      *C
 * @param:  StackPrintFn        *P
 * @param:  StackDestroyFn      *D
 * @return: stack_t             **
 *
 */

stack_t **stack_create_test(StackCompareFn *C,StackPrintFn *P,StackDestroyFn *D,char *Messages[])
{
    int num=5;int fc=0,pc=0;
    stack_t **stacks=NULL;
    assert(C!=NULL && P!=NULL);
    assert(D!=NULL && Messages!=NULL);
    stacks=(stack_t **)malloc(num*sizeof(*stacks));
    assert(stacks!=NULL);
    fprintf(stderr,YEL "Initiating testing for the stack_create() procedure.\n"RESET);
    
    for (int i=0;i<num;i++)
    {
        fprintf(stderr,"\tstack_create(): %s",Messages[i]);
        stacks[i]=stack_create(C[i],P[i],D[i]);
        if (stacks[i]!=NULL)
        {
            print_pass(); pc++;
        }
        else
        {
            print_fail(); fc++;
        }
    }


    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n",pc,(pc+fc),fc,(fc+pc));
    fprintf(stderr,YEL "Terminating testing for the stack_create() procedure.\n"RESET);
    return stacks;
}







/*
 * @COMPLEXITY: O(n)
 *
 * The function stack_push_test(),takes an array of
 * stack data structures and an array of strings and
 * tests the stack_push() function on the array of
 * stacks for different values associated with each
 * stack on that array.
 *
 * @param:  stack_t     *Array[]
 * @param:  char        *Messages[]
 * @return: int
 *
 */

int stack_push_test(stack_t *Array[],char *Messages[])
{
    int pc=0,fc=0;
    assert(Array!=NULL && Messages!=NULL);
    long long int i,max=100000;
    fprintf(stderr,YEL "Initiating testing for the stack_push() procedure.\n"RESET);



    fprintf(stderr,"\tstack_push():   %s",Messages[0]);
    for (i=0;i<max;i++) 
    { 
        void **temp=NULL;
        long long int l=rand()%max;
        temp=(void **)&l;
        stack_push(Array[0],*temp); 
    }
    if ((Array[0]->n+1)==max)   { print_pass(); pc++; }
    else                        { print_fail(); fc++; }




    fprintf(stderr,"\tstack_push():   %s",Messages[1]);
    for (i=0;i<max;i++) 
    { 
        long *temp=(long *)malloc(sizeof(long )); 
        *temp=rand()%max; 
        stack_push(Array[1],temp); 
    }
    if ((Array[1]->n+1)==max)   { print_pass(); pc++; }
    else                        { print_fail(); fc++; }




    
    fprintf(stderr,"\tstack_push():   %s",Messages[2]);
    for (i=0;i<max;i++) 
    { 
        char *new_string=generate_random_string(10); 
        stack_push(Array[2],new_string); 
    }
    if ((Array[2]->n+1)==max)   { print_pass(); pc++; }
    else                        { print_fail(); fc++; }




    fprintf(stderr,"\tstack_push():   %s",Messages[3]);
    for (i=0;i<max;i++)
    { 
        void **temp=NULL; 
        double d=(double )(rand()/(RAND_MAX+1.0));
        temp=(void **)&d; 
        stack_push(Array[3],*temp);
    }
    if ((Array[3]->n+1)==max)   { print_pass(); pc++; }
    else                        { print_fail(); fc++; }



    fprintf(stderr,"\tstack_push():   %s",Messages[4]);
    for (i=0;i<max;i++)
    { 
        double *temp=(double *)malloc(sizeof(double )); 
        *temp=(double )(rand()/(RAND_MAX+1.0)); 
        stack_push(Array[4],temp);
    }
    if ((Array[4]->n+1)==max)   { print_pass(); pc++; }
    else                        { print_fail(); fc++; }


    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n",pc,(pc+fc),fc,(fc+pc));
    fprintf(stderr,YEL "Terminating testing for the stack_push() procedure.\n"RESET);
    if (fc==0) { return STACK_TEST_SUCCESS; }
    else       { return STACK_TEST_FAILURE; }
}







/*
 * @COMPLEXITY: O(n)
 *
 * The function stack_pop_test() takes an array of
 * stack data structures and an array of strings
 * and tests the stack_pop() function on the array
 * of stacks for different values associated with
 * each stack on that array.
 *
 * @param:  stack_t     *Array[]
 * @param:  char        *Messages[]
 * @return: int
 *
 */

int stack_pop_test(stack_t *Array[],char *Messages[])
{
    int pc=0,fc=0,num=5;
    assert(Array!=NULL && Messages!=NULL);
    fprintf(stderr,YEL "Initiating testing for the stack_pop() procedure.\n"RESET);

    for (int i=0;i<num;i++)
    {

        fprintf(stderr,"\tstack_pop():    %s",Messages[i]);
        while (!stack_isEmpty(Array[i]))
        { 
            void *popped=stack_pop(Array[i]);
            if (Array[i]->destroy!=NULL) { Array[i]->destroy(popped); }
        }
        if ((Array[i]->n+1)==0) { print_pass(); pc++; }
        else                    { print_fail(); fc++; }
    }


    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n",pc,(pc+fc),fc,(fc+pc));
    fprintf(stderr,YEL "Terminating testing for the stack_pop() procedure.\n"RESET);
    if (fc==0) { return STACK_TEST_SUCCESS; }
    else       { return STACK_TEST_FAILURE; }

}




/*
 * @COMPLEXITY: O(n)
 *
 * The function stack_hasElem_test() takes an
 * array of stack data structures and an array
 * of strings and tets the stack_hasElem() function
 * on the array of stacks for different values associated
 * with each element on that array.
 *
 * @param:  stack_t     *Array[]
 * @param:  char        *Messages[]
 * @return: int
 *
 */

int stack_hasElem_test(stack_t *Array[],char *Messages[])
{
    int pc=0,fc=0,flag=0,counter=0,num=5;
    assert(Array!=NULL && Messages!=NULL);
    long long int index=0;
    fprintf(stderr,YEL "Initiating testing for the stack_hasElem() procedure.\n"RESET);


    for (int i=0;i<num;i++)
    {
        fprintf(stderr,"\tstack_hasElem(): %s",Messages[i]);
        for (int i=0;i<3;i++)
        {
            index=rand()%(Array[i]->n);
            void *temp=NULL;
            temp=Array[i]->A[index];
            flag=stack_hasElem(Array[i],temp);
            if (flag==1) { counter++; }
        }
        if (counter==3) { print_pass(); pc++; }
        else            { print_fail(); fc++; }
        counter=0;
    }

    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n",pc,(pc+fc),fc,(fc+pc));
    fprintf(stderr,YEL "Terminating testing for the stack_hasElem() procedure.\n"RESET);
    if (fc==0) { return STACK_TEST_SUCCESS; }
    else       { return STACK_TEST_FAILURE; }
}





/*
 * @COMPLEXITY: O(n)
 *
 * The function stack_isEmpty_test() takes an array of 
 * stack data structures and an array of strings
 * and tests the stack_isEmpty() function on the
 * array of stacks for different values associated
 * with each element on that array.
 *
 * @param:  stack_t     *Array[]
 * @param:  char        *Messages[]
 * @return: int
 *
 */

int stack_isEmpty_test(stack_t *Array[],char *Messages[])
{
    int num=5,pc=0,fc=0,flag;
    assert(Array!=NULL && Messages!=NULL);
    fprintf(stderr,YEL "Initiating testing for the stack_isEmpty() procedure.\n"RESET);
    for (int i=0;i<num;i++)
    {
        fprintf(stderr,"\tstack_hasElem(): %s",Messages[i]);
        flag=stack_isEmpty(Array[0]);
        if   (flag==1)  { print_pass(); pc++; }
        else            { print_fail(); fc++; }
    }
    
    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n",pc,(pc+fc),fc,(fc+pc));
    fprintf(stderr,YEL "Terminating testing for the stack_isEmpty() procedure.\n"RESET);
    if (fc==0) { return STACK_TEST_SUCCESS; }
    else       { return STACK_TEST_FAILURE; }
}







/*
 * @COMPLEXITY: O(n)
 *
 * The function stack_free_test() takes an array of
 * stack data structures and an array of strings and
 * tests the stack_free() function on the array of
 * stacks for different values associated with each
 * element on that array.
 *
 * @param:  stack_t     *Array[]
 * @param:  char        *Messages[]
 * @return: int
 *
 */

int stack_free_test(stack_t *Array[],char *Messages[])
{
    int num=5,pc=0,fc=0;
    assert(Array!=NULL && Messages!=NULL);
    fprintf(stderr,YEL "Initiating testing for the stack_free() procedure.\n"RESET);
    
    for (int i=0;i<num;i++)
    {
        fprintf(stderr,"\tstack_free():  %s",Messages[i]);
        stack_free(Array[i]); Array[i]=NULL;
        print_pass(); pc++;
    }

    fprintf(stderr,CYN "\ttotal pass = %d/%d, total fail = %d/%d\n",pc,(pc+fc),fc,(fc+pc));
    fprintf(stderr,YEL "Terminating testing for the stack_free() procedure.\n"RESET);
    if (fc==0) { return STACK_TEST_SUCCESS; }
    else       { return STACK_TEST_FAILURE; }
}







/*
 * Main execution program,runs different
 * unit tests for the stack data structure
 * defined in the header file stack.h.This
 * program has been designed in such a way
 * that users can insert extra datatype tests
 * based on preferences or circumstances.
 *
 */

int main(int argc,char *argv[])
{

    // Declaring variables and structures
    // that will be used for the testing
    // of the stack data structure.
    int cnum=5,pnum=5,dnum=5;                           // Increment everytime you insert a new datatype.
    StackCompareFn *C=NULL;                             // This array will contain the comparison functions.
    StackPrintFn *P=NULL;                               // This array will contain the printing functions.
    StackDestroyFn *D=NULL;                             // This array will contain the destroy functions.
    C=(StackCompareFn *)malloc(cnum*sizeof(*C));        // Allocating memory for the comparison array based on the values above.
    assert(C!=NULL);                                    // Check if allocation was successful.
    P=(StackPrintFn *)malloc(pnum*sizeof(*P));          // Allocating memory for the print array based on the values above.
    assert(P!=NULL);                                    // Check if allocation was successful.
    D=(StackDestroyFn *)malloc(dnum*sizeof(*D));        // Allocating memory for the destroy array based on the values above.
    assert(D!=NULL);                                    // Check if allocation was successful.


    // This array of strings contains datatype information
    // and descriptions for each datatype that will be used
    // during the execution of the testing functions.Keep
    // strings in order based on the comparison,print and
    // destroy arrays.Insert new strings everytime you
    // insert a new datatype.
    char *Messages[]={
        "type = long long int,  description = \"using pseudo-address casting of llints\",    \t",        // 1.
        "type = long long int,  description = \"using malloc and normal casting of llints\", \t",        // 2.
        "type = string,         description = \"using normal casting of string\",            \t",        // 3.
        "type = double,         description = \"using pseudo-address casting of doubles.\"   \t",        // 4.
        "type = double,         description = \"using malloc and normal casting of doubles.\"\t"         // 5.
   };                                                                                                    // ...Insert new datatype.
    
    
    // Insert here the comparison functions
    // for each datatype.Insert new comparison
    // functions everytime you insert a new
    // datatype.
    C[0]=compare_llints;
    C[1]=compare_alloc_llints;
    C[2]=compare_strings;
    C[3]=compare_doubles;
    C[4]=compare_alloc_doubles;

    

    // Insert here the printing functions
    // for each datatype.Insert new printing
    // functions everytime you insert a new
    // datatype.
    P[0]=print_llint;
    P[1]=print_alloc_llint;
    P[2]=print_string;
    P[3]=print_doubles;
    P[4]=print_alloc_doubles;


    // insert here the destroy functions
    // for each datatype.Insert new destroy
    // functions everytime you insert a new
    // datatype.
    D[0]=NULL;
    D[1]=destroy_llint;
    D[2]=destroy_string;
    D[3]=NULL;
    D[4]=destroy_double;



    

    // Performing the unit tests for the stack data structure
    // and the operations and functions associated with it.
    fprintf(stderr,BLU "INITIATING STACK TESTING: author = \"Endri Kastrati\", email = \"endriau@gmail.com\"\n"RESET);
    printf("\n");
    stack_t **stacks=stack_create_test(C,P,D,Messages);
    printf("\n");
    stack_push_test(stacks,Messages);
    printf("\n");
    stack_hasElem_test(stacks,Messages);
    printf("\n");
    stack_pop_test(stacks,Messages);
    printf("\n");
    stack_isEmpty_test(stacks,Messages);
    printf("\n");
    stack_free_test(stacks,Messages);
    printf("\n");
    fprintf(stderr,BLU "TERMINATING STACK TESTING.\n"RESET);


    // Deallocating memory for the arrays of
    // function pointers and the array of
    // stack data structure.
    free(stacks); stacks=NULL;
    free(D); free(P); free(C);
    return 0;
}
