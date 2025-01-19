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


/**
 * @brief Data structure representing a hash table.
 */
typedef struct
{
    void **A; ///< @brief Pointers to memory blocks holding hash table elements.
    int chain_type; ///< @brief The type of separate chaining method (linked list or tree).
    unsigned long long int n; ///< @brief The number of elements in the hash table.
    unsigned long long int size; ///< @brief The current memory size of the hash table.
    double load_factor; ///< @brief the load factor of the hash table.
    mads_uni_hash_t *hfunc; ///< @brief A universal hashing function data structure.
    mads_hash_table_hash_fn hash; ///< @brief The user-defined hashing function for the key element.
} mads_hash_table_t;


/**
 * @brief Function to create a new hash table.
 * @param[in] hash The hashing function for the key element.
 * @param[in] chain_type The type of separate chaining method.
 * @return Pointer to created hash table.
 */
MADS_EXPORT mads_hash_table_t *mads_hash_table_create(mads_hash_table_hash_fn hash, int chain_type);

/**
 * @brief Function to insert a (key, value) pair into the hash table.
 * @param[in,out] t The hash table to insert into.
 * @param[in] p The key value pair to add.
 */
MADS_EXPORT void mads_hash_table_insert(mads_hash_table_t *t, mads_pair_t *p);

/**
 * @brief Function to look up the hash table for the given key.
 * @param[in] t The hash table to perform the lookup.
 * @param[in] key The key element to search for.
 * @return One if the key already exists, zero otherwise.
 */
MADS_EXPORT int mads_hash_table_lookup(const mads_hash_table_t *t, void *key);

/**
 * @brief Function to remove a (key, value) pair from the hash table.
 * @param[in,out] t The hash table from which to remove.
 * @param[int] key The key element to be removed.
 */
MADS_EXPORT void mads_hash_table_remove(mads_hash_table_t *t, void *key);

/**
 * @brief Function to retrieve the value associated with the given key element from the hash table.
 * @param[in] t The hash table from which to retrieve the value element of the given key.
 * @param[in] key The key element whose value we must retrieve.
 * @return The value assocaited with the given element.
 */
MADS_EXPORT void *mads_hash_table_get_value(const mads_hash_table_t *t, void *key);

/**
 * @brief Function to change the value associated with the given key element into the hash table.
 * @param[in,out] t The hash table from which to change the value element of the given key.
 * @param[in] key The key element wwho value must be changed.
 * @param[in] value The new value to replace the old one.
 */
MADS_EXPORT void mads_hash_table_change_value(const mads_hash_table_t *t, void *key, void *value);


/**
 * @brief Function to clear the hash table.
 * @param[in,out] t Hash table data structure to be cleared.
 */
MADS_EXPORT void mads_hash_table_clear(mads_hash_table_t *t);

/**
 * @brief Function to print the contents of the hash table.
 * @param[in] t The hash table whose contents will be printed.
 */
MADS_EXPORT void mads_hash_table_print(const mads_hash_table_t *t);

/**
 * Function to free hash table and release all allocated memory.
 * @param[in,out] t The hash table to be freed.
 */
MADS_EXPORT void mads_hash_table_free(mads_hash_table_t **t);


#ifdef __cplusplus
}
#endif


#endif //MADS_DATA_STRUCTURES_HASH_TABLE_H
