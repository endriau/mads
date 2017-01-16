/*
 * This header file contains function 
 * prototyping for testing procedures
 * regarding the polymorphic stack
 * data structure.
 *
 * @author: Endri Kastrati
 * @date:   9/01/2017
 *
 */



/*
 * Using include guards to check
 * if the stacTest.h header file
 * has been included at least once.
 * If it hasn't the compiler copy
 * pastes everything into the file
 * that is including it.If the file
 * on the other hand has been included
 * the compiler skips the contents
 * entirely.
 *
 */

#ifndef STACKTEST_H
#define STACKTEST_H




/* 
 * Including the stack.h header
 * file that contains datatype
 * definitions and function 
 * prototyping for the cuckoo
 * hash table data structure.
 * 
 */

#include "stack.h"



/*
 * Defining two macro constants
 * that represent the status
 * of the testing cases.failure
 * is represented as zero and
 * success as one.
 *
 */

#define STACK_TEST_FAILURE 1
#define STACK_TEST_SUCCESS 0



/*
 * Defining these macro constants
 * that represent different colors
 * that can be ouput in the standard
 * error stream.
 *
 */

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"




/*
 * Function prototyping of procedures regarding
 * the testing of the stack data structure and
 * the operations associated with it.
 *
 */

stack_t     **stack_create_test(StackCompareFn *C,StackPrintFn *P,StackDestroyFn *D,char *Message[]);
int         stack_push_test(stack_t *Array[],char *Messages[]);
int         stack_pop_test(stack_t *Array[],char *Messages[]);
int         stack_print_test(stack_t *Array[],char *Messages[]);
int         stack_isEmpty_test(stack_t *Array[],char *Messages[]);
int         stack_free_test(stack_t *Array[],char *Messages[]);
int         stack_hasElem_test(stack_t *Array[],char *Messages[]);




/*
 * Once everything has been copy-pasted
 * by the compiler and the macro STACKTEST_H
 * has been defined,the stackTest.h header
 * file will not be included more than once.
 *
 */

#endif

