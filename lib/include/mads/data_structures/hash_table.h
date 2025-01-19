// ReSharper disable CppDoxygenUnresolvedReference

/**
 * @file hash_table.h
 * @brief This header file provides an API for managing a hash table.
 * In this file a generic hash table is implemented. It includes methods for create,
 * manipulate and destroy hash tables. It supports insertion, lookup, removal and
 * changing the value of a hash table key.
 *
 * Each hash table must contain an important function pointer: a universal hashing function
 * which tells it how to hash the key values for insertion and queries into the hash table.
 */

#ifndef MADS_DATA_STRUCTURES_HASH_TABLE_H
#define MADS_DATA_STRUCTURES_HASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def MADS_HASH_TABLE_INITIAL_SIZE
 * @brief A macro constant to specify the initial size of the hash table.
 */
#define MADS_HASH_TABLE_INITIAL_SIZE 107

/**
 * @def MADS_HASH_TABLE_CHAIN_LIST
 * @brief A macro constant to represent separate chaining via linked lists.
 */
#define MADS_HASH_TABLE_CHAIN_LIST 76

/**
 * @def MADS_HASH_TABLE_CHAIN_TREE
 * @brief A macro constant to represent separate chaining via balanced trees.
 */
#define MADS_HASH_TABLE_CHAIN_TREE 84

#include <mads_export.h>
#include <mads/data_structures/uni_hash.h>
#include <mads/data_structures/pair.h>

/**
 * @brief A hashing function for the hash table.
 * @param[in] Pointer to a mads_uni_hash_t data structure.
 * @param[in] GenericPointer to the item to be hashed.
 * @return An unsigned integer that represents the computed index.
 */
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
