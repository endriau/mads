#ifndef MADS_ALGORITHMS_RANDOM_H
#define MADS_ALGORITHMS_RANDOM_H



#define MADS_RANDOM_NN 312
#define MADS_RANDOM_MM 156
#define MADS_RANDOM_LM 0x7FFFFFFFULL
#define MADS_RANDOM_UM 0xFFFFFFFF80000000ULL
#define MADS_RANDOM_MATRIX_A 0xB5026F5AA96619E9ULL


void mads_init_genrand64(unsigned long long int seed);
void mads_init_by_array64(unsigned long long int init_key[], unsigned long long int key_length);
unsigned long long int mads_genrand64_int64(void);
long long int mads_genrand64_int63(void);
double mads_genrand64_real1(void);
double mads_genrand64_real2(void);
double mads_genrand64_real3(void);

#endif //MADS_ALGORITHMS_RANDOM_H
