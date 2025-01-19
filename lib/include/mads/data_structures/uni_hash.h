#ifndef MADS_DATA_STRUCTURES_UNI_HASH_H
#define MADS_DATA_STRUCTURES_UNI_HASH_H


/**
 * @file uni_hash.h
 * @brief The file contains API definitions for the MADS universal hash data structure.
 * The universal hash implementation comprises a key value, a pointer to an array of values,
 * and the size of the table used by the hash function.
 * The implementation in this file supports operations for creating the hash object,
 * retrieving the generated values, getting the table size and key value, printing the 
 * hash object details, and freeing the allocated memory.
 */


#ifdef __cplusplus
extern "C" {
#endif


#include <mads_export.h>


/**
 * @brief Data structure that represents a universal hash function.
 */
typedef struct
{
    unsigned long long int kvalue; ///< @brief The key value used in the hash function.
    unsigned long long int *values; ///< @brief Pointer to the array of values generated by the hash function.
    unsigned long long int tabsize; ///< @brief The size of the table used by the hash function.
} mads_uni_hash_t;


/**
 * @brief This function is used to create a new mads_uni_hash_t object.
 * @param [in] ts - The size of the table used by the hash function.
 * @param [in] k - The key value used in the hash function.
 * @return This function returns a pointer to the new mads_uni_hash_t object.
 */
MADS_EXPORT mads_uni_hash_t *mads_uni_hash_create(unsigned long long int ts, unsigned long long int k);

/**
 * @brief This function is used to get the array of values generated by the hash function.
 * @param [in] h - A pointer to the mads_uni_hash_t object.
 * @return This function returns a pointer to the array of values generated by the hash function.
 */
MADS_EXPORT unsigned long long int *mads_uni_hash_get_values(const mads_uni_hash_t *h);

/**
 * @brief This function is used to get the table size used by the hash function.
 * @param [in] h - A pointer to the mads_uni_hash_t object.
 * @return This function returns the size of the table used by the hash function.
 */
MADS_EXPORT unsigned long long int mads_uni_hash_get_table_size(const mads_uni_hash_t *h);

/**
 * @brief This function is used to get the key value used in the hash function.
 * @param [in] h - A pointer to the mads_uni_hash_t object.
 * @return This function returns the key value used in the hash function.
 */
MADS_EXPORT unsigned long long int mads_uni_hash_get_k(const mads_uni_hash_t *h);

/**
 * @brief This function is used to print the details of the mads_uni_hash_t object.
 * @param [in] h - A pointer to the mads_uni_hash_t object.
 */
MADS_EXPORT void mads_uni_hash_print(const mads_uni_hash_t *h);

/**
 * @brief This function is used to free the memory allocated for the mads_uni_hash_t object.
 * @param [in] h - The mads_uni_hash_t object to be freed.
 */
MADS_EXPORT void mads_uni_hash_free(mads_uni_hash_t **h);


#ifdef __cplusplus
}
#endif


#endif //MADS_DATA_STRUCTURES_UNI_HASH_H
