/*
 * This file contains datatype definitions and function
 * prototyping regarding the mersenne twister pseudo
 * random number generator algorithm and the procedures
 * associated with it.
 *
 * @author: Endri Kastrati
 * @date:   25/01/2017
 *
 */




/*
 * Using include guards to check if
 * the random.h header file has been
 * included at least once.If it hasn't,
 * the compiler copy-pastes everything
 * into the file that is including it.
 * If the file on the other hand has
 * been included the compiler skips
 * the contents entirely.
 *
 */

#ifndef RANDOM_H
#define RANDOM_H





/*
 * Defining the following macro
 * constants that will be used
 * during the initialization of
 * the state vectors and the
 * generation processes.
 *
 */

#define NN          312
#define MM          156
#define LM          0x7FFFFFFFULL
#define UM          0xFFFFFFFF80000000ULL
#define MATRIX_A    0xB5026F5AA96619E9ULL





/*
 * Defining two aliases for the unsigned long long int
 * and long long int native datatypes.The reason for
 * this is to improve readability of the code.
 *
 */

typedef long long int           llint;
typedef unsigned long long int  lluint;





/*
 * Function prototyping of procedures to
 * deal with 64-bit random number generation
 * using the mersenne twister algorithm.
 *
 */

void            init_genrand64(lluint seed);
void            init_by_array64(lluint init_key[],lluint key_length);
lluint          genrand64_int64(void);
llint           genrand64_int63(void);
double          genrand64_real1(void);
double          genrand64_real2(void);
double          genrand64_real3(void);




/*
 * Once everything has been copy-pasted
 * by the compiler and the macro constant
 * RANDOM_H has been defined,the random.h
 * header file will not be included more
 * than once.
 *
 */

#endif

