//
// Created by p0int3r on 6/12/21.
//

#ifndef TINYLIB_ARRAY_H
#define TINYLIB_ARRAY_H

/// Type signature for destructor function pointer.
typedef int (*array_comparator_fn)(const void *, const void *);

// Type signature for a printer function pointer.
typedef void (*array_printer_fn)(const void *);

// Type signature for a destructor function pointer.
typedef void (*array_destructor_fn)(void *);


/// The array_t structure presents the concept of a parametrically polymorphic \n
/// and dynamically growing array data structure. It requires a comparator, a printer \n
/// and a destructor in the form of function pointers that must be supplied by the user. \n
/// When the array is full, it's msize grows geometrically to accommodate the new elements.
typedef struct _array
{
    void **mblocks;                     // The contiguous memory blocks to store elements.
    long long int index;                // The current index at the end of the array.
    long long int msize;                // The number of allocated blocks of memory.
    array_comparator_fn comparator;     // mblocks function pointer to a comparator.
    array_printer_fn printer;           // mblocks function pointer to a printer.
    array_destructor_fn destructor;     // mblocks function pointer to a destructor.
} array_t;


/// This function creates a new array data structure. It takes as arguments function pointers \n
/// to a comparator, printer and destructor. It returns a pointer to the array data structure.
/// \param comparator The comparator function.
/// \param printer The printer function.
/// \param destructor The destructor function.
/// \return A pointer to an array data structure.
/// \complexity O(1)
array_t *array_create(array_comparator_fn comparator, array_printer_fn printer, array_destructor_fn destructor);

/// This function appends an element into the array data structure. \n
/// \param array mblocks pointer to an array data structure.
/// \param data The data to be appended into the array.
/// \complexity O(1)
void array_append(array_t *array, void *data);

/// This function prepends an element into the array data structure. \n
/// \param array mblocks pointer to the array data structure.
/// \param data The data to be prepended into the array.
/// \complexity O(N)
void array_prepend(array_t *array, void *data);

/// This function inserts an element into the array data structure at the specified index. \n
/// All the elements at the index and aftewards are shifted up by one slot to accommodate for \n
/// the insertion of the the given element at the specified index.
/// \param array A pointer to an array data structure.
/// \param index The array index where the element will be inserted at.
/// \param data The data to be inserted into the specified index within the array.
/// \complexity O(N)
void array_insert_at(array_t *array, long long int index, void *data);

/// This function removes an element from the array data structure at the speficied index. \n
/// All elements at the index and afterwards are shifted down by one slot to accommodate for \n
/// the deletion of the given element at the specified index. If a desstructor was provided, \n
/// it will be used to destroy the removed element.
/// \param array A pointer to an array data structure.
/// \param index The array index where the element will be removed from.
/// \complexity O(N)
void array_remove_at(array_t *array, long long int index);

/// This function replaces an element from the array data structure at the specified index with the \n
/// new given element. If a destructor is provided, it will be used to destroy the replaced element.
/// \param array A pointer to an array data structure.
/// \param index The index where the element will be place at.
/// \param data The data to be placed at the specified index within the array.
/// \complexity O(1)
void array_set_at(array_t *array, long long int index, void *data);

/// The function returns the element of the array located at the specified index.
/// \param array A pointer to an array data structure.
/// \param index The index of the element to retrieve from the array.
/// \return The element located at the specified index within the array.
/// \complexity O(1)
void *array_get_at(array_t *array, long long int index);

/// This function queries the array data structure for the existence of the given element. \n
/// If the element exists it returns it's index, otherwise it returns minus one (-1).
/// \param array A pointer to an array data structure.
/// \param item The element to be queried in the array.
/// \return The index of the element if it exists, otherwise -1.
/// \complexity O(N)
long long int array_has_element(array_t *array, void *item);

/// This function returns the current size of the array (total number of elements).
/// \param array A pointer to an array data structure.
/// \return The size of the array (total number of elements).
/// \complexity (1)
long long int array_size(array_t *array);

/// This function queries the array data structure for emptyness.
/// \param array A pointer to an array data structure.
/// \return If the array is empty it returns one (1), otherwise it returns zero (0).
/// \complexity O(1)
int array_is_empty(array_t *array);

/// This function removes all elements and resets the array data structure. \n
/// If a destructor was provided, it will be used to destroy all the elements in the array.
/// \param array A pointer to an array data structure.
/// \complexity O(N) if destructor is provided, otherwise O(1)
void array_clear(array_t *array);

/// This function prints the array data structure to the standard output.
/// \param array A pointer to an array data structure.
/// \complexity O(N)
void array_print(array_t *array);

/// This function destroys the array data structure. If a destructor was provided, \n
/// it will be used to destroy all of the elements of the array.
/// \param array A pointer to an array data structure.
/// \complexity O(N) if destructor is provided, otherwise O(1)
void array_free(array_t *array);


#endif //TINYLIB_ARRAY_H
