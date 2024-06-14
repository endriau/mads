#ifndef MADS_ALGORITHMS_RANDOM_H
#define MADS_ALGORITHMS_RANDOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mads_export.h>

#define MADS_RANDOM_NN 312
#define MADS_RANDOM_MM 156
#define MADS_RANDOM_LM 0x7FFFFFFFULL
#define MADS_RANDOM_UM 0xFFFFFFFF80000000ULL
#define MADS_RANDOM_MATRIX_A 0xB5026F5AA96619E9ULL


MADS_EXPORT void mads_init_genrand64(unsigned long long int seed);
MADS_EXPORT void mads_init_by_array64(unsigned long long int init_key[], unsigned long long int key_length);
MADS_EXPORT unsigned long long int mads_genrand64_int64(void);
MADS_EXPORT long long int mads_genrand64_int63(void);
MADS_EXPORT double mads_genrand64_real1(void);
MADS_EXPORT double mads_genrand64_real2(void);
MADS_EXPORT double mads_genrand64_real3(void);

#ifdef __cplusplus
}
#endif

#endif //MADS_ALGORITHMS_RANDOM_H
