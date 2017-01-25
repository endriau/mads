/*
 * This file contains the definition of procedures
 * and operations regarding the mersenne twister
 * pseudo-random number generator algorithm.
 *
 * @author: Endri kastrati
 * @date:   25/01/2017
 *
 */





/*
 * Including the header file random.h
 * that contains datatype definitions
 * and function prototyping regarding
 * the mersenne twister pseudo-random
 * number generator algorithm.
 *
 */

#include "random.h"





/*
 * Defining two static variables.The first
 * one,represents the state vector and the
 * second one if (mti==NN+1) means that the
 * state vector is not initialized.
 *
 */

static lluint   mt[NN];
static int      mti=NN+1;






/*
 * @COMPLEXITY: O(NN) where NN is the value
 *              of the macro constant defined
 *              in the header file random.h
 * 
 * The function init_genrand64() takes a lluint
 * (unsigned long long int) datatype as an argument.
 * This function initializes the state vector mt[NN]
 * using the given parameter as a seeding value.
 *
 * @param:  lluint  seed
 * @return: void
 *
 */

void init_genrand64(lluint seed)
{
    mt[0]=seed;

    for (mti=1;mti<NN;mti++)
    {
        mt[mti]=(6364136223846793005ULL*
            (mt[mti-1]^(mt[mti-1]>>62))+mti);
    }

    return;
}




/*
 * @COMPLEXITY: O(NN) where NN is the value of the
 *              macro constant defined in the
 *              header file random.h
 * 
 * the function init_by_array64(),takes two arguments
 * as parameters.The first one is an array of lluints
 * and the second one a lluint datatype that represents
 * the length of the array.This function initializes the
 * state vector mt[NN] using the given parameters.
 *
 * @param:  lluint      *init_key
 * @param:  lluint      key_length
 * @return: void
 *
 */

void init_by_array64(lluint init_key[],lluint key_length)
{
    lluint i,j,k;
    init_genrand64(19650218ULL);
    i=1; j=0; k=(NN>key_length ? NN : key_length);

    for (;k;k--)
    {
        mt[i]=(mt[i]^((mt[i-1]^(mt[i-1]>>62))*
            3935559000370003845ULL))+init_key[j]+j;
        i++; j++;
        if (j>=NN) { mt[0]=mt[NN-1]; i=1; }
        if (j>=key_length) { j=0; }
    }

    for (k=NN-1;k;k--)
    {
        mt[i]=(mt[i]^((mt[i-1]^(mt[i-1]>>62))*
            2862933555777941757ULL))-i; i++;
        if (i>=NN) { mt[0]=mt[NN-1]; i=1; }
    }

    mt[0]=1ULL<<63;
    return;
}




/*
 * @COMPLEXITY: O(NN) where NN is the value of the macro
 *              constant defined in the header file random.h
 * 
 * The function genrand64_int64(),takes no arguments as
 * parameters and returns a randomly generated number
 * from the range [ 0, 2^64 - 1].In detail,this function
 * returns a pseudo-random 64-bit value unsigned long long 
 * integer based on the mersenne twister algorithm.
 *
 * @param:  void
 * @return: lluint
 *
 */

lluint genrand64_int64(void)
{
    int i; lluint x;
    static lluint mag01[2]={0ULL, MATRIX_A};

    if (mti>=NN)
    {
        if (mti==NN+1)
        {
            init_genrand64(5489ULL);
        }

        for (i=0;i<NN-MM;i++)
        {
            x=(mt[i]&UM)|(mt[i+1]&LM);
            mt[i]=mt[i+MM]^(x>>1)^mag01[(int)(x&1ULL)];
        }

        for (;i<NN-1;i++)
        {
            x=(mt[i]&UM)|(mt[i+1]&LM);
            mt[i]=mt[i+(MM-NN)]^(x>>1)^mag01[(int)(x&1ULL)];
        }

        x=(mt[NN-1]&UM)|(mt[0]&LM);
        mt[NN-1]=mt[MM-1]^(x>>1)^mag01[(int)(x&1ULL)];
        mti=0;
    }
    
    x=mt[mti++];
    x^=(x>>29)&0x5555555555555555ULL;
    x^=(x<<17)&0x71D67FFFEDA60000ULL;
    x^=(x<<37)&0xFFF7EEE000000000ULL;
    x^=(x>>43);
    return x;
}





/*
 * @COMPLEXITY: O(NN) where NN is the value of the macro
 *              constant defined in the header file random.h
 * 
 * The function genrand64_int63(),takes no arguments as parameters
 * and returns a randomly generated number from the range [ 0, 2^63 -1 ].
 * In detail,this function returns a pseudo-random 64-bit long long
 * integer based on the mersenne twister algorithm.
 *
 * @param:  void
 * @return: llint
 *
 */

llint genrand64_int63(void) { return (llint )(genrand64_int64()>>1); }





/*
 * @COMPLEXITY: O(NN) where NN is the value of the macro
 *              constant defined in the header file random.h
 * 
 * The function genrand64_real1(),takes no arguments as parameters
 * and returns a randomly generated number from the range [ 0, 1 ].
 * In detail,this function returns a pseudo-random 64-bit double
 * numeral based on the mersenne twister algorithm.
 *
 * @param:  void
 * @return: double
 *
 */

double genrand64_real1(void) { return (genrand64_int64()>>11)*(1.0/9007199254740991.0); }





/*
 * @COMPLEXITY: O(NN) where NN is the value of the macro
 *              constant defined in the header file random.h
 * 
 * The function genrand64_real2(),takes no arguments as parameters
 * and returns a randomly generated number from the range [ 0, 1 ).
 * In detail,this function returns a pseudo-random 64-bit double
 * numeral based on the mersenne twister algorithm.
 *
 * @param:  void
 * @return: double
 *
 */

double genrand64_real2(void) { return (genrand64_int64()>>11)*(1.0/9007199254740992.0); }




/*
 * @COMPLEXITY: O(NN) where NN is the value of the macro
 *              constant defined in the header file random.h
 * 
 * The function genrand64_real3(),takes no arguments as parameters
 * and returns a randomly generated number from the range ( 0, 1 ).
 * In detail,this function returns a pseudo-random 64-bit double
 * numeral based on the mersenne twister algorithm.
 *
 * @param:  void
 * @return: double
 *
 */

double genrand64_real3(void) { return ((genrand64_int64()>>12)+0.5)*(1.0/4503599627370496.0); }


