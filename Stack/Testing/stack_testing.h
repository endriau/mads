/*
 * This file contains macro constants
 * and function prototyping for the
 * for the testing procedures and
 * operations regarding the stack
 * data structure.
 *
 * @author: Endri Kastrati
 * @date:   4/01/2017
 *
 */



/*
 * Including the standard input-output
 * library,the standard utilities library,
 * the standard assertions library as well
 * as the header file stack.h that contains
 * datatype definitions and function prototyping
 * for the polymorphic stack data structure.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>




/*
 * This macro constants are used to change
 * the color of the printed output,in the
 * testing procedures,into one of the 
 * following color formats.
 *
 */

#define RED     "\x1B[31m"
#define GRN     "\x1B[32m"
#define YEL     "\x1B[33m"
#define BLU     "\x1B[34m"
#define MAG     "\x1B[35m"
#define CYN     "\x1B[36m"
#define WHT     "\x1B[37m"
#define RESET   "\x1B[0m"




/*
 * Defining two macro constants that
 * indicate whether a testing procedure
 * was successful or failed partly or
 * entirely.The values associated with
 * sucess is the value of one and the
 * value associated with failure is zero.
 *
 */

#define TEST_SUCCESSFUL 1
#define TEST_FAILURE    0




/*
 * Function prototyping for the stack data
 * structure testing procedures.This functions
 * will be used to test the procedures and
 * functions associated with the stack as well
 * as the stack properties.
 *
 */

int     compare_longs(const void *l1,const void *l2);
int     compare_alloc_longs(const void *l1,const void *l2);
int     compare_doubles(const void *d1,const void *d2);
int     compare_alloc_doubles(const void *d1,const void *d2);
int     compare_chars(const void *c1,const void *c2);
int     compare_alloc_chars(const void *c1,const void *c2);
int     compare_uints(const void *u1,const void *u2);
int     compare_alloc_uints(const void *u1,const void *u2);
int     compare_strings(const void *s1,const void *s2);
int     compare_addresses(const void *a1,const void *a2);
void    print_long(const void *l);
void    print_alloc_long(const void *l);
void    print_double(const void *d);
void    print_alloc_double(const void *d);
void    print_char(const void *c);
void    print_alloc_char(const void *c);
void    print_uint(const void *u);
void    print_alloc_uint(const void *u);
void    print_string(const void *s);
void    print_address(const void *a);
void    deallocate_long(void *l);
void    deallocate_double(void *d);
void    deallocate_char(void *c);
void    deallocate_uint(void *u);
void    deallocate_string(void *s);
char    *generate_random_string(int l);
int     stack_create_test();
int     stack_push_test();
int     stack_pop_test();
int     stack_print_test();
int     stack_free_test();
int     stack_isEmpty_test();
int     stack_hasElem_test();
int     stack_properties_test();
