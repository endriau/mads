

#ifndef MADS_DATA_STRUCTURES_STACK_H
#define MADS_DATA_STRUCTURES_STACK_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file stack.h
 * @brief This file provides the declarations for a generic stack data structure.
 *
 * The stack data structure declared here employs a dynamic array implementation. Stack elements are stored in an array
 * which grows as needed. Elements are pushed to the top of the stack and popped from the top as well. The stack also
 * provides functionality to check if a particular element exists within it or if the stack itself is empty.
 *
 * In order to accommodate elements of any type, pointers to void are used. To compare, print and destroy specific types
 * of elements, function pointers are used. These function pointers need to be set while creating the stack according to
 * the type of elements the stack is going to hold.
 */


/**
 * @brief Function pointer type for comparing elements in the stack.
 * @param[in] a First element pointer.
 * @param[in] b Second element pointer.
 * @return An integer less than, equal to, or greater than zero if the first argument
 * is considered to be respectively less than, equal to, or greater than the second.
 */
typedef int (*stack_compare_fn)(const void *a, const void *b);

/**
 * @brief Function pointer type for printing elements in the stack.
 * @param[in] item Element pointer.
 */
typedef void (*stack_print_fn)(const void *item);

/**
 * @brief Function pointer type for destroying elements in the stack.
 * @param[out] item Element pointer.
 */
typedef void (*stack_destroy_fn)(void *item);

/**
 * @brief Struct representing a stack.
 */
typedef struct
{
    void **A;           /** @brief Pointer to the array holding the stack elements. */
    long long int n;    /** @brief Index of the top element on the stack. */
    long long int size; /** @brief Total size of the stack. */
    stack_compare_fn cmp; /** @brief Comparison function for the stack elements. */
    stack_print_fn print; /** @brief Print function for the stack elements. */
    stack_destroy_fn destroy; /** @brief Destroy function for the stack elements. */
} stack_t;

/**
 * @brief Creates a new stack.
 * @param[in] cmp Comparison function.
 * @param[in] print Print function.
 * @param[in] destroy Destroy function.
 * @return New stack.
 */
stack_t *stack_create(stack_compare_fn cmp, stack_print_fn print, stack_destroy_fn destroy);

/**
 * @brief Pushes an item on to the stack.
 * @param[out] s Stack pointer.
 * @param[in] item Item pointer.
 */
void stack_push(stack_t *s, void *item);

/**
 * @brief Removes the item on top of the stack and returns it.
 * @param[out] s Stack pointer.
 * @return Item pointer.
 */
void *stack_pop(stack_t *s);

/**
 * @brief Prints the stack.
 * @param[in] s Stack pointer.
 */
void stack_print(const stack_t *s);

/**
 * @brief Frees the stack.
 * @param[out] s Stack pointer.
 */
void stack_free(stack_t *s);

/**
 * @brief Checks if the stack is empty.
 * @param[in] s Stack pointer.
 * @return 1 if empty, 0 otherwise.
 */
int stack_is_empty(const stack_t *s);

/**
 * @brief Checks if a certain item is in the stack.
 * @param[in] s Stack pointer.
 * @param[in] item Item pointer.
 * @return 1 if found, 0 otherwise.
 */
int stack_has_elem(const stack_t *s, const void *item);


#ifdef __cplusplus
}
#endif


#endif //MADS_DATA_STRUCTURES_STACK_H
