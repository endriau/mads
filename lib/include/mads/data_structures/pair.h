// ReSharper disable CppDoxygenUnresolvedReference

/**
 * @file pair.h
 * @brief The file contains API definitions for the MADS pair data structure.
 * The pair implementation comprises two fields, a cue and a value component.
 * The implementation for each in this file supports operations for creation, get
 * and set functions. It also supports custom comparison, print and destruction
 * functionality passed as function pointers.
 */

#ifndef MADS_DATA_STRUCTURES_PAIR_H
#define MADS_DATA_STRUCTURES_PAIR_H


#ifdef __cplusplus
extern "C" {
#endif


#include <mads_export.h>


/**
 * @typedef mads_cue_comparator_fn
 * @brief Function pointer type for comparing two cues.
 *
 * A function of this type should take two void pointers to the cues that need to be compared.
 * The function should cast the void pointers to the appropriate data types before comparing them.
 * The comparison function you provide should return an integer less than, equal to, or greater than zero
 * if the first cue is considered to be respectively less than, equal to, or greater than the second.
 * @param [in] GenericPointer Pointer to the first cue.
 * @param [in] GenericPointer Pointer to the second cue.
 * @return An integer less than, equal to, or greater than zero if the first cue is considered to
 * be respectively less than, equal to, or greater than the second.
 */
typedef int (*mads_cue_comparator_fn)(const void *, const void *);


/**
 * @typedef mads_cue_printer_fn
 * @brief Function pointer type for printing a cue.
 * A function of this type should take a void pointer to the cue that needs to be printed.
 * The function should cast the void pointer to the appropriate data type before printing it.
 * @param [in] GenericPointer Pointer to the cue.
 */
typedef void (*mads_cue_printer_fn)(const void *);


/**
 * @typedef mads_cue_destructor_fn
 * @brief Function pointer type for destroying a cue.
 * A function of this type should take a void pointer to the cue that needs to be destroyed.
 * The function should cast the void pointer to the appropriate data type before destroying it.
 * @param [in] GenericPointer Pointer to the cue to be destroyed.
 */
typedef void (*mads_cue_destructor_fn)(void *);


/**
* @typedef mads_value_comparator_fn
* @brief Function pointer type for comparing two values.
* A function of this type should take two void pointers to the values that need to be compared.
* The function should cast the void pointers to the appropriate data types before comparing them.
* The comparison function you provide should return an integer less than, equal to, or greater than zero
* if the first value is considered to be respectively less than, equal to, or greater than the second.
* @param [in] GenericPointer1 Pointer to the first value.
* @param [in] GenericPointer2 Pointer to the second value.
* @return An integer less than, equal to, or greater than zero if the first value is considered to
* be respectively less than, equal to, or greater than the second.
*/
typedef int (*mads_value_comparator_fn)(const void *, const void *);


/**
 * @typedef mads_value_printer_fn
 * @brief Function pointer type for printing a value.
 * A function of this type should take a void pointer to the value that
 * needs to be printed. The function should cast the void pointer to the
 * appropriate data type before printing it.
 * @param [in] GenericPointer Pointer to the value.
 */
typedef void (*mads_value_printer_fn)(const void *);


/**
 * @typedef mads_value_destructor_fn
 * @brief Function pointer type for destroying a value.
 * A function of this type should take a void pointer to
 * the value that needs to be destroyed. The function should
 * cast the void pointer to the appropriate data type before
 * destroying it.
 * @param [in] GenericPointer Pointer to the value to be destroyed.
 */
typedef void (*mads_value_destructor_fn)(void *);

/**
 * @brief Data structure that represents the key of a pair.
 */
typedef struct
{
    void *cue; ///< @brief Pointer to the data that represents the cue
    mads_cue_comparator_fn comparator; ///< @brief Function pointer to a comparator for the cue
    mads_cue_printer_fn printer; ///< @brief  Function pointer to a printer for the cue
    mads_cue_destructor_fn destructor; ///< @brief  Function pointer to a destructor for the cue
} mads_cue_t;


/**
 * @brief Data structure that represents the value of a pair.
 */
typedef struct
{
    void *value; ///< @brief  Pointer to the data that represents the value
    mads_value_comparator_fn comparator; ///< @brief  Function pointer to a comparator for the value
    mads_value_printer_fn printer; ///< @brief  Function pointer to a printer for the value
    mads_value_destructor_fn destructor; ///< @brief  Function pointer to a destructor for the value
} mads_value_t;


/**
 * @brief Data structure that represents a pair of objects, (key, value).
 * The key and value can be of any type as long as the necessary comparators,
 * printers are provided. Note that the destructor is optional.
 */
typedef struct
{
    mads_cue_t *k; ///< @brief The key of the pair
    mads_value_t *v; ///< @brief The value of the pair
} mads_pair_t;


/**
 * @brief This function is used to create a new mads_cue_t object.
 * @param [in] cue    - This should be a pointer that points to the cue data.
 * @param [in] comparator    - A function pointer set to compare two cue items.
 * @param [in] printer  - A function pointer that is set to handle cue printing.
 * @param [in] destructor - A function pointer that is set to manage cue destruction.
 * @return This function returns a pointer to the new mads_cue_t object.
 */
MADS_EXPORT mads_cue_t *mads_cue_create(void *cue, mads_cue_comparator_fn comparator, mads_cue_printer_fn printer, mads_cue_destructor_fn destructor);


/**
 * @brief This function provides a way to access the data related to the cue from a mads_cue_t object.
 * @param [in] k - A pointer to an instance of mads_cue_t.
 * @return - The function returns a void pointer. This pointer points to the data related to the cue.
 */
MADS_EXPORT void *mads_cue_get(const mads_cue_t *k);


/**
 * @brief This function is used to compare the cue data from a mads_cue_t object with another give data
 * @param [in] k - This should be a pointer to an instance of mads_cue_t.
 * @param [in] data - This should be a void pointer to the data to be compared with the cue data.
 * @return This function returns an integer less than, equal to, or greater than zero if the cue
 * data is considered to be respectively less than, equal to, or greater than the data.
 */
MADS_EXPORT int mads_cue_compare_to(const mads_cue_t *k, const void *data);


/**
  * @brief Prints the cue data from a mads_cue_t object using the provided print function.
  * @param [in] k - A pointer to an instance of mads_cue_t whose cue data is to be printed.
  */
MADS_EXPORT void mads_cue_print(const mads_cue_t *k);


/**
 * @brief This function is used to free the mads_cue_t object.
 * @details It will use the destroy function if it was provided during the creation of the mads_cue_t object.
 *          It's important to remember that it does not deallocate the memory for the cue data itself.
 * @param [in] k - A pointer to an instance of mads_cue_t which is to be freed.
 */
MADS_EXPORT void mads_cue_free(mads_cue_t *k);


/**
 * @brief This function is used to create a new mads_value_t object.
 * @param [in] value   - This should be a pointer that points to the value data.
 * @param [in] comparator     - A function pointer set to compare two value items.
 * @param [in] printer   - A function pointer that is set to handle value printing.
 * @param [in] destructor - A function pointer that is set to manage value destruction.
 * @return This function returns a pointer to the new mads_value_t object.
 */
MADS_EXPORT mads_value_t *mads_value_create(void *value, mads_value_comparator_fn comparator, mads_value_printer_fn printer, mads_value_destructor_fn destructor);


/**
 * @brief Function to obtain the value data from a mads_value_t object.
 * @details This function takes as input a pointer to a mads_value_t object and retrieves the value it's storing.
 * @param [in] v Pointer to the mads_value_t object whose value data we want to retrieve.
 * @return Returns a void pointer that points to the value data stored in the input mads_value_t object.
 */
MADS_EXPORT void *mads_value_get(const mads_value_t *v);


/**
 * @brief This function is used to compare the value data from a mads_value_t object with the data provided.
 * @details This function calls the comparator passed during the creation of mads_value_t object for comparison.
 * @param [in] v - This should be a pointer to an instance of mads_value_t.
 * @param [in] data - This should be a void pointer to the data to be compared with the value data.
 * @return This function returns an integer less than, equal to, or greater than zero if the value
 * data is considered to be respectively less than, equal to, or greater than the data.
 */
MADS_EXPORT int mads_value_compare_to(const mads_value_t *v, const void *data);


/**
 * @brief This function is used to print the value data from a mads_value_t object using the provided print function.
 * @param [in] v - A pointer to an instance of mads_value_t whose value data is to be printed.
 */
MADS_EXPORT void mads_value_print(const mads_value_t *v);


/**
 * @brief This function is used to free the memory associated with a mads_value_t object.
 * @details This function not only frees the memory for the mads_value_t object but also calls
 * the destroy function, if it was provided during the creation of the mads_value_t object, to
 * deal with the memory associated with the value data.
 * Also, it's important to note that this function does not ensure the removal of any reference to
 * the mads_value_t object in other data structures.
 * @param [in] v Is a pointer to a mads_value_t object which is to be freed.
 */
MADS_EXPORT void mads_value_free(mads_value_t *v);


/**
 * @brief Creates a new mads_pair_t object.
 * This function takes two pointers to mads_cue_t and mads_value_t objects respectively
 * and packages them into a mads_pair_t object. This object represents a key-value pair
 * in which mads_cue_t acts as the key and mads_value_t, as the value.
 * @param [in] k - Pointer to a mads_cue_t object that represents the key.
 * @param [in] v - Pointer to a mads_value_t object that represent the value.
 * @return A pointer to the newly created mads_pair_t object.
 */
MADS_EXPORT mads_pair_t *mads_pair_create(mads_cue_t *k, mads_value_t *v);


/**
 * @brief Function to get the cue from a mads_pair_t object.
 * This function retrieves the mads_cue_t element from a given mads_pair_t object.
 * @param [in] p A pointer to a mads_pair_t object.
 * @return A pointer to the mads_cue_t element from the specified mads_pair_t object.
 */
MADS_EXPORT mads_cue_t *mads_pair_get_cue(const mads_pair_t *p);


/**
 * @brief Function to get the value from a mads_pair_t object.
 * This function retrieves the mads_value_t element from a given mads_pair_t object.
 * @param [in] p A pointer to a mads_pair_t object.
 * @return A pointer to the mads_value_t element from the specified mads_pair_t object.
 */
MADS_EXPORT mads_value_t *mads_pair_get_value(const mads_pair_t *p);


/**
 * @brief This function is used to change the cue of a mads_pair_t object.
 * @details In case the cue part of the provided pair needs to be replaced or updated,
 * this function can be used. It replaces the existing cue within the pair with the newly
 * provided cue. Note that this function does NOT free the old cue memory, you should handle
 * that manually if necessary.
 * @param [in] p - A pointer to a mads_pair_t object whose cue is to be changed.
 * @param [in] new_k - A pointer to a mads_cue_t object that will now act as the new cue.
 */
MADS_EXPORT void mads_pair_change_cue(mads_pair_t *p, mads_cue_t *new_k);


/**
 * @brief This function is used to change the value of a mads_pair_t object.
 * @details In case the value part of the provided pair needs to be replaced or updated,
 * this function can be used. It replaces the existing value within the pair with the newly
 * provided value. Note that this function does NOT free the old value memory, you should handle
 * that manually if necessary.
 * @param [in] p - A pointer to a mads_pair_t object whose value is to be changed.
 * @param [in] new_v - A pointer to a mads_value_t object that will now act as the new value.
 */
MADS_EXPORT void mads_pair_change_value(mads_pair_t *p, mads_value_t *new_v);


/**
 * @brief This function is used to print the cue and value data from a mads_pair_t object.
 * @details This function first prints the cue followed by the value data from a mads_pair_t object.
 * The functions mads_cue_print and mads_value_print are used to print the cue and value respectively.
 * The functions used for printing are those that were passed during the creation of mads_cue_t and mads_value_t objects.
 * @param [in] p - A pointer to an instance of mads_pair_t that is to be printed.
 */
MADS_EXPORT void mads_pair_print(const mads_pair_t *p);


/**
 * @brief This function is used to deallocate the memory linked with a mads_pair_t object.
 * @details This function not only frees the memory allocated for the mads_pair_t object, but
 * also calls the destruction functions for mads_cue_t and mads_value_t, if present during the
 * creation of these structures. Please note that this function does not ensure the removal of
 * any reference to the mads_pair_t object in other data structures.
 * @param [in] p - A pointer to the mads_pair_t object which is to be freed.
 */
MADS_EXPORT void mads_pair_free(mads_pair_t *p);


#ifdef __cplusplus
}
#endif

#endif //MADS_DATA_STRUCTURES_PAIR_H
