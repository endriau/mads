#ifndef MADS_DATA_STRUCTURES_UNI_HASH_H
#define MADS_DATA_STRUCTURES_UNI_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mads_export.h>

typedef struct
{
    unsigned long long int kvalue;
    unsigned long long int *values;
    unsigned long long int tabsize;
} mads_uni_hash_t;


MADS_EXPORT mads_uni_hash_t *mads_uni_hash_create(unsigned long long int ts, unsigned long long int k);
MADS_EXPORT unsigned long long int *mads_uni_hash_get_values(const mads_uni_hash_t *h);
MADS_EXPORT unsigned long long int mads_uni_hash_get_table_size(const mads_uni_hash_t *h);
MADS_EXPORT unsigned long long int mads_uni_hash_get_k(const mads_uni_hash_t *h);
MADS_EXPORT void mads_uni_hash_print(const mads_uni_hash_t *h);
MADS_EXPORT void mads_uni_hash_free(mads_uni_hash_t *h);

#ifdef __cplusplus
}
#endif

#endif //MADS_DATA_STRUCTURES_UNI_HASH_H
