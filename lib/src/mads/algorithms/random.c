

#include <mads/algorithms/random.h>


static unsigned long long int mt[MADS_RANDOM_NN];
static int mti = MADS_RANDOM_NN + 1;


void mads_init_genrand64(const unsigned long long int seed)
{
    mt[0] = seed;

    for (mti = 1; mti < MADS_RANDOM_NN; mti++)
    {
        mt[mti] = (6364136223846793005ULL *
            (mt[mti - 1] ^ (mt[mti - 1] >> 62)) + mti);
    }

    return;
}

void mads_init_by_array64(unsigned long long int init_key[], const unsigned long long int key_length)
{
    mads_init_genrand64(19650218ULL);
    unsigned long long int i = 1;
    unsigned long long int j = 0;
    unsigned long long int k = (MADS_RANDOM_NN > key_length ? MADS_RANDOM_NN : key_length);

    for (; k; k--)
    {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 62)) *
            3935559000370003845ULL)) + init_key[j] + j;
        i++;
        j++;
        if (j >= MADS_RANDOM_NN)
        {
            mt[0] = mt[MADS_RANDOM_NN - 1];
            i = 1;
        }
        if (j >= key_length) { j = 0; }
    }

    for (k = MADS_RANDOM_NN - 1; k; k--)
    {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 62)) *
            2862933555777941757ULL)) - i;
        i++;
        if (i >= MADS_RANDOM_NN)
        {
            mt[0] = mt[MADS_RANDOM_NN - 1];
            i = 1;
        }
    }

    mt[0] = 1ULL << 63;
    return;
}

unsigned long long int mads_genrand64_int64(void)
{
    unsigned long long int x;
    static unsigned long long int mag01[2] = {0ULL, MADS_RANDOM_MATRIX_A};

    if (mti >= MADS_RANDOM_NN)
    {
        int i;
        if (mti == MADS_RANDOM_NN + 1)
        {
            mads_init_genrand64(5489ULL);
        }

        for (i = 0; i < MADS_RANDOM_NN - MADS_RANDOM_MM; i++)
        {
            x = (mt[i] & MADS_RANDOM_UM) | (mt[i + 1] & MADS_RANDOM_LM);
            mt[i] = mt[i + MADS_RANDOM_MM] ^ (x >> 1) ^ mag01[(int)(x & 1ULL)];
        }

        for (; i < MADS_RANDOM_NN - 1; i++)
        {
            x = (mt[i] & MADS_RANDOM_UM) | (mt[i + 1] & MADS_RANDOM_LM);
            mt[i] = mt[i + (MADS_RANDOM_MM - MADS_RANDOM_NN)] ^ (x >> 1) ^ mag01[(int)(x & 1ULL)];
        }

        x = (mt[MADS_RANDOM_NN - 1] & MADS_RANDOM_UM) | (mt[0] & MADS_RANDOM_LM);
        mt[MADS_RANDOM_NN - 1] = mt[MADS_RANDOM_MM - 1] ^ (x >> 1) ^ mag01[(int)(x & 1ULL)];
        mti = 0;
    }

    x = mt[mti++];
    x ^= (x >> 29) & 0x5555555555555555ULL;
    x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
    x ^= (x << 37) & 0xFFF7EEE000000000ULL;
    x ^= (x >> 43);
    return x;
}

long long int mads_genrand64_int63(void) { return mads_genrand64_int64() >> 1; }

double mads_genrand64_real1(void) { return (mads_genrand64_int64() >> 11) * (1.0 / 9007199254740991.0); }

double mads_genrand64_real2(void) { return (mads_genrand64_int64() >> 11) * (1.0 / 9007199254740992.0); }

double mads_genrand64_real3(void) { return ((mads_genrand64_int64() >> 12) + 0.5) * (1.0 / 4503599627370496.0); }
