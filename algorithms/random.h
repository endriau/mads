//
// Created by p0int3r on 6/12/21.
//

#ifndef TINYLIB_RANDOM_H
#define TINYLIB_RANDOM_H


#define NN          312
#define MM          156
#define LM          0x7FFFFFFFULL
#define UM          0xFFFFFFFF80000000ULL
#define MATRIX_A    0xB5026F5AA96619E9ULL


typedef long long int llint;
typedef unsigned long long int lluint;


void init_genrand64(lluint seed);
void init_by_array64(lluint init_key[],lluint key_length);
lluint genrand64_int64(void);
llint genrand64_int63(void);
double genrand64_real1(void);
double genrand64_real2(void);
double genrand64_real3(void);

#endif //TINYLIB_RANDOM_H
