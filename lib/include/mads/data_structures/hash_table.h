#ifndef MADS_DATA_STRUCTURES_HASH_TABLE_H
#define MADS_DATA_STRUCTURES_HASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define MADS_HASH_TABLE_INITIAL_SIZE 107
#define MADS_HASH_TABLE_CHAIN_LIST 76
#define MADS_HASH_TABLE_CHAIN_TREE 84

#include <mads_export.h>
#include <mads/data_structures/uni_hash.h>
#include <mads/data_structures/pair.h>


typedef unsigned long long int (*mads_hash_table_hash_fn)(const mads_uni_hash_t *, const void *);


typedef struct
{
    void **A;
    int chain_type;
    unsigned long long int n;
    unsigned long long int size;
    double load_factor;
    mads_uni_hash_t *hfunc;
    mads_hash_table_hash_fn hash;
} mads_hash_table_t;


MADS_EXPORT mads_hash_table_t *mads_hash_table_create(mads_hash_table_hash_fn hash, int chain_type);
MADS_EXPORT void mads_hash_table_insert(mads_hash_table_t *t, mads_pair_t *p);
MADS_EXPORT int mads_hash_table_lookup(const mads_hash_table_t *t, void *key);
MADS_EXPORT void mads_hash_table_remove(mads_hash_table_t *t, void *key);
MADS_EXPORT void *mads_hash_table_get_value(const mads_hash_table_t *t, void *key);
MADS_EXPORT void mads_hash_table_change_value(const mads_hash_table_t *t, void *key, void *value);
MADS_EXPORT void mads_hash_table_print(const mads_hash_table_t *t);
MADS_EXPORT void mads_hash_table_free(mads_hash_table_t **t);

#ifdef __cplusplus
}
#endif


#endif //MADS_DATA_STRUCTURES_HASH_TABLE_H
