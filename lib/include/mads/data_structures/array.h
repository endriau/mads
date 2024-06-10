// ReSharper disable CppDoxygenUnresolvedReference



/**
 * @file array.h
 * @brief This header file provides an API for managing dynamic arrays.
 *
 * In this file, a generic dynamic array is implemented. It includes methods to create,
 * manipulate, and destruct arrays. The dynamic array is a data structure that holds pointers
 * to your stored elements. It supports adding elements in different ways: appending, prepending,
 * and inserting at a specific index. Removing an element at a specific index is also supported.
 *
 * Each array must contain three important function pointers: a comparator for comparing elements,
 * a printer for displaying elements, and a destructor for deleting the elements.
 */

#ifndef MADS_DATA_STRUCTURES_ARRAY_H
#define MADS_DATA_STRUCTURES_ARRAY_H


/**
 * @brief Function pointer type for comparing elements in the array
 * @param[in] GenericPointer The first element to compare
 * @param[in] GenericPointer The second element to compare
 * @return An integer less than, equal to, or greater than zero if the first argument is
 * considered to be respectively less than, equal to, or greater than the second.
 */
typedef int (*mads_array_comparator_fn)(const void *, const void *);

/**
 * @brief Function pointer type for printing array elements
 * @param[in] GenericPointer The element to print
 */
typedef void (*mads_array_printer_fn)(const void *);

/**
 * @brief Function pointer type for destructing the array elements
 * @param[in] GenericPointer The element to be destructed
 */
typedef void (*mads_array_destructor_fn)(void *);

/**
 * @brief Data structure representing an array
 */
typedef struct
{
    void **mblocks; ///< @brief Pointers to blocks holding array elements
    long long int index; ///< @brief Current index
    long long int msize; ///< @brief Maximum size of the array
    mads_array_comparator_fn comparator; ///< @brief Comparator function for array elements
    mads_array_printer_fn printer; ///< @brief Printer function for array elements
    mads_array_destructor_fn destructor; ///< @brief Destructor function for array elements
} mads_array_t;

/**
 * @brief Function to create a new array
 * @param[in] comparator Comparator function
 * @param[in] printer Printer function
 * @param[in] destructor Destructor function
 * @return Pointer to a created array
 */
mads_array_t *mads_array_create(mads_array_comparator_fn comparator, mads_array_printer_fn printer, mads_array_destructor_fn destructor);

/**
 * @brief Function to append data to an array
 * @param[in,out] array The array to append to
 * @param[in] data The data to append
 */
void mads_array_append(mads_array_t *array, void *data);

/**
 * @brief Function to prepend data to an array
 * @param[in,out] array The array to prepend to
 * @param[in] data The data to prepend
 */
void mads_array_prepend(mads_array_t *array, void *data);

/**
 * @brief Function to insert data at a specific index in the array
 * @param[in,out] array The array to insert into
 * @param[in] index The position index where new data is to be inserted
 * @param[in] data The new data to insert
 */
void mads_array_insert_at(mads_array_t *array, long long int index, void *data);

/**
 * @brief Function to remove data at a specific index in the array
 * @param[in,out] array The array to remove data from
 * @param[in] index The position index where data is to be removed
 */
void mads_array_remove_at(mads_array_t *array, long long int index);

/**
 * @brief Function to set data at a specific index in the array
 * @param[in,out] array The array to set data in
 * @param[in] index The position index where data is to be set
 * @param[in] data The data to set
 */
void mads_array_set_at(const mads_array_t *array, long long int index, void *data);

/**
 * @brief Function to get data at a specific index from the array
 * @param[in] array The array to get data from
 * @param[in] index The position index of wanted data
 * @return The data at the specified position or NULL if index is invalid
*/
void *mads_array_get_at(const mads_array_t *array, long long int index);

/**
 * @brief Function to check if an array contains a given item
 * @param[in] array The array to check
 * @param[in] item The item to find in the array
 * @return The position index of the item if found, -1 otherwise
 */
long long int mads_array_has_element(const mads_array_t *array, const void *item);

/**
 * @brief Function to get the size of an array
 * @param[in] array The array to find the size of
 * @return The current size of the array
 */
long long int mads_array_size(const mads_array_t *array);

/**
 * @brief Function to check if an array is empty
 * @param[in] array The array to check
 * @return 1 if the array is empty, 0 otherwise
 */
int mads_array_is_empty(const mads_array_t *array);

/**
 * @brief Function to clear an array, removing all elements
 * @param[in,out] array The array to clear
 */
void mads_array_clear(mads_array_t *array);

/**
 * @brief Function to print an array
 * @param[in] array The array to print
 */
void mads_array_print(const mads_array_t *array);

/**
 * @brief Function to free an array, releasing all allocated memory
 * @param[in,out] array The array to free
 */
void mads_array_free(mads_array_t *array);


#endif //MADS_DATA_STRUCTURES_ARRAY_H
