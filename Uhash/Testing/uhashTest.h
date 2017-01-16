/*
 * This  file contains function
 * prototyping for testing procedures
 * regarding the universal hash function
 * data structure.
 *
 * @author: Endri Kastrati
 * @date:   16/01/2017
 *
 */



/*
 * Using include guards to check
 * if the uhashTest.h header file
 * has been included at least once.
 * If it hasn't the compiler copy
 * pastes everything into the file
 * that is inlcuding it.If the file
 * on the other hand has been included
 * the compiler skips the contents 
 * entirely.
 *
 */

#ifndef UHASHTEST_H
#define UHASHTEST_H




/*
 * Including the uhash.h header
 * file that contains datatype
 * definitions and function
 * prototyping for the universal
 * hash function data structure.
 *
 */

#include "uhash.h"



/*
 * Defining two macro constants that
 * represent the status of the testing
 * cases.Failure is represented with
 * the value of zero and success with
 * the value of one.
 *
 */

#define UHASH_TEST_FAILURE  0
#define UHASH_TEST_SUCCESS  1





/*
 * Defining these macros constants
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
 * Function prototyping of procedures
 * regarding the testing of the universal
 * hash function data structure and the
 * operations associated with it.
 *
 */

hashfn_t        **hashfn_create_test(lluint *tss,lluint *ks,lluint n);
int             hashfn_getValues_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n);
int             hashfn_getTableSize_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n);
int             hashfn_getK_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n);
int             stack_print_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n);
int             hashfn_free_test(hashfn_t **fs,lluint *tss,lluint *ks,lluint n);






/*
 * Once everything has been copy-pasted
 * by the compiler and the macro UHASHTEST_H
 * has been defined,the uhashTest.h header file
 * will not be included more than once.
 *
 */

#endif
