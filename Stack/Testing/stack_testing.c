/*
 * This file performs unit testing
 * for the procedures and functions
 * that are defined in the stack.c
 * source file.
 *
 * @author: Endri Kastrati
 * @date:   4/01/2017
 *
 */




/*
 * Including the standard input-output
 * library,the standard utilities library,
 * te standard assertion library,the standard
 * string library,the standard time library 
 * the header file stack_testing.h that
 * contains function prototyping for test
 * procedures regarding the stack data
 * structure and the header file stack.h
 * that contains the definition of the
 * stack data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "stack.h"
#include "stack_testing.h"




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function compare_longs(),takes two
 * pointers to some immutable unknown data
 * and casts them into pointers to longs.
 * The method used for casting is the
 * pseudo-address casting technique.
 * Once the casting has been completed
 * the reference values of the two long
 * pointers are compared by subtracting
 * the first from the second.
 *
 * @param:  const void      *l1
 * @param:  const void      *l2
 * @return: int
 *
 */

int compare_longs(const void *l1,const void *l2)
{
    long *ll1=NULL,*ll2=NULL;
    ll1=(long *)&l1;
    ll2=(long *)&l2;
    return (*ll1-*ll2);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function compare_alloc_longs(),takes two
 * pointers to some immutable unknown data and
 * casts them into pointers to longs.The method
 * used for casting is the usual technique.
 * Once the casting has been completed the
 * reference values of the two long pointers
 * are compared by subtracting the first from
 * the second.
 *
 * @param:  const void      *l1
 * @param:  const void      *l2
 * @return: int
 *
 */

int compare_alloc_longs(const void *l1,const void *l2)
{
    long *ll1=NULL,*ll2=NULL;
    ll1=(long *)l1;
    ll2=(long *)l2;
    return (*ll1-*ll2);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function compare_doubles(),takes two pointers
 * to some immutable unknown data and casts them into
 * pointers to doubles.The method used for casting is
 * the pseudo-address casting technique.Once the 
 * casting has been completed the reference values
 * of the two double pointers are compared using
 * a conditional statement.
 *
 * @param:  const void      *d1
 * @param:  const void      *d2
 * @return: int
 *
 */

int compare_doubles(const void *d1,const void *d2)
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
 * The function compare_alloc_doubles(),takes two
 * pointers to some immutable unknown data and casts
 * them into pointers to doubles.The method used for
 * casting is the usial technique.Once the casting
 * has been completed the reference values of the two
 * double pointers are compared using a conditional 
 * statement.
 *
 * @param:  const void      *d1
 * @param:  const void      *d2
 * @return: int
 *
 */

int compare_alloc_doubles(const void *d1,const void *d2)
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
 * @COMPLEXITY: Theta(1)
 *
 * The function compare_chars(),takes two pointers
 * to some immutable unknown data and casts them
 * into pointers to chars.The method used for casting
 * is the pseudo-address casting technique.Once the
 * casting has been completed the reference values
 * of the two char pointers are compared by 
 * subtracting the first from the second.
 *
 * @param:  const void      *c1
 * @param:  const void      *c2
 * @return: int
 *
 */

int compare_chars(const void *c1,const void *c2)
{
    char *cc1=NULL,*cc2=NULL;
    cc1=(char *)&c1;
    cc2=(char *)&c2;
    return (*cc1-*cc2);
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function compare_alloc_chars(),takes two pointers
 * to some immutable unknown data and casts them into
 * pointers to chars.The method used for casting is
 * the usual technique..Once the casting has been
 * completed the reference values of the two char 
 * pointers are compared by subtracting the first
 * one from the second one.
 *
 * @param:  const void      *c1
 * @param:  const void      *c2
 * @return: int
 *
 */

int compare_alloc_chars(const void *c1,const void *c2)
{
    char *cc1=NULL,*cc2=NULL;
    cc1=(char *)c1;
    cc2=(char *)c2;
    return (*cc1-*cc2);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function compare_uints(),takes two pointers
 * to some immutable data and casts them into
 * pointers to unsigned ints.The method used for
 * casting is the pseudo-address casting technique.
 * Once the casting has been completed the reference
 * values of the two uint pointers are compared using
 * a conditional statement.
 *
 * @param:  const void      *u1
 * @param:  const void      *u2
 * @return: int
 *
 */

int compare_uints(const void *u1,const void *u2)
{
    unsigned int *uu1=NULL,*uu2=NULL;
    uu1=(unsigned int *)&u1;
    uu2=(unsigned int *)&u2;
    if (*uu1<*uu2)  { return -1; }
    if (*uu1==*uu2) { return  0; }
    if (*uu1>*uu2)  { return  1; }
    return 0;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function compare_uints(),takes two pointers
 * to some immutable data and casts them into pointers
 * to unsigned ints.The method used for casting is
 * the usual technique.Once the casting has been
 * completed the reference values of the two uint
 * pointers are compared using a conditional statement.
 *
 * @param:  const void      *u1
 * @param:  const void      *u2
 * @return: int
 *
 */

int compare_alloc_uints(const void *u1,const void *u2)
{
    unsigned int *uu1=NULL,*uu2=NULL;
    uu1=(unsigned int *)u1;
    uu2=(unsigned int *)u2;
    if (*uu1<*uu2)  { return -1; }
    if (*uu1==*uu2) { return  0; }
    if (*uu1>*uu2)  { return  1; }
    return 0;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The function compare_strings(),takes two pointers
 * to some immutable data and casts them into pointers
 * to chars.Because the given arguments are arrays of
 * chars,namely strings the only way to do the casting
 * is the usual way.Once the casting has been completed
 * the two strings are compared using the built-int
 * function strcmp() contained in the string.h header.
 *
 * @param:  const void      *s1
 * @param:  const void      *s2
 * @return: int
 *
 */

int compare_strings(const void *s1,const void *s2)
{
    char *ss1=NULL,*ss2=NULL;
    ss1=(char *)s1;
    ss2=(char *)s2;
    return strcmp(ss1,ss2);
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function compare_addresses(),takes two pointers
 * to some immutable data and casts them into pointers
 * to addresses.Because we are dealing with memory
 * addresses the casting way is the usual technique.
 * Once the casting has been completed the the two
 * addresses are compared using a conditional statement.
 *
 * @param:  const void      *a1
 * @param:  const void      *a2
 * @return: int
 *
 */

int compare_addresses(const void *a1,const void *a2)
{
    if (a1<a2)  { return -1; }
    if (a1==a2) { return  0; }
    if (a1>a2)  { return  1; }
    return 0;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_long(),takes a pointer
 * to some immutable data and casts it into
 * a pointer to a long.The method used for
 * casting is the pseudo-address casting
 * technique.Once the casting has been
 * completed the long is printed into
 * the standard output stream.
 *
 * @param:  const void  *l
 * @return: void
 *
 */

void print_long(const void *l)
{
    long *ll=NULL;
    ll=(long *)&l;
    printf("%ld",*ll);
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_alloc_long(),takes a
 * pointer to some immutable data and casts
 * into a pointer to a long.The method used
 * for casting is the usual technique.Once
 * the casting has been completed the long
 * is printed into the standard output stream.
 *
 * @param:  const void  *l
 * @return: void
 *
 */

void print_alloc_long(const void *l)
{
    long *ll=NULL;
    ll=(long *)l;
    printf("%ld",*ll);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_double(),takes a pointer
 * to some immutable data and casts it into a
 * pointer to a double.The method used for casting
 * is the pseudo-address casting technique.Once the
 * casting has been completed the double is printed
 * into the standard output stream.
 *
 * @param:  const void  *d
 * @return: void
 *
 */

void print_double(const void *d)
{
    double *dd=NULL;
    dd=(double *)&d;
    printf("%.2lf",*dd);
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_alloc_double(),takes a
 * pointer to some immutable data and casts it
 * into a pointer to a double.The method used
 * for casting is the usual technique.Once the 
 * casting has been completed the double is 
 * printed into the standard output stream.
 *
 * @param:  const void  *d
 * @return: void
 *
 */

void print_alloc_double(const void *d)
{
    double *dd=NULL;
    dd=(double *)d;
    printf("%.2lf",*dd);
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_char(),takes a pointer
 * to some immutable data and casts into it
 * a pointer to a char.The method used for
 * casting is the pseudo-address casting
 * technique.Once the casting has been
 * completed the char is printed into
 * the standard output stream.
 *
 * @param:  const void  *c
 * @return: void
 *
 */

void print_char(const void *c)
{
    char *cc=NULL;
    cc=(char *)&c;
    printf("%c",*cc);
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_alloc_char(),takes a
 * pointer to some immutable data and casts
 * it into a pointer to char.The method
 * used for casting is the usual technique.
 * Once the casting has been completed the
 * char is printed into the standard output
 * stream.
 *
 * @param:  const void  *c
 * @return: void
 *
 */

void print_alloc_char(const void *c)
{
    char *cc=NULL;
    cc=(char *)c;
    printf("%c",*cc);
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_uint(),takes a pointer
 * to some immutable data and casts it into
 * a pointer to some unsigned int.The method
 * used for casting is the pseudo-address
 * casting technique.Once the casting has
 * been completed the uint is printed into
 * the standard output stream.
 *
 * @param:  const void  *u
 * @return: void
 *
 */

void print_uint(const void *u)
{
    unsigned int *uu=NULL;
    uu=(unsigned int *)&u;
    printf("%u",*uu);
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_alloc_uint(),takes
 * a pointer to some immutable data and
 * casts it into a pointer to an unsigned int.
 * The method for casting is the normal casting
 * technique.Once the casting has been completed
 * the uint is printed into the standard output
 * stream.
 *
 * @param:  const void  *u
 * @return: void
 *
 */

void print_alloc_uint(const void *u)
{
    unsigned int *uu=NULL;
    uu=(unsigned int *)u;
    printf("%u",*uu);
    return;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The function print_string(),takes a
 * pointer to some immutable data and
 * casts it into a pointer to char.
 * Because the given argument is an
 * array of chars the only way to do
 * the casting is the usual way.Once
 * the casting has been completed the
 * string is printed into the standard
 * output stream.
 *
 * @param:  const void  *s
 * @return: void
 *
 */

void print_string(const void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    printf("%s",ss);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The function print_address(),takes a
 * pointer to some immutable data and
 * casts it into a pointer to an address.
 * Because the given argument represents
 * a memory address the casting is done
 * via the usual way.Once the casting
 * has been completed the memory address
 * is printed into the standard output
 * stream.
 *
 * @param:  const void  *a
 * @return: void
 *
 */

void print_address(const void *a)
{
    printf("%p",a);
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The function deallocate_long(),takes
 * a pointer to some unknown data and
 * casts it into a pointer to a long.
 * Once the casting has been completed
 * the memory chunk associated with this
 * pointer is deallocated and returned
 * back into the heap.
 *
 * @param:  void    *l
 * @return: void
 *
 */

void deallocate_long(void *l)
{
    long *ll=NULL;
    ll=(long *)l;
    free(ll); ll=NULL;
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function deallocate_double(),takes
 * a pointer to some unknown data and 
 * casts it into a pointer to a double.
 * Once the casting has been completed
 * the memory chunk associated with this 
 * pointer is deallocated and returned 
 * back into the heap.
 *
 * @param:  void    *d
 * @return: void
 *
 */

void deallocate_double(void *d)
{
    double *dd=NULL;
    dd=(double *)d;
    free(dd); dd=NULL;
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function deallocate_char(),takes
 * a pointer to some unknown data and
 * casts it into a pointer to a char.
 * Once the casting has been completed
 * the memory chunk associated with this
 * pointer is deallocated and returned
 * back into the heap.
 *
 * @param:  void    *c
 * @return: void
 *
 */

void deallocate_char(void *c)
{
    char *cc=NULL;
    cc=(char *)c;
    free(cc); cc=NULL;
    return;
}




/*
 * @COMPLEXITY: Theta(1)
 *
 * The function deallocate_uint(),takes
 * a pointer to some unknown data and
 * casts it into a pointer to an unsigned
 * int.Once the casting has been completed
 * the memory chunk associated with this
 * pointer is deallocated and returned 
 * back into the heap.
 *
 * @param:  void    *u
 * @return: void
 *
 */

void deallocate_uint(void *u)
{
    unsigned int *uu=NULL;
    uu=(unsigned int *)u;
    free(uu); uu=NULL;
    return;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function deallocate_string(),takes
 * a pointer to some unknown data and 
 * casts it into a pointer to a char.
 * Once the casting has been completed
 * the memory chunk associated with
 * this pointer is deallocated and
 * returned back into the heap.
 *
 * @param:  void    *s
 * @return: void
 *
 */

void deallocate_string(void *s)
{
    char *ss=NULL;
    ss=(char *)s;
    free(ss); ss=NULL;
    return;
}



/*
 * @COMPLEXITY: Theta(1)
 *
 * The function deallocate_address(),takes
 * a pointer to some unknown data and deallocates
 * the memory chunk associated with the given
 * pointer.
 *
 * @param:  void    *a
 * @return: void
 *
 */

void deallocate_address(void *a)
{
    free(a); a=NULL;
    return;
}




/*
 * @COMPLEXITY: O(n)
 *
 * The function generate_random_string(),takes
 * one argument as a parameter,namely an integer that
 * represents the length of the randomly generated
 * strings.This function allocates memory based on
 * the given value and randomly generatess the 
 * character values of a string data structure.
 * The newly randomly generated string is returned.
 *
 * @param:  int     length
 * @return: char    *
 *
 */

char *generate_random_string(int l)
{
    char *new_string=NULL; int i;
    new_string=(char *)malloc((l+1)*sizeof(char ));
    assert(new_string!=NULL);
    for (i=0;i<l;i++) { new_string[i]=65+rand()%25; }
    new_string[l]='\0';
    return new_string;
}





/*
 * @COMPLEXITY: Theta(1)
 *
 * The function stack_create_test(),takes no arguments
 * as parameters and performs a thorough testing of
 * the stack_create() procedure that instantiates a
 * new stack data structure.The procedure is tested
 * with different function pointers as parameters
 * that provide a polymorphic interface for different
 * kinds of datatypes.
 *
 * @param;  void
 * @return: int
 *
 */

int stack_create_test()
{
    // Variable declaration.In this section
    // of the code we define the variables
    // that will be used for the testing
    // of the stack_create() procedure and
    // print the appropriate message output
    // to the standard error output stream.
    int pc=0,fc=0;
    stack_t *stack_long=NULL,*stack_alloc_long=NULL;
    stack_t *stack_double=NULL,*stack_alloc_double=NULL;
    stack_t *stack_char=NULL,*stack_alloc_char=NULL,*stack_uint=NULL;
    stack_t *stack_alloc_uint=NULL,*stack_string=NULL,*stack_address=NULL;
    fprintf(stderr,YEL "initiating unit testing for procedure stack_create()\n"RESET);
    
    
    // Testing the stack_create() procedure for long datatypes
    // that are casted using pseudo-address casting.This means
    // that there is no need for a destroy function associated
    // with the long datatypes since presumably they have been
    // instantiated into the stack (not the data structure)
    // instead of the heap.If the stack_create() procedure
    // fails to allocate memory then this case fails,otherwise
    // it succeeds.
    char description1[]="\tstack_create(): type = long,\
      method = \"testing using pseudo-address casting of longs.\"";
    stack_long=stack_create(compare_longs,print_long,NULL);
    fprintf(stderr,"%s",description1);
    if (stack_long!=NULL) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
    
    
    // Testing the stack_create() procedure for the long datatypes
    // that have been instantiated using malloc and are cast using
    // the usual technique.In this case a deallocation function is
    // provided as an argument to stack_create() function.If the
    // function fails to allocate memory then this case fails,
    // otherwise it succeeds.
    char description2[]="\tstack_create(): type = long,\
      method = \"testing using malloc and normal casting of longs.\"";
    stack_alloc_long=stack_create(compare_alloc_longs,print_alloc_long,deallocate_long);
    fprintf(stderr,"%s",description2);
    if (stack_alloc_long!=NULL) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
    
    
    // Testing the stack_create() procedure for the double datatypes
    // that are casted using pseudo-address casting.This means that
    // there is no need for a destroy function associated with the
    // double datatypes since,presumably,they have been instantiated
    // into the stack (not the data structure) instead of the heap.
    // If the stack_create() fails to allocate memory then this
    // case fails,otherwise it succeeds.
    char description3[]="\tstack_create(): type = double,\
    method = \"testing using pseudo-address casting of doubles.\"";
    stack_double=stack_create(compare_doubles,print_double,NULL);
    fprintf(stderr,"%s",description3);
    if (stack_double!=NULL) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
    
    
    // Testing the stack_create() procedure for the double datatypes
    // that have been instantiated using malloc and are cast using
    // the usual technique.In this case a deallocation function is
    // provided as an argument to the stack_create() function.If the
    // function fails to allocate memory then this case fails,otherwise
    // it succeeds.
    char description4[]="\tstack_create(): type = double,\
    method = \"testing using malloc and normal casting of longs.\"";
    stack_alloc_double=stack_create(compare_alloc_doubles,print_alloc_double,deallocate_double);
    fprintf(stderr,"%s",description4);
    if (stack_alloc_double!=NULL) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
    
    
    // Testing the stack_create() procedure for char datatypes
    // that are casted using pseudo-address casting.This means
    // that there is no need for a destroy function associated
    // with the char datatypes,sicen they have been instantiated
    // into the stack (not the data structure) instead of the heap.
    // If the stack_create() procedure fails to allocate memory
    // then this case fails,otherwise it succeeds.
    char description5[]="\tstack_create(): type = char,\
      method = \"testing using pseudo-address casting of chars.\"";
    stack_char=stack_create(compare_chars,print_char,NULL);
    fprintf(stderr,"%s",description5);
    if (stack_char!=NULL) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
    
    
    // Testing the stack_create() procedure for char datatypes
    // that have been instantiated using malloc and are cast
    // using the usual technique.In this case a deallocation
    // function is provided as an argument to the stack_create()
    // function.If the stack_create() procedure fails to allocate
    // memory then this case fails,otherwise it succeeds.
    char description6[]="\tstack_create(): type = char,\
      method = \"testing using malloc and normal casting of chars.\"";
    stack_alloc_char=stack_create(compare_alloc_chars,print_alloc_char,deallocate_char);
    fprintf(stderr,"%s",description6);
    if (stack_alloc_char!=NULL) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
   

    // Testing the stack_create() procedure for unsigned int
    // datatypes that are casted using pseudo-address casting.
    // This means that there is no need for a destroy function
    // associated with the unsigned int dataypes since,presumably
    // they have been instantiated into the stack (not the data structure)
    // instead of the heap.If the stack_create() function fails to allocate
    // memory then this case fails,otherwise it succeeds.
    char description7[]="\tstack_create(): type = uint,\
      method = \"testing using pseudo-address casting of uints.\"";
    stack_uint=stack_create(compare_uints,print_uint,NULL);
    fprintf(stderr,"%s",description7);
    if (stack_uint!=NULL) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
    
   
    // Testing the stack_create() procedure for the unsigned int
    // datatypes that have been instantiated using malloc and
    // are cast using the usual technique.In this case a deallocation
    // function is provided as an argument to the stack_create()
    // function.If the stack_create() procedure fails to allocate
    // memory then this case fails,otherwise it succeeds.
    char description8[]="\tstack_create(): type = uint,\
      method = \"testing using malloc and normal casting of uints.\"";
    stack_alloc_uint=stack_create(compare_alloc_uints,print_alloc_uint,deallocate_uint);
    fprintf(stderr,"%s",description8);
    if (stack_alloc_uint!=NULL) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
    

    // Testing the stack_create() procedure for the string datatype.
    // Because the string datatype is allocated as an array of 
    // characters whether it is from the heap or the stack it is
    // treated the same way.A deallocation function can be provided
    // or it cannot depending on the circumstances.If the stack_create()
    // procedure fails to allocate memory then this case fails,otherwise
    // it succeeds.
    char description9[]="\tstack_create(): type = string,\
    method = \"testing using normal casting of strings.\"";
    stack_string=stack_create(compare_strings,print_string,deallocate_string);
    fprintf(stderr,"%s",description9);
    if (stack_string!=NULL) { pc++; fprintf(stderr,"\t\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t\t["RED" FAIL "RESET"]\n"); }
   

    // Testing the stack_create() procedure for the memory address datatype.
    // Because the memory address datatype is very straight forward in some
    // cases a deallocation function is not need,but not always.If the 
    // stack_create() procedure fails to allocate memory then this case
    // fails,otherwise it succeeds.
    char description10[]="\tstack_create(): type = address,\
   method = \"testing using normal casting of addresses.\"";
    stack_address=stack_create(compare_addresses,print_address,NULL);
    fprintf(stderr,"%s",description10);
    if (stack_address!=NULL) { pc++; fprintf(stderr,"\t\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t\t["RED" FAIL "RESET"]\n"); }


    // Printing the results of testing the stack_create() procedure.
    // The total number of fails and total number of succeeds are
    // printed as well in a user friendly format.
    fprintf(stderr,CYN "\ttotal passes = %d/%d, ",pc,(pc+fc));
    fprintf(stderr,CYN "\ttotal fails  = %d/%d\n",fc,(pc+fc));
    fprintf(stderr,YEL "terminating unit testing for procedure stack_create()\n"RESET);

    
    // Deallocating memory for all the stack data
    // structures that were declared in the beginning
    // of this function.
    stack_free(stack_long); stack_long=NULL;
    stack_free(stack_alloc_long); stack_alloc_long=NULL;
    stack_free(stack_double); stack_double=NULL;
    stack_free(stack_alloc_double); stack_alloc_double=NULL;
    stack_free(stack_char); stack_char=NULL;
    stack_free(stack_alloc_char); stack_alloc_char=NULL;
    stack_free(stack_uint); stack_uint=NULL;
    stack_free(stack_alloc_uint); stack_alloc_uint=NULL;
    stack_free(stack_string); stack_string=NULL;
    stack_free(stack_address); stack_address=NULL;

    
    // If all test cases passed succcessfully then
    // the testing for the stack_create() procedure
    // was successful.If at least one case failed
    // then the testing was a failure and something
    // is wrong with the stack_create() procedure.
    if (fc==0) { return TEST_SUCCESSFUL; }
    else { return TEST_FAILURE; }
}







int stack_push_test()
{
    time_t seed; long long i,max=10000000; int pc=0,fc=0;
    stack_t *stack_long=NULL,*stack_alloc_long=NULL;
    stack_t *stack_double=NULL,*stack_alloc_double=NULL;
    stack_t *stack_char=NULL,*stack_alloc_char=NULL,*stack_uint=NULL;
    stack_t *stack_alloc_uint=NULL,*stack_string=NULL,*stack_address=NULL;
    fprintf(stderr,YEL "initiating unit testing for procedure stack_push()\n"RESET);
    srand((unsigned )time(&seed));

    char description1[]="\tstack_push(): type = long,\
    method = \"testing using pseudo-address casting of longs.\"";
    stack_long=stack_create(compare_longs,print_long,NULL);
    fprintf(stderr,"%s",description1); 
    for (i=0;i<max;i++)
    {
        long ll=(long )(rand()%max);
        void **temp=NULL; temp=(void **)&ll;
        stack_push(stack_long,*temp);
    }
    if ((stack_long->n+1)==max) { pc++; fprintf(stderr,"\t\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t\t["RED" FAIL "RESET"]\n"); }


    char description2[]="\tstack_push(): type = long,\
    method = \"testing using malloc and normal casting of longs.\"";
    stack_alloc_long=stack_create(compare_alloc_longs,print_alloc_long,deallocate_long);
    fprintf(stderr,"%s",description2);
    for (i=0;i<max;i++)
    {
        long *temp=NULL;
        temp=(long *)malloc(sizeof(long ));
        *temp=rand()%max;
        stack_push(stack_alloc_long,temp);
    }
    if ((stack_alloc_long->n+1)==max) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }


    char description3[]="\tstack_push(): type = double,\
  method = \"testing using pseudo-address casting of doubles.\"";
    stack_double=stack_create(compare_doubles,print_double,NULL);
    fprintf(stderr,"%s",description3);
    for (i=0;i<max;i++)
    {
        double dd=(double )(rand()/(RAND_MAX+1.0));
        void **temp=NULL; temp=(void **)&dd;
        stack_push(stack_double,*temp);
    }
    if ((stack_double->n+1)==max) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
    

    char description4[]="\tstack_push(): type = double,\
  method = \"testing using malloc and normal casting of doubles.\"";
    stack_alloc_double=stack_create(compare_alloc_doubles,print_alloc_double,deallocate_double);
    fprintf(stderr,"%s",description4);
    for (i=0;i<max;i++)
    {
        double *temp=NULL;
        temp=(double *)malloc(sizeof(double ));
        *temp=(double )(rand()/(RAND_MAX+1.0));
        stack_push(stack_alloc_double,temp);
    }
    if ((stack_alloc_double->n+1)==max) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }

    

    char description5[]="\tstack_push(): type = char,\
    method = \"testing using pseudo-address casting of chars.\"";
    stack_char=stack_create(compare_chars,print_char,NULL);
    fprintf(stderr,"%s",description5);
    for (i=0;i<max;i++)
    {
        char cc=(char )(65+rand()%25);
        void **temp=NULL; temp=(void **)&cc;
        stack_push(stack_char,*temp);
    }
    if ((stack_char->n+1)==max) { pc++; fprintf(stderr,"\t\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t\t["RED" FAIL "RESET"]\n"); }


    char description6[]="\tstack_push(): type = char,\
    method = \"testing using malloc and normal casting of chars.\"";
    stack_alloc_char=stack_create(compare_alloc_chars,print_alloc_char,deallocate_char);
    fprintf(stderr,"%s",description6);
    for (i=0;i<max;i++)
    {
        char *temp=(char *)malloc(sizeof(char ));
        *temp=(char )(65+rand()%25);
        stack_push(stack_alloc_char,temp);
    }
    if ((stack_alloc_char->n+1)==max) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }

    
    char description7[]="\tstack_push(): type = uint,\
    method = \"testing using pseudo-address casting of uints.\"";
    stack_uint=stack_create(compare_uints,print_uint,NULL);
    fprintf(stderr,"%s",description7);
    for (i=0;i<max;i++)
    {
        unsigned int uu=rand()%max;
        void **temp=NULL; temp=(void **)&uu;
        stack_push(stack_uint,*temp);
    }
    if ((stack_uint->n+1)==max) { pc++; fprintf(stderr,"\t\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t\t["RED" FAIL "RESET"]\n"); }
    


    char description8[]="\tstack_push(): type = uint,\
    method = \"testing using malloc and normal casting of uints.\"";
    stack_alloc_uint=stack_create(compare_alloc_uints,print_alloc_uint,deallocate_uint);
    fprintf(stderr,"%s",description8);
    for (i=0;i<max;i++)
    {
        unsigned int *temp=NULL;
        temp=(unsigned int *)malloc(sizeof(unsigned int ));
        stack_push(stack_alloc_uint,temp);
    }
    if ((stack_alloc_uint->n+1)==max) { pc++; fprintf(stderr,"\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr,"\t\t["RED" FAIL "RESET"]\n"); }
        

    char description9[]="\tstack_push(): type = string,\
  method = \"testing using normal casting of strings.\"";
    stack_string=stack_create(compare_strings,print_string,deallocate_string);
    fprintf(stderr,"%s",description9);
    for (i=0;i<max;i++)
    {
        stack_push(stack_string,generate_random_string(5));
    }
    if ((stack_string->n+1==max)) { pc++; fprintf(stderr, "\t\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr, "\t\t\t["RED" FAIL "RESET"]\n"); }

    char description10[]="\tstack_push(): type = address,\
 method = \"testing using normal casting of addresses.\"";
    stack_address=stack_create(compare_addresses,print_address,deallocate_address);
    fprintf(stderr,"%s",description10);
    for (i=0;i<max;i++)
    {
        void *address=NULL;
        address=(void *)malloc(sizeof(void *));
        stack_push(stack_address,address);
    }
    if ((stack_address->n+1)==max) { pc++; fprintf(stderr, "\t\t\t["GRN" PASS "RESET"]\n"); }
    else { fc++; fprintf(stderr, "\t\t\t["RED" FAIL "RESET"]\n"); }


    fprintf(stderr,CYN "\ttotal passes = %d/%d, ",pc,(pc+fc));
    fprintf(stderr,CYN "\ttotal fails  = %d/%d\n",fc,(pc+fc));
    fprintf(stderr,YEL "terminating unit testing for procedure stack_push()\n"RESET);


    stack_free(stack_long); stack_long=NULL;
    stack_free(stack_alloc_long); stack_alloc_long=NULL;
    stack_free(stack_double); stack_double=NULL;
    stack_free(stack_alloc_double); stack_alloc_double=NULL;
    stack_free(stack_char); stack_char=NULL;
    stack_free(stack_alloc_char); stack_alloc_char=NULL;
    stack_free(stack_uint); stack_uint=NULL;
    stack_free(stack_alloc_uint); stack_alloc_uint=NULL;
    stack_free(stack_string); stack_string=NULL;
    stack_free(stack_address); stack_address=NULL;

    if (fc==0) { return TEST_SUCCESSFUL; }
    else { return TEST_FAILURE; }
}





int main(int argc,char *argv[])
{
    fprintf(stderr,BLU "INITIATING STACK TESTING: author = \"Endri Kastrati\", email = \"endriau@gmail.com\"\n\n");
    stack_create_test(); printf("\n");stack_push_test(); printf("\n"); //stack_pop_test(); stack_print_test(); stack_free_test();
    //stack_isEmpty_test(); stack_hasElem_test();
    fprintf(stderr,BLU "TERMINATING STACK TESTING.\n"RESET);
    return 0;
}
