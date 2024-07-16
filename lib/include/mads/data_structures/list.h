// ReSharper disable CppDoxygenUnresolvedReference


/**
 * @file list.h
 * @brief This file contains the API definitions for the MADS Double Linked List data structure.
 * The MADS Linked List data structure implementation in this file supports operations for creation, insertion, removal,
 * accessing list elements and some additional functionality. It also supports custom comparison, print and destruction
 * functionality passed as function pointers.
 */


#ifndef MADS_DATA_STRUCTURES_LIST_H
#define MADS_DATA_STRUCTURES_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include <mads_export.h>

/**
 * @brief Compare function type.
 * @details This type is used to pass a function to compare two list elements. This function pointer is used while maintaining
 *          the ordering or while checking for the existence of an element in the list.
 * @param [in] GenericPointer to the first element.
 * @param [in] GenericPointer to the second element.
 * @return Integer value less than, equal to, or greater than zero if the first argument is considered to be respectively
 *         less than, equal to, or greater than the second.
 */
typedef int (*mads_list_comparator_fn)(const void *, const void *);

/**
 * @brief Print function type.
 * @details This type is used to pass a function to print a list element.
 *          This function pointer is used while implementing the print functionality.
 * @param [in] GenericPointer to the element.
 */
typedef void (*mads_list_printer_fn)(const void *);

/**
 * @brief Destroy function type.
 * @details This type is used to pass a function to destroy/free a list element.
 *          This function is used while implementing the destroy list functionality.
 * @param [in] GenericPointer to the element.
 */
typedef void (*mads_list_destructor_fn)(void *);

// Forward declaration for Linked list node type
typedef struct mads_llnode mads_llnode_t;

/**
 * @brief Data structure that represents a node in a linked list.
 */
struct mads_llnode
{
    void *data; ///< @brief Pointer to the data of the list node
    mads_llnode_t *next; ///< @brief Pointer to the next node in the list
    mads_llnode_t *previous; ///< @brief Pointer to the previous node in the list
};

/**
 * @brief Data structure that represents a doubly linked list.
 */
typedef struct
{
    unsigned long long int size; ///< @brief Number of elements in the list
    mads_llnode_t *head; ///< @brief Pointer to the head of the list
    mads_llnode_t *foot; ///< @brief Pointer to the tail of the list
    mads_list_comparator_fn cmp; ///< @brief Function to compare two elements in the list
    mads_list_printer_fn print; ///< @brief Function to print an element of the list
    mads_list_destructor_fn destroy; ///< @brief Function to destroy an element of the list
} mads_list_t;


/**
* @brief Creates a doubly linked list
* @details This function creates a new doubly linked list and initializes its attributes.
* The compare, print, and destroy function pointers are set to the provided input functions.
* The size is initialized to 0 and head and foot pointers are set to NULL.
* @param [in] comparator User provided function pointer for comparing two list elements
* @param [in] printer User provided function pointer for printing an element of the list
* @param [in] destructor User provided function pointer to free or delete an element of the list
* @return Pointer to the newly created list
*/
MADS_EXPORT mads_list_t *mads_list_create(mads_list_comparator_fn comparator, mads_list_printer_fn printer, mads_list_destructor_fn destructor);

/**
* @brief Adds a new element to the front of the list
* @details This function creates a new node with the provided data and adds it to the front of the list.
* It then updates the head of the list to the newly created node.
* @param [in] list The list where the new element should be added
* @param [in] data The data to be stored in the new node
*/
MADS_EXPORT void mads_list_push(mads_list_t *list, void *data);


/**
* @brief Frees the list and its elements
* @details This function traverses through the list, freeing each node and its data using the provided destroy function.
* After freeing all nodes, it frees the list itself.
* @param [in] list The list to be freed
*/
MADS_EXPORT void mads_list_free(mads_list_t *list);


/**
* @brief Appends a new element to the end of the list
* @details This function creates a new node with the provided data and adds it to the end of the list.
* It then updates the foot of the list to the newly created node.
* @param [in] list The list where the new element should be added
* @param [in] data The data to be stored in the new node
*/
MADS_EXPORT void mads_list_append(mads_list_t *list, void *data);

/**
* @brief Inserts a new element at a specific position in the list
* @details This function creates a new node with the provided data and inserts it at the specified position in the list.
* It adjusts the next and previous pointers of the adjacent nodes to maintain the list.
* @param [in] list The list where the new element should be inserted
* @param [in] data The data to be stored in the new node
* @param [in] position The position where the new node should be inserted
*/
MADS_EXPORT void mads_list_insert_at(mads_list_t *list, void *data, unsigned long long int position);

/**
* @brief Returns the element at the head of the list
* @param [in] list The list whose head element should be returned
* @return Pointer to the data in the head node of the list
*/
MADS_EXPORT void *mads_list_get_head(const mads_list_t *list);

/**
* @brief Returns the element at the foot of the list
* @param [in] list The list whose foot element should be returned
* @return Pointer to the data in the foot node of the list
*/
MADS_EXPORT void *mads_list_get_foot(const mads_list_t *list);


/**
* @brief This function retrieves an element from the list at the given position.
* @details This function takes in the list and the position as inputs. It then navigates to the given position on
*          the list and retrieves the corresponding data.
* @param list The list from which to retrieve the data.
* @param position The specified position in the list where the object/data is located.
*
* @return Returns a `void*` pointer to the requested object/data.
*/
MADS_EXPORT void *mads_list_get_at(const mads_list_t *list, unsigned long long int position);

/**
* @brief This function removes the head node from the list.
* @details This function takes in a list, removes the head node and adjusts the `head` pointer to point at the next node.
* @param list The list from which to remove the head.
* @return void
*/
MADS_EXPORT void mads_list_remove_head(mads_list_t *list);

/**
* @brief This function removes the foot node from the list.
* @details This function takes in a list, removes the last node and adjusts the `foot` pointer to point at the previous node.
* @param list The list from which to remove the foot.
* @return void
*/
MADS_EXPORT void mads_list_remove_foot(mads_list_t *list);


/**
* @brief This function removes an element from the list at the given position.
* @details This function takes in the list and the position as inputs. It navigates to the given position on
*          the list, removes the corresponding node and adjusts the `next` and `previous` pointers of the adjacent nodes.
* @param list The list from which to remove the node.
* @param position The specified position in the list where the node is located.
* @return void
*/
MADS_EXPORT void mads_list_remove_at(mads_list_t *list, unsigned long long int position);

/**
* @brief This function prints all the elements in the list.
* @param list The list whose elements are to be printed.
* @return void
*/
MADS_EXPORT void mads_list_print(const mads_list_t *list);

/**
* @brief This function returns the size of the list.
* @param list The list whose size is to be returned.
* @return The number of elements in the list.
*/
MADS_EXPORT unsigned long long int mads_list_size(const mads_list_t *list);

/**
* @brief This function checks if the list is empty.
* @param list The list to check.
* @return 1 if the list is empty, 0 otherwise.
*/
MADS_EXPORT int mads_list_is_empty(const mads_list_t *list);

/**
* @brief This function checks if a specific element exists in the list.
* @param list The list to check.
* @param item The item to search for.
* @return 1 if the item exists in the list, 0 otherwise.
*/
MADS_EXPORT int mads_list_has_elem(const mads_list_t *list, const void *item);


#ifdef __cplusplus
}
#endif

#endif //MADS_DATA_STRUCTURES_LIST_H
